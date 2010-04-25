
#include "mvar.h"
#include "mlibrary.h"
#include "mvarlibrary.h"
#include "mparser.h"
#include "mparsercontext.h"
#include "mstringbuffer.h"
#include "mstringfactory.h"
#include "mtemplatecontext.h"
#include "mnode.h"
#include "mmemutils.h"
#include "mtokenlists.h"
#include "mutils.h"
#include "msingletons.h"


/**
 * Creates a new mango variable.
 * \param   mstr        Value of the variable.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next variable in the chain.
 * \return  A new MangoVariable instance.
 */
MangoVariable *mango_variable_new(MangoString *mstr, BOOL isQuoted, MangoVariable *next)
{
    MangoVariable *mvar     = NEW(MangoVariable);
    mvar->next              = next;
    mvar->varData           = NULL;
    bzero(&mvar->value, sizeof(mvar->value));
    mvar->setNextVariable   = mango_variable_set_next;
    mango_variable_set_value(mvar, mstr, isQuoted);
    return mvar;
}

/**
 * Destroys a mango variable.
 * \param   mstr        MangoVariable *to be destroyed.
 */
void mango_variable_free(MangoVariable *mvar)
{
    if (mvar->value != NULL)
        mango_object_release((MangoObject *)mvar->value);
    MangoVariable *next = mvar->next;
    free(mvar);
    if (next != NULL)
        mango_variable_free(next);
}

/**
 * Sets the new value of a variable.
 *
 * \param   mvar        MangoVariable *whose value is to be changed.
 * \param   value       New Value
 * \param   isquoted    Is the value quoted?
 */
void mango_variable_set_value(MangoVariable *mvar, MangoString *value, BOOL isQuoted)
{
    if (mvar->value != value)
    {
        if (mvar->value != NULL)
            mango_object_release((MangoObject *)mvar->value);
        mvar->value     = value;
        mvar->isQuoted  = isQuoted;
        mvar->intValue  = 0;
        mvar->isNumber  = is_integer(mango_string_buffer(value),
                                     mango_string_length(value),
                                     &mvar->intValue);
    }
}

/**
 * Resolves the value of a variable (for rendering purposes) given the
 * template and node contexts.
 */
int mango_variable_resolve(MangoVariable *mvar,
                           MangoTemplateContext *context,
                           MangoNodeRenderContext *topContext,
                           void **value)
{
    return 0;
}

/**
 * Returns if two variables are equal.
 */
BOOL mango_variables_are_equal(const MangoVariable *var1, const MangoVariable *var2)
{
    if (var1 == var2)
    {
        return true;
    }
    else if (var1 == NULL || var2 == NULL)
    {
        return false;
    }
    else if (var1->isQuoted == var2->isQuoted && 
             var1->isNumber == var2->isNumber &&
             var1->intValue == var2->intValue)
    {
        return (mango_string_compare(var1->value, var2->value) == 0) &&
                    mango_variables_are_equal(var1->next, var2->next);
    }
    return false;
}

/**
 * Sets the next variable for a particular variable.
 *
 * \param   mvar    The variable whose next variable is to be set.
 * \param   value   Value of the next variable.  The variable now owns this
 *                  string.
 * \param   iquote  Is the value quoted?
 *
 * \return  A new variable if it is set.
 */
MangoVariable *mango_variable_set_next(MangoVariable *mvar,
                                       MangoString *value,
                                       BOOL isquoted)
{
    MangoVariable *nextVar = mango_variable_new(value, isquoted, NULL);
    mvar->next = nextVar;
    return nextVar;
}

/**
 * Extract a variable using the parser.
 *
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Errors to be set if any.
 *
 * \return A MangoVariable instance if successful, otherwise NULL with the
 * error variable set (if it is supplied).
 */
MangoVariable *mango_variable_extract_with_parser(MangoParserContext *ctx, MangoError **error)
{
    MangoParser *parser = ctx->parser;
    MangoVariable *firstVar = NULL;
    MangoVariable *lastVar = NULL;
    const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
    if (token == NULL || (error != NULL && *error != NULL))
    {
        return NULL;
    }

    MangoStringFactory *msf = ctx->strfactory;
    while (true)
    {
        BOOL isQuoted = token->tokenType == TOKEN_QUOTED_STRING;
        if (firstVar == NULL)
        {
            MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
            // see if the variable library returns a "special" variable
            MangoVariable *nextVar = isQuoted ? NULL : mango_variable_library_new_instance(varValue, ctx->varlib);
            if (nextVar == NULL)
            {
                nextVar = mango_variable_new(varValue, isQuoted, NULL);
            }
            firstVar = lastVar = nextVar;
        }
        else
        {
            MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
            MangoVariable *nextVar = lastVar->setNextVariable(lastVar, varValue, isQuoted);
            if (nextVar != NULL)
            {
                lastVar = nextVar;
            }
        }
        
        // peek at the next token...
        token = mango_parser_peek_token(parser, error);
        if (token != NULL && token->tokenType == TOKEN_DOT)
        {
            mango_parser_get_token(parser, error);    // discard the DOT
            token = mango_parser_expect_token_in_list(parser, IDENT_OR_STRING, false, error);
        }
        else
        {
            break ;
        }
    }
    return firstVar;
}



#include "mvariable.h"
#include "mparser.h"
#include "mstring.h"
#include "mtemplatecontext.h"
#include "mnode.h"
#include "mmemutils.h"
#include "mtokenlists.h"

/**
 * Creates a new mango variable.
 * \param   mstr        Value of the variable.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next variable in the chain.
 * \return  A new MangoVariable instance.
 */
MangoVariable *mango_variable_new(MangoString *mstr, BOOL isQuoted, MangoVariable *next)
{
    MangoVariable *mvar = NEW(MangoVariable);
    mvar->next      = next;
    mvar->value     = NULL;
    mango_variable_set_value(mvar, isQuoted, mstr->buffer, mstr->length);
    return mvar;
}

/**
 * Destroys a mango variable.
 * \param   mstr        MangoVariable *to be destroyed.
 */
void mango_variable_free(MangoVariable *mvar)
{
    if (mvar->value != NULL)
        mango_string_free(mvar->value);
    MangoVariable *next = mvar->next;
    free(mvar);
    if (next != NULL)
        mango_variable_free(next);
}

/**
 * Sets the new value of a variable.
 *
 * \param   mvar    MangoVariable *whose value is to be changed.
 * \param   buffer  New Value
 * \param   length  Length of the buffer.  if < then buffer is NULL terminated.
 */
void mango_variable_set_value(MangoVariable *mvar, BOOL isQuoted, const char *buffer, int length)
{
    if (mvar->value != NULL)
    {
        mango_string_free(mvar->value);
    }
    mvar->value = mango_string_from_buffer(buffer, length);
    mvar->isQuoted  = isQuoted;
    mvar->isNumber  = false;
    mvar->intValue  = 0;
    // TODO: check if integer
}

/**
 * Resolves the value of a variable (for rendering purposes) given the
 * template and node contexts.
 */
int mango_variable_resolve(MangoVariable *mvar, MangoTemplateContext *context, MangoNodeContext *topContext, void **value)
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
             var1->isNumber == var2->isNumber)
    {
        return mango_string_compare(var1->value, var2->value->buffer, var2->value->length) == 0 &&
                    mango_variables_are_equal(var1->next, var2->next);
    }
    return false;
}

/**
 * Extract a variable using the parser.
 *
 * \param   parser  Parser extracting the tokens.
 * \param   error   Errors to be set if any.
 *
 * \return A MangoVariable instance if successful, otherwise NULL with the
 * error variable set (if it is supplied).
 */
MangoVariable *mango_variable_extract_with_parser(MangoParser *parser, MangoError **error)
{
    MangoVariable *firstVar = NULL;
    MangoVariable *lastVar = NULL;
    const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
    if (token == NULL || (error != NULL && *error != NULL))
    {
        return NULL;
    }

    while (true)
    {
        const MangoString *varValue = token->tokenValue;
        BOOL isQuoted = token->tokenType == TOKEN_QUOTED_STRING;
        if (firstVar == NULL)
        {
            // see if the variable library returns a "special" variable
            MangoVariable *nextVar = isQuoted ? NULL : VariableLibrary.getSharedInstance().makeNewInstance(varValue);
            if (nextVar == NULL)
            {
                nextVar = mango_variable_new(mango_string_from_buffer(varValue->buffer, varValue->length), isQuoted, NULL);
            }
            firstVar = lastVar = nextVar;
        }
        else
        {
            // MangoVariable *nextVar = lastVar->setNextVariable(varValue, isQuoted);
            MangoVariable *nextVar = mango_variable_new(mango_string_from_buffer(varValue->buffer, varValue->length), isQuoted, NULL);
            lastVar->next = nextVar;
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


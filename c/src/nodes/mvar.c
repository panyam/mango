
#include "mangopub.h"

/**
 * The prototype for the MangoVar.
 */
DECLARE_PROTO_FUNC(mango_var_prototype, MangoVarPrototype, NULL, 
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_var_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc  = (ObjectEqualsFunc)mango_vars_are_equal;
);

/**
 * Creates a new mango var.
 * \param   mstr        Value of the var.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next var in the chain.
 * \return  A new MangoVar instance.
 */
MangoVar *mango_var_new(MangoString *mstr, BOOL isQuoted, MangoVar *next)
{
    MangoVar *mvar = NEW(MangoVar);
    return mango_var_init(mvar, NULL, mstr, isQuoted, next);
}

/**
 * Initialises a mango var.
 * \param   mvar        Var to be initialised.
 * \param   proto       Prototype to be initialised with.
 * \param   mstr        Value of the var.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next var in the chain.
 * \return  The same var.
 */
MangoVar *mango_var_init(MangoVar *mvar, MangoVarPrototype *proto,
                         MangoString *mstr, BOOL isQuoted, MangoVar *next)
{
    if (proto == NULL)
        proto = mango_var_prototype();
    OBJ_INIT(mvar, proto);
    mvar->next      = next;
    mvar->isQuoted  = isQuoted;
    mvar->isNumber  = false;
    mvar->value     = NULL;
    mango_var_set_value(mvar, mstr, isQuoted);
    return mvar;
}

/**
 * Destroys a mango var.
 * \param   mstr        MangoVar *to be destroyed.
 */
void mango_var_dealloc(MangoVar *mvar)
{
    if (mvar->value != NULL)
        OBJ_DECREF(mvar->value);
    if (mvar->next != NULL)
        OBJ_DECREF(mvar->next);
}

/**
 * Sets the new value of a var.
 *
 * \param   mvar        MangoVar *whose value is to be changed.
 * \param   value       New Value
 * \param   isquoted    Is the value quoted?
 */
void mango_var_set_value(MangoVar *mvar, MangoString *value, BOOL isQuoted)
{
    if (mvar->value != value)
    {
        OBJ_DECREF(mvar->value);
        mvar->value     = OBJ_INCREF(value);
        mvar->isQuoted  = isQuoted;
        mvar->intValue  = 0;
        mvar->isNumber  = is_integer(mango_string_buffer(value),
                                     mango_string_length(value),
                                     &mvar->intValue);
    }
}

/**
 * Resolves the value of a var (for rendering purposes) given the
 * template and node contexts.
 */
MangoObject *mango_var_resolve(MangoVar *            mvar,
                               MangoTemplateContext *context,
                               MangoNodeContext *    topContext)
{
    if (mvar->__prototype__->resolveFunc != NULL)
    {
        return mvar->__prototype__->resolveFunc(mvar, context, topContext);
    }
    // use the default resolver otherwise
    return mango_varresolver_resolve(mango_varresolver_default(), OBJ(context), mvar);
}

/**
 * Returns if two vars are equal.
 */
BOOL mango_vars_are_equal(const MangoVar *var1, const MangoVar *var2)
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
        return (OBJ_COMPARE(var1->value, var2->value) == 0) &&
                    mango_vars_are_equal(var1->next, var2->next);
    }
    return false;
}

/**
 * Sets the next var for a particular var.
 *
 * \param   mvar    The var whose next var is to be set.
 * \param   value   Value of the next var.  The var now owns this
 *                  string.
 * \param   iquote  Is the value quoted?
 *
 * \return  A new var if it is set.
 */
MangoVar *mango_var_set_next(MangoVar *mvar, MangoString *value, BOOL isquoted)
{
    if (mvar->__prototype__->setNextVarFunc != NULL)
    {
        return mvar->__prototype__->setNextVarFunc(mvar, value, isquoted);
    }

    // fall back to default
    MangoVar *nextVar = mango_var_new(value, isquoted, NULL);
    mvar->next = nextVar;
    return nextVar;
}

/**
 * Extract a var using the parser.
 *
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Errors to be set if any.
 *
 * \return A MangoVar instance if successful, otherwise NULL with the
 * error var set (if it is supplied).
 */
MangoVar *mango_var_extract_with_parser(MangoParser *parser, MangoContext *ctx, MangoError **error)
{
    MangoVar *firstVar = NULL;
    MangoVar *lastVar = NULL;
    const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
    if (token == NULL || (error != NULL && *error != NULL))
    {
        return NULL;
    }

    MangoStringFactory *msf = ctx->string_factory;
    while (true)
    {
        BOOL isQuoted = token->tokenType == TOKEN_QUOTED_STRING;
        if (firstVar == NULL)
        {
            MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
            MangoVar *nextVar = NULL;
            if (!isQuoted)
            {
                // see if the var library returns a "special" var
                MangoVarBuilder *varbuilder = (MangoVarBuilder *)OBJ_GETSTRATTR(ctx->var_library, varValue);
                if (varbuilder != NULL)
                    mango_varbuilder_new_var(varbuilder, ctx, varValue);
            }

            if (nextVar == NULL)
            {
                nextVar = mango_var_new(varValue, isQuoted, NULL);
            }
            firstVar = lastVar = nextVar;
        }
        else
        {
            MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
            MangoVar *nextVar = mango_var_set_next(lastVar, varValue, isQuoted);
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


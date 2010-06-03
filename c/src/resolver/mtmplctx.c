
#include "mangopub.h"

MangoObject *mango_tmplctx_get(MangoTemplateContext *ctx, MangoString *key);

DECLARE_PROTO_FUNC(mango_tmplctx_prototype, MangoTemplateContextPrototype, NULL, 
    ((MangoPrototype *)&__proto__)->deallocFunc     = (ObjectDeallocFunc)mango_tmplctx_dealloc;
    ((MangoPrototype *)&__proto__)->getStrAttrFunc  = (ObjectGetStrAttrFunc)mango_tmplctx_get;
    ((MangoPrototype *)&__proto__)->hasStrAttrFunc  = (ObjectHasStrAttrFunc)mango_tmplctx_contains;
    __proto__.getValuesFunc     = NULL;
    __proto__.setFunc           = NULL;
    __proto__.pushFunc          = NULL;
    __proto__.popFunc           = NULL;
    __proto__.deleteFunc        = NULL;
    __proto__.mergeFunc         = NULL;
);

/**
 * Creates a new mango template context.
 *
 * @test(TestTmplCtxInit)
 * MangoTemplateContext *context = mango_tmplctx_new();
 * CHECK_EQUAL(1, OBJ_REFCOUNT(context));
 * CHECK_EQUAL(mango_tmplctx_prototype(), context->__prototype__);
 * OBJ_DECREF(context);
 * @endtest
 */
MangoTemplateContext *mango_tmplctx_new()
{
    return mango_tmplctx_init(ZNEW(MangoTemplateContext), mango_tmplctx_prototype());
}

/**
 * Initialises the template context and returns it.
 */
MangoTemplateContext *mango_tmplctx_init(MangoTemplateContext *ctx, MangoTemplateContextPrototype *proto)
{
    if (proto == NULL)
        proto = mango_tmplctx_prototype();
    OBJ_INIT(ctx, proto);
    ctx->values = NULL;
    return ctx;
}

/**
 * Frees the context and all values in it.
 * \param   context Context to be freed.
 */
void mango_tmplctx_dealloc(MangoTemplateContext *ctx)
{
    // clear the values
    OBJ_DECREF(ctx->values);
    mango_object_dealloc((MangoObject *)(ctx));
}

/**
 * Merge the values of another dictionary into a context.
 * \param   context Context into which the values are being merged.
 * \param   dict    Dictionary from which the values are being merged.
 */
void mango_tmplctx_merge(MangoTemplateContext *ctx, MangoTable *dict)
{
    if (ctx->__prototype__->mergeFunc != NULL)
    {
        ctx->__prototype__->mergeFunc(ctx, dict);
    }
    else if (dict != NULL)
    {
        // back on default
        assert("not implemented" && false);
    }
}

/**
 * Get the values for a particular var in the context.
 * \param   context Context from which the values are extracted.
 * \param   key     Var for which the values are extracted.
 * \param   create  If the key was not found, this specifies whether a new
 *                  stack it to be created.
 * \return A MangoList of values for the var.
 *
 * @test(TestTmplCtx_GetValuesOnEmpty)
 * MangoTemplateContext *context = mango_tmplctx_new();
 * MangoString *key = (MangoString *)mango_rcstring_new("key", -1, NULL);
 * CHECK(NULL == context->values);
 * CHECK(NULL == mango_tmplctx_get_values(context, key, false));
 * OBJ_DECREF(context);
 * @endtest
 */
MangoList *mango_tmplctx_get_values(MangoTemplateContext *ctx, MangoString *key, BOOL create)
{
    if (ctx->__prototype__->getValuesFunc != NULL)
    {
        return ctx->__prototype__->getValuesFunc(ctx, key, create);
    }
    else // use default
    {
        if (ctx->values == NULL)
        {
            if (!create)
                return NULL;
            ctx->values = (MangoTable*)mango_treetable_new();
        }

        MangoList *valueStack = NULL;
        if (!OBJ_HASSTRATTR(ctx->values, key))
        {
            if (!create)
                return NULL;
            valueStack = (MangoList *)mango_linkedlist_new();
            mango_table_put(ctx->values, key, (MangoObject *)valueStack);
            OBJ_DECREF(valueStack);     // delete ref as it is now in the table
        }
        else
        {
            valueStack = (MangoList *)OBJ_GETSTRATTR(ctx->values, key);
        }
        return valueStack;
    }
    return NULL;
}

/**
 * Gets the value of a var by a key.
 * \param   ctx     The context where values are stored.
 * \param   key     Var whose value is to be fetched.
 * \return  Value of the var.
 */
MangoObject *mango_tmplctx_get(MangoTemplateContext *ctx, MangoString *key)
{
    if (ctx->values != NULL)
    {
        // fallback on our default implementation
        MangoList *valueStack = mango_tmplctx_get_values(ctx, key, true);
        if (valueStack != NULL && !COLLECTION_IS_EMPTY(valueStack))
        {
            return LIST_FRONT(valueStack);
        }
    }
    return NULL;
}

/**
 * Sets the value of a particular key, overwriting an existing one or
 * pushing onto one if necessary.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \param   push    Whether the value is to be pushed or replaced.
 * \param   The new size of the value stack for the var.
 */
int mango_tmplctx_set_or_push(MangoTemplateContext *ctx, MangoString *key, MangoObject *value, BOOL push)
{
    if (push)
    {
        return mango_tmplctx_set(ctx, key, value);
    }
    else
    {
        return mango_tmplctx_push(ctx, key, value);
    }
}

/**
 * Sets the value of a particular key.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
int mango_tmplctx_set(MangoTemplateContext *ctx, MangoString *key, MangoObject *value)
{
    if (ctx->__prototype__->setFunc != NULL)
    {
        return ctx->__prototype__->setFunc(ctx, key, value);
    }
    // resort to default 
    MangoList *valueStack = mango_tmplctx_get_values(ctx, key, true);
    if (COLLECTION_IS_EMPTY(valueStack))
    {
        LIST_PUSH_FRONT(valueStack, value);
    }
    else
    {
        LIST_SET_AT(valueStack, 0, value);
    }
    return COLLECTION_SIZE(valueStack);
}

/**
 * Sets multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be set.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
void mango_tmplctx_set_values(MangoTemplateContext *ctx, ...)
{
    va_list ap;
    va_start(ap, ctx);
    MangoString *key = va_arg(ap, MangoString *);
    while (key != NULL)
    {
        MangoObject *value = va_arg(ap, MangoObject *);
        mango_tmplctx_set(ctx, key, value);
        key = va_arg(ap, MangoString *);
    }
    va_end(ap);
}

/**
 * Pushes the value of a particular key.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
int mango_tmplctx_push(MangoTemplateContext *ctx,
                               MangoString *key,
                               MangoObject *value)
{
    if (ctx->__prototype__->pushFunc != NULL)
    {
        return ctx->__prototype__->pushFunc(ctx, key, value);
    }

    // default behaviour
    MangoList *valueStack = mango_tmplctx_get_values(ctx, key, true);
    LIST_PUSH_FRONT(valueStack, value);
    return COLLECTION_SIZE(valueStack);
}

/**
 * Pushes multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
void mango_tmplctx_push_values(MangoTemplateContext *ctx, ...)
{
    va_list ap;
    va_start(ap, ctx);
    MangoString *key = va_arg(ap, MangoString *);
    while (key != NULL)
    {
        MangoObject *value = va_arg(ap, MangoObject *);
        mango_tmplctx_push(ctx, key, value);
        key = va_arg(ap, MangoString *);
    }
    va_end(ap);
}

/**
 * Pops the value of a var and returns it.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return  MangoObject for the var.
 */
MangoObject *mango_tmplctx_pop(MangoTemplateContext *ctx,
                                      MangoString *key)
{
    if (ctx->__prototype__->popFunc != NULL)
    {
        return ctx->__prototype__->popFunc(ctx, key);
    }
    else if (ctx->values != NULL)
    {
        MangoList *ctxStack = (MangoList *)OBJ_GETSTRATTR(ctx->values, key);
        if (ctxStack != NULL && !COLLECTION_IS_EMPTY(ctxStack))
        {
            return (MangoObject *)LIST_POP_FRONT(ctxStack);
        }
    }
    return NULL;
}

/**
 * Deletes the value of a var completely.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 */
void mango_tmplctx_delete(MangoTemplateContext *ctx, MangoString *key)
{
    if (ctx->__prototype__->deleteFunc != NULL)
    {
        ctx->__prototype__->deleteFunc(ctx, key);
    }
    else if (ctx->values != NULL)
    {
        mango_table_erase(ctx->values, key);
    }
}

/**
 * Tells if a var by a particular key exists.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return true if the var exits, false otherwise.
 */
BOOL mango_tmplctx_contains(MangoTemplateContext *ctx, MangoString *key)
{
    // default impl otherwise
    return ctx->values != NULL && OBJ_HASSTRATTR(ctx->values, key);
}


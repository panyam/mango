
#include "mtmplctx.h"
#include "mstring.h"
#include "mmemutils.h"
#include "mtreetable.h"

DECLARE_PROTO_FUNC("MangoTemplateContext", MangoTemplateContextPrototype, mango_tmplctx_prototype,
    __proto__.getValuesFunc     = NULL;
    __proto__.getFunc           = NULL;
    __proto__.setFunc           = NULL;
    __proto__.pushFunc          = NULL;
    __proto__.popFunc           = NULL;
    __proto__.deleteFunc        = NULL;
    __proto__.containsFunc      = NULL;
    __proto__.mergeFunc         = NULL;
);

/**
 * Creates a new mango template context.
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
    assert("not implemented" && false);
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
    else
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
 */
const MangoList *mango_tmplctx_get_values(MangoTemplateContext *ctx, const MangoString *key, BOOL create)
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
            ctx->values = mango_treetable_new();
        }

        MangoList *valueStack = NULL;
        if (!mango_table_contains(ctx->values, key))
        {
            if (!create)
                return NULL;
            valueStack = mango_list_new();
            mango_table_put(ctx->values, key, valueStack);
        }
        else
        {
            valueStack = mango_table_get(ctx->values, key);
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
MangoObject *mango_tmplctx_get(MangoTemplateContext *ctx, const MangoString *key)
{
    if (ctx->__prototype__->getFunc != NULL)
    {
        return ctx->__prototype__->getFunc(ctx, key);
    }
    else
    {
        // fallback on our default implementation
    }
    // if not in the default impl then fallback on the get attr method
    return OBJ_GETSTRATTR(ctx, key);
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
int mango_tmplctx_set_or_push(MangoTemplateContext *ctx,
                                      const MangoString *key,
                                      MangoObject *value,
                                      BOOL push)
{
    MangoList *valueStack = mango_tmplctx_get_values(ctx, key, true);
    if (push || mango_list_is_empty(valueStack))
    {
        mango_list_push_front(valueStack, value);
    }
    else
    {
        mango_list_set_at(valueStack, 0, value);
    }
    return mango_list_size(valueStack);
}

/**
 * Sets the value of a particular key.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
int mango_tmplctx_set(MangoTemplateContext *ctx,
                              const MangoString *key,
                              MangoObject *value)
{
    if (ctx->__prototype__->setFunc != NULL)
    {
        return ctx->__prototype__->setFunc(ctx, key, value);
    }
    return 0;
}

/**
 * Sets multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be set.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
void mango_tmplctx_set_values(MangoTemplateContext *ctx, ...)
{
}

/**
 * Pushes the value of a particular key.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
int mango_tmplctx_push(MangoTemplateContext *ctx,
                               const MangoString *key,
                               MangoObject *value)
{
    if (ctx->__prototype__->pushFunc != NULL)
    {
        return ctx->__prototype__->pushFunc(ctx, key, value);
    }
    return 0;
}

/**
 * Pushes multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
void mango_tmplctx_push_values(MangoTemplateContext *ctx, ...)
{
}

/**
 * Pops the value of a var and returns it.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return  MangoObject for the var.
 */
MangoObject *mango_tmplctx_pop(MangoTemplateContext *ctx,
                                      const MangoString *key)
{
    if (ctx->__prototype__->popFunc != NULL)
    {
        return ctx->__prototype__->popFunc(ctx, key);
    }
    else if (ctx->values != NULL)
    {
        MangoList *ctxStack = mango_table_get(ctx->values, key);
        if (ctxStack != NULL && !mango_list_is_empty(ctxStack))
        {
            return mango_list_pop_front(ctxStack);
        }
    }
    return NULL;
}

/**
 * Deletes the value of a var completely.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 */
void mango_tmplctx_delete(MangoTemplateContext *ctx, const MangoString *key)
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
BOOL mango_tmplctx_contains(MangoTemplateContext *ctx, const MangoString *key)
{
    if (ctx->__prototype__->containsFunc != NULL)
    {
        return ctx->__prototype__->containsFunc(ctx, key);
    }
    // default impl otherwise
    return ctx->values != NULL && mango_table_contains(ctx->values, key);
}

#if 0
public void mergeDictionary(HashMap<String, ?> dictionary)
{
    if (dictionary != NULL)
    {
        if (values == NULL)
        {
            values = new HashMap<String, Stack<Object>>();
            for (Iterator<String> iter = dictionary.keySet().iterator();iter.hasNext();)
            {
                String key = iter.next();
                Object value = dictionary.get(key);
                setValue(key, value);
            }
        }
    }
}

/**
 * Gets the object by a key.
 * This can return a nil if the context is a sequential or an iterative container.
 */
public Object getValue(String key)
{
    if (values != NULL)
    {
        Stack<Object> ctxStack = values.get(key);
        if (ctxStack != NULL && !ctxStack.isEmpty())
            return ctxStack.firstElement();
    }
    return NULL;
}

/**
 * Sets the value of a particular key, overwriting an existing one or
 * pushing onto one if necessary.
 */
public int setValue(String key, Object value, boolean push)
{
}

/**
 * Sets the value of a key overwriting if necessary.
 * Returns the new depth of the stack.
 */
public int setValue(String key, Object value)
{
    return setValue(key, value, false);
}

/**
 * Sets multiple values into the context.
 */
public void setValues(Object ... keyValuePairs)
{
    for (int i = 0;i < keyValuePairs.length;i += 2)
        setValue((String)keyValuePairs[i], keyValuePairs[i + 1]);
}

/**
 * Pushes the value of a key to indicate entering of a new context.
 * Returns the new depth of the stack.
 */
public int pushValue(String key, Object value)
{
    return setValue(key, value, true);
}

/**
 * Pushes multiple values into the context.
 */
public void pushValues(Object ... keyValuePairs)
{
    for (int i = 0;i < keyValuePairs.length;i += 2)
        pushValue((String)keyValuePairs[i], keyValuePairs[i + 1]);
}

#endif


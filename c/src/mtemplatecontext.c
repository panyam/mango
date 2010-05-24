
#include "mtemplatecontext.h"
#include "mstring.h"
#include "mmemutils.h"
#include "mbintree.h"

/**
 * Creates a new mango template context.
 */
MangoTemplateContext *mango_templatecontext_new()
{
    return ZNEW(MangoTemplateContext);
}

/**
 * Frees the context and all values in it.
 * \param   context Context to be freed.
 */
void mango_templatecontext_free(MangoTemplateContext *context)
{
}

/**
 * Merge the values of another dictionary into a context.
 * \param   context Context into which the values are being merged.
 * \param   dict    Dictionary from which the values are being merged.
 */
void mango_templatecontext_merge(MangoTemplateContext *context, MangoBinTree *dict)
{
}

/**
 * Get the values for a particular var in the context.
 * \param   context Context from which the values are extracted.
 * \param   key     Var for which the values are extracted.
 * \param   create  If the key was not found, this specifies whether a new
 *                  stack it to be created.
 * \return A MangoList of values for the var.
 */
const MangoList *mango_templatecontext_get_values(
            MangoTemplateContext *context,
            const MangoString *key,
            BOOL create)
{
    return NULL;
}

/**
 * Gets the value of a var by a key.
 * \param   ctx     The context where values are stored.
 * \param   key     Var whose value is to be fetched.
 * \return  Value of the var.
 */
MangoObject *mango_templatecontext_get(MangoTemplateContext *ctx, const MangoString *key)
{
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
int mango_templatecontext_set_or_push(MangoTemplateContext *ctx,
                                      const MangoString *key,
                                      MangoObject *value,
                                      BOOL push)
{
    return 0;
}

/**
 * Sets the value of a particular key.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
int mango_templatecontext_set(MangoTemplateContext *ctx,
                              const MangoString *key,
                              MangoObject *value)
{
    return 0;
}

/**
 * Sets multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be set.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
void mango_templatecontext_set_values(MangoTemplateContext *ctx, ...)
{
}

/**
 * Pushes the value of a particular key.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
int mango_templatecontext_push(MangoTemplateContext *ctx,
                               const MangoString *key,
                               MangoObject *value)
{
    return 0;
}

/**
 * Pushes multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
void mango_templatecontext_push_values(MangoTemplateContext *ctx, ...)
{
}

/**
 * Pops the value of a var and returns it.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return  MangoObject for the var.
 */
MangoObject *mango_templatecontext_pop(MangoTemplateContext *ctx,
                                      const MangoString *key)
{
    return NULL;
}

/**
 * Deletes the value of a var completely.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 */
void mango_templatecontext_delete(MangoTemplateContext *ctx, const MangoString *key)
{
}

/**
 * Tells if a var by a particular key exists.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return true if the var exits, false otherwise.
 */
BOOL mango_templatecontext_contains(MangoTemplateContext *ctx, const MangoString *key)
{
    return false;
}

#if 0
public void mergeDictionary(HashMap<String, ?> dictionary)
{
    if (dictionary != null)
    {
        if (values == null)
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
 * Gets the value stack for a particular key.
 * 
 * @param key
 * @param create
 * @return
 */
public Stack<Object> getValueStack(String key, boolean create)
{
    if (values == null)
    {
        if (!create)
            return null;
        values = new HashMap<String, Stack<Object>>();
    }

    Stack<Object> valueStack = null;
    if (!values.containsKey(key))
    {
        if (!create)
            return null;
        valueStack = new Stack<Object>();
        values.put(key, valueStack);
    }
    else
    {
        valueStack = values.get(key);
    }
    return valueStack;
}

/**
 * Gets the object by a key.
 * This can return a nil if the context is a sequential or an iterative container.
 */
public Object getValue(String key)
{
    if (values != null)
    {
        Stack<Object> ctxStack = values.get(key);
        if (ctxStack != null && !ctxStack.isEmpty())
            return ctxStack.firstElement();
    }
    return null;
}

/**
 * Sets the value of a particular key, overwriting an existing one or
 * pushing onto one if necessary.
 */
public int setValue(String key, Object value, boolean push)
{
    Stack<Object> valueStack = getValueStack(key, true);
    if (push || valueStack.isEmpty())
    {
        valueStack.push(value);
    }
    else
    {
        valueStack.setElementAt(value, 0);
    }
    return valueStack.size();
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

/**
 * Pushes the value of a key to indicate entering of a new context.
 * Returns the old value.
 */
public Object popValue(String key)
{
    if (values != null)
    {
        Stack<?> ctxStack   = values.get(key);
        if (ctxStack != null && !ctxStack.isEmpty())
        {
            return ctxStack.pop();
        }
    }
    return null;
}

/**
 * Deletes a value completely.
 */
public void deleteValue(String key)
{
    if (values != null)
        values.remove(key);
}

/**
 * Tells if a value exists in the context.
 */
public boolean hasValue(String key)
{
    return values != null && values.containsKey(key);
}
#endif


package com.panyam.mango.templates.core;

import java.util.*;

/**
 * Context objects contain values for variables that get substituted in a template.
 */
public class TemplateContext
{
    protected HashMap<String, Stack<Object>> values;

    /**
     * Creates a new template context.
     */
    public TemplateContext()
    {
        this(null);
    }

    /**
     * Creates a new template context with a dictionary of values.
     */
    public TemplateContext(HashMap<String, ?> dictionary)
    {
        mergeDictionary(dictionary);
    }

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
}


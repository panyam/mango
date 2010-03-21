package com.panyam.mango.templates.variables;

import java.lang.reflect.*;
import java.util.*;
import com.panyam.mango.templates.core.*;

/**
 * @author Sri Panyam
 */
public class DefaultVariableResolver extends VariableResolver 
{
	// static instance
	public static DefaultVariableResolver DEFALT_RESOLVER = new DefaultVariableResolver();

	/* 
	 * (non-Javadoc)
	 * @see com.panyam.mango.templates.VariableResolver#resolve(java.lang.Object, com.panyam.mango.templates.Variable)
	 */
	@Override
	public Object resolve(Object source, Variable variable) 
	{
	    /**
	     * Resolves the value of a variable using a particular value.
	     * The resolution strategy used is slightly different from what django
	     * does, in order to make things a bit faster for the common case of
	     * dictionary and index based lookups.
	     *
	     * ((Array)source)[value] if value is an integer
	     * ((Dictionary)source)[value] if value is NOT an integer
	     *
	     * If the object is 
	     * If value is a quoted string or a variable then the object is
	     *
	     * Returns null if the variable cannot be resolved after applying the
	     * above rules.
	     */
        // try as an integer first
    	boolean performMethodAndAttributeCheck = true;
        if (variable.isNumber)
        {
        	int intValue = variable.intValue();
        	// set this flag to true so that if we fall through here and go to the map case
        	// then we do not want this to be treated as a method or an attribute
        	performMethodAndAttributeCheck = false;
            if (source instanceof Vector<?>)
            {
                return ((Vector<?>)source).elementAt(intValue);
            }
            else if (source instanceof ArrayList<?>)
            {
                return ((ArrayList<?>)source).get(intValue);
            }
            else
            {
                // convert to an array
            	if (source.getClass().isArray())
            	{
            		return Array.get(source, intValue);
            	}
            	else
            	{
            		// worst case - see if the object has a method
            		// atIndex or elementAt or something like that
            		// we will go with elementAtIndex for now.
            		Class<?> sourceClass = source.getClass();
            		Method method = null;
					try {
						method = sourceClass.getMethod("elementAtIndex", int.class);
					} catch (SecurityException e) {
						e.printStackTrace();
					} catch (NoSuchMethodException e) {
						e.printStackTrace();
					}

            		if (method != null)
            		{
            			try {
            				method.setAccessible(true);
							return method.invoke(source, intValue);
						} catch (IllegalArgumentException e) {
							e.printStackTrace();
						} catch (IllegalAccessException e) {
							e.printStackTrace();
						} catch (InvocationTargetException e) {
							e.printStackTrace();
						}
            		}
            		
            		// here we fall through and let it be handled as a map/associative 
            		// container of some sort
            	}
            }
        }
        
        String value = variable.value;

        // try as a dictionary lookup - ie using a Map
        if (source instanceof Map<?,?> && ((Map<?,?>)source).containsKey(value))
        {
        	return ((Map<?,?>)source).get(value);
        }
        if (source instanceof Hashtable<?,?> && ((Hashtable<?,?>)source).containsKey(value))
        {
        	return ((Hashtable<?,?>)source).get(value);
        }
        if (source instanceof TemplateContext && ((TemplateContext)source).hasValue(value))
        {
        	return ((TemplateContext)source).getValue(value);
        }

        // now check if we are a method or an attribute
        if (performMethodAndAttributeCheck)
        {
        	// first check for attributes
        	Class<?> sourceClass = source.getClass();
        	try {
				Field field = sourceClass.getField(value);
				try {
					field.setAccessible(true);
					return field.get(source);
				} catch (IllegalArgumentException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				}
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (NoSuchFieldException e) {
			}
			
			try {
				Method method = sourceClass.getMethod(value, (Class [])null);
				try {
					method.setAccessible(true);
					return method.invoke(source, (Object [])null);
				} catch (IllegalArgumentException e) {
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					e.printStackTrace();
				} catch (InvocationTargetException e) {
					e.printStackTrace();
				}
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (NoSuchMethodException e) {
			}
        }
        return null;
	}
}

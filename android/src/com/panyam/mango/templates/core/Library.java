 
package com.panyam.mango.templates.core;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.*;

public class Library<E>
{
    protected HashMap<String, Class<?>> objClasses;
    
    public Library()
    {
        objClasses = new HashMap<String, Class<?>>();
    }

    public void registerObjectClass(String name, Class<?> objClass)
    {
        objClasses.put(name, objClass);
        onClassRegistered(objClass);
    }
    
    public Class<?> getObjectClass(String name)
    {
        return objClasses.get(name);
    }
    
    /**
     * Makes a new instance of a particular class.
     * 
     * @param c
     * @return
     */
	public E makeNewInstance(String name)
    {
    	Class<?> objClass = objClasses.get(name);
    	if (objClass == null)
    		return null;
    	return createNewInstance(name, objClass);
    }
    
    /**
     * Callback called when a class is registered.
     * @param objClass
     */
    public void onClassRegistered(Class<?> objClass)
    {
        Method callbackMethod;
		try {
			callbackMethod = objClass.getMethod("onClassRegistered", (Class [])null);
	        try {
				callbackMethod.invoke(objClass, (Object[])null);
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

    @SuppressWarnings("unchecked")
	protected E createNewInstance(String name, Class<?> objClass)
    {
        try 
        {
            return (E)objClass.newInstance();
        } 
        catch (IllegalAccessException e) 
        {
        	return (E)createFromConstructor(name, objClass);
        }
        catch (InstantiationException e) 
        {
        	e.printStackTrace();
        }
        return null;
    }
    
	protected Object createFromConstructor(String name, Class<?>objClass)
    {
    	// this could happen if the class is an inner (or anonymous) class 
    	// and does not explicitly define a constructor
    	try {
			Constructor<?> constructor = objClass.getConstructor((Class [])null);
			try {
				constructor.setAccessible(true);
				return constructor.newInstance((Object[])null);
			} catch (IllegalArgumentException e1) {
				e1.printStackTrace();
			} catch (InstantiationException e1) {
				e1.printStackTrace();
			} catch (IllegalAccessException e1) {
				e1.printStackTrace();
			} catch (InvocationTargetException e1) {
				e1.printStackTrace();
			}
		} catch (SecurityException e1) {
			e1.printStackTrace();
		} catch (NoSuchMethodException e1) {
			e1.printStackTrace();
		}
		return null;
    }
}


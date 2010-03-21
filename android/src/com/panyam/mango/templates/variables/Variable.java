package com.panyam.mango.templates.variables;

import com.panyam.mango.templates.core.*;

public class Variable
{
    protected String value;
    public boolean isQuoted;
    protected Variable nextVar;
    protected boolean isNumber;
    protected int   intValue;       // only valid if isNumber
	protected final static Class<?> []INT_PARAM_CLASS = new Class[]{int.class};

    /**
     * Creates a variable out a value. If the string is not quoted, then whether 
     * the value is a number will be automatically determined.
     * @param val
     * @param isNum
     * @param next
     */
    public Variable(String val, boolean isQuoted, Variable next)
    {
        this.isNumber = true;
        this.isQuoted = isQuoted;
        this.nextVar = next;
        setValue(val);
    }

    /**
     * Constructor to create a variable out a non-quoted string value 
     * to auto determine whether the value is a number.
     * @param val
     * @param next
     */
    public Variable(String val, Variable next)
    {
        this(val, false, next);
    }

    /**
     * Creates a variable out a value. If the string is not quoted, then whether 
     * the value is a number will be automatically determined.
     * @param val
     * @param isQuoted
     */
    public Variable(String val, boolean isQuoted)
    {
    	this(val, isQuoted, null);
    }

    /**
     * Constructor to create a variable out a non-quoted string.  
     * @param val
     */
    public Variable(String val)
    {
        this(val, null);
    }

    /**
     * Default constructor setting default values of all variables.
     */
    public Variable()
    {
        this(null, false, null);
    }
    
    /**
     * Gets the value of the variable.
     * 
     * @return
     */
    public String value()
    {
    	return value;
    }

    /**
     * Sets the value of the variable.
     * 
     * @param val
     */
    public void setValue(String val)
    {
        this.value = val;
        if (value != null)
        {
            try
            {
                intValue = Integer.parseInt(value);
            }
            catch (NumberFormatException nfe)
            {
                // if not an integer than turn off isNumber
                isNumber = false;
            }
        }
    }
    
    /**
     * Gets the next variable if any.
     * @return the next variable if any.
     */
    public Variable nextVariable()
    {
    	return nextVar;
    }
    
    /**
     * Tries to the set the value of the next variable.
     * Returns the next variable if it was set, otherwise null.
     * 
     * @param value
     * @param isquoted
     * @return the next variable if it was set, otherwise null.
     */
    public Variable setNextVariable(String value, boolean isquoted)
    {
    	nextVar = new Variable(value, isquoted);
    	return nextVar;
    }
    
    /**
     * Resolves the value of the variable against the rendering and template contexts and returns the value.
     * @return Resolved value of the variable.
     */
    public Object resolve(TemplateContext context, NodeContext topContext)
    {
    	return DefaultVariableResolver.DEFALT_RESOLVER.resolveVariableChain(context, this);
    }
    
    /**
     * Resolves the value of the variable against the rendering and template contexts and returns the value.
     * @return Resolved value of the variable.
     */
    public Object resolve(TemplateContext context)
    {
    	return resolve(context, null);
    }

    /**
     * Resolves the value of the variable against the rendering and template contexts and returns the value.
     * @return Resolved value of the variable.
     */
    public Object resolve()
    {
    	return resolve(null, null);
    }

    /**
     * returns the integer value of the variable.
     * Only valid if isNumber is set.
     * @return The parsed integer value.
     */
    public int intValue()
    {
    	return intValue;
    }
    
    /**
     * Returns whether the value is a number or not.
     * @return
     */
    public boolean isNumber()
    {
    	return isNumber;
    }
    
    /**
     * Checks if this variable equals another object.
     */
    public boolean equals(Object another)
    {
        if (another == null)
            return false;
        if (this == another)
            return true;
        if (!(another instanceof Variable))
            return false;
        Variable anotherVar = (Variable)another;
        if (anotherVar.value.equals(value))
            if (anotherVar.isQuoted == this.isQuoted)
                if (anotherVar.isNumber == this.isNumber)
                    if (nextVar == anotherVar.nextVar)
                        return true;
                    else if (nextVar != null)
                        return nextVar.equals(anotherVar.nextVar); 
        return false;
    }
}



package com.panyam.mango.templates.core.expressions;

import java.util.Collection;

import com.panyam.mango.templates.core.*;

/**
 * Enables boolean expressions.
 * 
 * @author Sri Panyam
 */
public class Expression 
{
	/**
	 * Whether the negation is true or not.
	 */
	protected boolean negate;

	/**
	 * Constructor.
	 * 
	 * @param neg
	 */
	public Expression()
	{
		this(false);
	}

	/**
	 * Constructor.
	 * 
	 * @param neg
	 */
	public Expression(boolean neg)
	{
		negate = neg;
	}

	/**
	 * Turns on negation of the result.
	 */
	public void negate()
	{
		negate = !negate;
	}
	
	/**
	 * Tells if the result is negated.
	 * @return
	 */
	public boolean isNegated()
	{
		return negate;
	}
	
	/**
	 * Evaluates a result taking into account the negation flag.
	 * 
	 * @param context
	 * @param topContext
	 * @return
	 */
	public final boolean evaluate(TemplateContext context, NodeContext topContext)
	{
		Object val = getValue(context, topContext);
		boolean evalResult = val != null;
		if (val instanceof Boolean)
		{
			evalResult =  ((Boolean)val).booleanValue();
		}
		else if (val instanceof Integer)
		{
			evalResult = ((Integer)val).intValue() != 0;
		}
		else if (val instanceof String)
		{
			evalResult = ((String)val).length() != 0;
		}
		else if (val instanceof Collection<?>)
		{
			evalResult = !((Collection<?>)val).isEmpty();
		}

		return negate ? !evalResult : evalResult;
	}
	
    /**
     * Evaluates a condition to true or false.
     * 
     * @param context
     * @param topContext
     * @return
     */
    protected boolean evaluateTrue(TemplateContext context, NodeContext topContext)
    {
        return false;
    }
    
    /**
     * Returns the value of a condition.
     * 
     * @param context
     * @param topContext
     * @return
     */
    protected Object getValue(TemplateContext context, NodeContext topContext)
    {
    	return null;
    }

    public boolean equalsAnotherExpression(Expression another)
    {
        return true;
    }

    public boolean equals(Object another)
    {
        if (another == this)
            return true;
        if (another == null)
            return false;
        if (!(another instanceof Expression))
            return false;

        Expression anotherCond = (Expression)another;
        return negate == anotherCond.negate && equalsAnotherExpression(anotherCond);
    }
}


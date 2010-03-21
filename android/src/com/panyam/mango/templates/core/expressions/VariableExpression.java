package com.panyam.mango.templates.core.expressions;

import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.utils.*;
import com.panyam.mango.templates.variables.*;

public class VariableExpression extends Expression 
{
	Variable variable;

	public VariableExpression(Variable var) 
	{
		variable = var;
	}

	public boolean equalsAnotherExpression(Expression cond)
	{
		if (!(cond instanceof VariableExpression))
			return false;
		return CompareUtils.ObjectsEqual(variable, ((VariableExpression)cond).variable);
	}
    
    /**
     * Returns the value of a condition.
     * 
     * @param context
     * @param topContext
     * @return
     */
    protected Object value(TemplateContext context, NodeContext topContext)
    {
    	return variable.resolve(context, topContext);
    }
}

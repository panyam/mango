package com.panyam.mango.templates.variables;

import com.panyam.mango.templates.core.*;

/**
 * This interface allows variables to be resolved against a source object.
 * How this is done can be changed by derived instances.  The default
 * resolver (mostly) follows mango's way of resolving variables on
 * contexts.
 */
public class VariableResolver 
{
	public Object resolve(Object source, Variable variable)
	{
		return null;
	}
	
	/**
	 * Resolves a variable chain starting from the first variable using the template context.
	 * @param context
	 * @param first
	 * @return
	 */
	public final Object resolveVariableChain(TemplateContext context, Variable first)
	{
		// if the first item is a number then everything is ignored
		Variable currVariable = first;
		Object prevVariable = null;
		Object currSource = context;
		while (currSource != null && currVariable != null)
		{
			if (prevVariable == null)
			{
				if (currVariable.isNumber)
					return currVariable.intValue();
				if (currVariable.isQuoted)
					return currVariable.value;
				if (context == null)
					return null;
				currSource = context.getValue(currVariable.value);
			}
			else
			{
				currSource = resolve(currSource, currVariable);
			}
			prevVariable = currVariable;
			currVariable = currVariable.nextVar;
		}
		return currSource;
	}
}

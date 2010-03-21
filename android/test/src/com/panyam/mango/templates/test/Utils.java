package com.panyam.mango.templates.test;

import java.util.*;

import com.panyam.mango.templates.core.expressions.BinaryExpression;
import com.panyam.mango.templates.core.expressions.Expression;
import com.panyam.mango.templates.core.expressions.Operator;
import com.panyam.mango.templates.core.expressions.VariableExpression;
import com.panyam.mango.templates.variables.Variable;

public class Utils 
{
	public static ArrayList<?> makeArrayList(Object ... arguments)
	{
		ArrayList<Object> out = new ArrayList<Object>();
		for (int i = 0;i < arguments.length;i++)
			out.add(arguments[i]);
		return out;
	}
	
	public static Hashtable<String,Object> makeHashtable(Object ...keysAndValues)
	{
		Hashtable<String,Object> out = new Hashtable<String,Object>();
		for (int i = 0;i < keysAndValues.length;i += 2)
		{
			out.put((String)keysAndValues[i], keysAndValues[i + 1]);
		}
		return out;
	}
	
	public static HashMap<String,Object> makeHashMap(Object ...keysAndValues)
	{
		HashMap<String,Object> out = new HashMap<String,Object>();
		for (int i = 0;i < keysAndValues.length;i += 2)
		{
			out.put((String)keysAndValues[i], keysAndValues[i + 1]);
		}
		return out;
	}

	public static LinkedList<Object> makeLinkedList(Object ... arguments)
	{
		LinkedList<Object> out = new LinkedList<Object>();
		for (int i = 0;i < arguments.length;i++)
		{
			out.add(arguments[i]);
		}
		return out;
	}
    
    protected VariableExpression makeVarCond(String ... varnames)
    {
    	Variable firstVar = null;
    	Variable lastVar = null;
    	for (int i = 0;i < varnames.length;i++)
    	{
    		Variable newVar = new Variable(varnames[i]);
    		if (firstVar == null)
    		{
    			firstVar = lastVar = newVar;
    		}
    		else 
    		{
    			Variable nextVar = lastVar.setNextVariable(varnames[i], false);
    			if (nextVar != null)
    				lastVar = nextVar;
    		}
    	}
    	return new VariableExpression(firstVar);
    }
    
    protected BinaryExpression binCond(Operator op, Expression lhs, Expression rhs)
    {
    	return new BinaryExpression(op, lhs, rhs);
    }
}

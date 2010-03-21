package com.panyam.mango.templates.filters;

import java.util.*;
import com.panyam.mango.templates.utils.*;
import com.panyam.mango.templates.variables.*;
import com.panyam.mango.templates.core.*;

/**
 * A filter node is a node in the parse tree indicating a call to a filter evaluation.
 * 
 * @author Sri Panyam.
 */
public class FilterNode 
{
    /**
     * The filter that will be applied when called.
     */
    public Filter            filter;
    public ArrayList<Variable>    arguments;
    
    /**
     * Creates a new filter node.
     * @param f
     */
    public FilterNode(Filter f)
    {
        filter = f;
    }
    
    /**
     * Compares two filter nodes.
     */
    public boolean equals(Object another)
    {
        if (another == this)
            return true;
        if (another == null || !(another instanceof FilterNode))
            return false;
        FilterNode anotherFilter = (FilterNode)another;
        if (filter != anotherFilter.filter)
        {
            return false;
        }
        return CompareUtils.IterablesEqual(arguments, anotherFilter.arguments);
    }
    
    /**
     * Adds a new variable to the argument list.
     * @param var
     */
    public void addArgument(Variable var)
    {
        if (arguments == null)
            arguments = new ArrayList<Variable>();
        arguments.add(var);
    }

    public Object applyFilter(Object value, TemplateContext context)
    {
    	return filter.apply(value, context, arguments);
    }
}

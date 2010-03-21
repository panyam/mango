package com.panyam.mango.templates.filters;

import java.io.*;
import java.util.*;
import com.panyam.mango.templates.variables.*;
import com.panyam.mango.templates.core.*;

/**
 * Filters get applied on variables in how they manipulate the value stored in a variable.
 * 
 * We do not want to have multiple instances of the same filter.  So it would be better to 
 * have a single instance of the filter through out the application to save memory and their
 * performance wouldnt be bad either.  Since only a certain number of filter instances are 
 * created to conserve memory, this implies that Filter objects cannot have shared state or 
 * state specific to each invocation(of their render) method.  This is for the sake of thread
 * safety.
 *
 * So as an extension (at a later date), this restriction on shared or invocation specific 
 * state can be relaxed by having a FilterContext object associated with each filter if
 * this is a paramount requirement.
 * 
 * @author Sri Panyam
 */
public class Filter
{
    /**
     * Creates a new filter.
     */
    public Filter()
    {
    }
    
    /**
     * Creates a filter instance specific context.
     * @return A filter specific context object.
     */
    public Object makeInstanceContext(ArrayList<Variable> arguments)
    {
        return null;
    }
    
    /**
     * Creates an invocation specific context for the filter.
     * @return An invocation specific context object for this filter.
     */
    public Object makeInvocationContext(ArrayList<Variable> arguments)
    {
        return null;
    }

    /**
     * Transforms the string and returns the rendered value.
     * The value is modified using the arguments and an optional filterContext.
     * The filterContext holds "softened" version of the arguments that it can use
     * on multiple invocations for the sake of efficiency.  For instance in an "add"
     * filter that would increment the value of an input string by some amount, 
     * it makes sense to cache the value as an integer instead of converting the
     * stringified argument on each render call!
     * @throws IOException 
     */
    public Object apply(Object input, TemplateContext context, ArrayList<Variable>arguments)
    {
    	return null;
    }
}

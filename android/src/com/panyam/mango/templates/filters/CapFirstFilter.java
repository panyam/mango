
package com.panyam.mango.templates.filters;

import java.io.*;
import java.util.*;

import com.panyam.mango.templates.variables.*;
import com.panyam.mango.templates.core.*;

/**
 * Capitalises the first character of the input.
 */
public class CapFirstFilter extends Filter
{
    /**
     * Constructor.
     */
    public CapFirstFilter()
    {
    }

    /**
     * Transforms the string and returns the rendered value.
     * @throws IOException 
     */
    public Object apply(Object input, VariableResolver resolver, TemplateContext context, ArrayList<Variable>arguments)
    {
        if (input != null && input instanceof String)
        {
        	String inputString = (String)input;
        	return Character.toUpperCase(inputString.charAt(0)) + inputString.substring(1);
        }
        return null;
    }
}


package com.panyam.mango.templates.filters;

import java.io.*;
import java.util.*;

import com.panyam.mango.templates.variables.*;
import com.panyam.mango.templates.core.*;

/**
 * Cuts all occurrences of a given pattern from the input string.
 */
public class CutFilter extends Filter
{
    /**
     * Constructor.
     */
    public CutFilter()
    {
    }

    /**
     * Transforms the string and returns the rendered value.
     * @throws IOException 
     */
    public Object appy(Object input, VariableResolver resolver, TemplateContext context, ArrayList<Variable>arguments)
    {
        if (input != null && input instanceof String && !arguments.isEmpty())
        {
            Variable firstVar = arguments.get(0);
            String replaced = (String)input;
            return replaced.replaceAll(firstVar.value(), "");
        }
        return null;
    }
}

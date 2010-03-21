package com.panyam.mango.templates.filters;

import java.io.*;
import java.util.*;

import com.panyam.mango.templates.variables.*;
import com.panyam.mango.templates.core.*;


/**
 * Adds a number to a value.
 */
public class AddFilter extends Filter
{
    /**
     * The AddFilter context.  Holds the increment amount.
     * 
     * @author Sri Panyam
     */
    class AddFilterContext
    {
        public int addAmount;
    }
    /**
     * Creates a ForTagNode directly without parsing from the input.
     */
    public AddFilter()
    {
    }

    /**
     * Transforms the string and returns the rendered value.
     * @throws IOException 
     */
    public Object apply(Object input, VariableResolver resolver, TemplateContext context, ArrayList<Variable>arguments)
    {
    	/*
        if (input != null)
        {
            int incrementAmount = 0;
            int inputValue = 0;
            if (filterContext != null)
            {
                incrementAmount = ((AddFilterContext)filterContext).addAmount;
            }
            else
            {
                try
                {
                    inputValue = Integer.parseInt(input);
                    incrementAmount = Integer.parseInt(input);
                }
                catch (NumberFormatException nfe)
                {
                    nfe.printStackTrace();
                }
            }
            try
            {
                Variable first = arguments.get(0);
                if (first.isNumber)
                {
                    output.write(""+ inputValue + incrementAmount);
                }
                else
                {
                    output.write(first.value);
                }
            }
            catch (NoSuchElementException nsee)
            {
                nsee.printStackTrace();
            }
        }
        */
    	return null;
    }
}

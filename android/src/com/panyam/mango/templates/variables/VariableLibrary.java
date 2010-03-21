package com.panyam.mango.templates.variables;

import com.panyam.mango.templates.core.Library;

public class VariableLibrary extends Library<Variable> 
{
    protected static VariableLibrary sharedInstance = null;

    /**
     * Gets the shared instance of the library.
     */
    public static VariableLibrary getSharedInstance()
    {
        if (sharedInstance == null)
            sharedInstance = new VariableLibrary();
        return sharedInstance;
    }
}

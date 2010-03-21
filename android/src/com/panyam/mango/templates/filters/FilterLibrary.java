package com.panyam.mango.templates.filters;

import com.panyam.mango.templates.core.*;
import java.util.*;

public class FilterLibrary extends Library<Filter>
{
    protected static FilterLibrary sharedInstance = null;
    protected HashMap<String, Filter> filterInstances;

    /**
     * Gets the shared instance of the library.
     */
    public static FilterLibrary getSharedInstance()
    {
        if (sharedInstance == null)
            sharedInstance = new FilterLibrary();
        return sharedInstance;
    }
    
    public FilterLibrary()
    {
    	filterInstances = new HashMap<String, Filter>();
    }

    /**
     * Makes a new instance of a particular TagNode class.
     * 
     * @param c
     * @return
     */
	public Filter createNewInstance(String name, Class<?>objClass)
    {
		Filter f = filterInstances.get(name);
		if (f == null)
		{
			f = super.createNewInstance(name, objClass);
			filterInstances.put(name, f);
		}
		return f;
    }
}


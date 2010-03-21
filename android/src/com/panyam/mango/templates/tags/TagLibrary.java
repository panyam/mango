
package com.panyam.mango.templates.tags;

import com.panyam.mango.templates.core.*;

public class TagLibrary extends Library<TagNode>
{
    protected static TagLibrary sharedInstance = null;

    /**
     * Gets the shared instance of the library.
     */
    public static TagLibrary getSharedInstance()
    {
        if (sharedInstance == null)
            sharedInstance = new TagLibrary();
        return sharedInstance;
    }
}


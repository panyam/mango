package com.panyam.mango.templates.core;

import java.io.*;

public class FreeTextNode extends Node
{
    /**
     * The freetext content.
     */
    protected String content;

    /**
     * Creates a ft node with some content.
     */
    public FreeTextNode(String content)
    {
        this.content = content == null ? "" : content;
    }

    /**
     * Renders the next bit or returns the next child node to transfer rendering to.
     * 
     * @param writer
     * @param context
     * @param topContext	The stack of rendering contexts of the parents and the current node.  
     * 						The top of the stack MUST be the context for the current node.  If 
     * 						the node has no contexts then it must atleast have a null.
     * 
     * @return The next node to be rendered.
     *  if null - then this node has finished and the control is to be transferred back to the parent
     *  if this - this this node will be continued on with
     *  otherwise, a child node will be rendered.
     */
    public Node renderBitMore(Writer writer, TemplateContext context, NodeContext topContext) throws IOException
    {
    	writer.write(content);
    	return null;	// no more output left
    }

    /**
     * Compares two objects.
     */
    public boolean equals(Object another)
    {
        if (another == this)
            return true;
        if (another == null || !(another instanceof FreeTextNode))
            return false;
        FreeTextNode ftNode = (FreeTextNode)another;
        return content.equals(ftNode.content);
    }
}


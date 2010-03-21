package com.panyam.mango.templates.core;

import java.io.IOException;
import java.io.Writer;
import java.util.*;

public class NodeList extends Node implements Iterable<Node>
{
	List<Node> nodeList;

    public class NodeListContext extends NodeContext
    {
        Iterator<Node> iterator;
        /**
         * Create with a node and a parent context.
         * @param node
         * @param parent
         */
        public NodeListContext(Node node, NodeContext parent)
        {
            super(node, parent);
            if (node instanceof NodeList)
            	iterator = ((NodeList)node).nodeList.iterator();
        }
    }

	public NodeList() 
	{
		this(null);
	}
	
	public NodeList(List<Node> nodes)
	{
		nodeList = nodes;
	}
	
	public Iterator<Node> iterator()
	{
		return nodeList == null ? null : nodeList.iterator();
	}
	
	public int size()
	{
		return nodeList == null ? 0 : nodeList.size();
	}

    /**
     * This method begins the incremental rendering process.  
     * Returns a nodeContext which will have to be passed into repeated calls to render.
     * 
     * @param resolver
     * @param context
     * @param contextStack	The stack containing the contexts of the parent nodes.
     * @return
     */
    public NodeContext createNodeContext(TemplateContext context, NodeContext topContext)
    {
    	return new NodeListContext(this, topContext);
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
    public Node renderBitMore(Writer writer, 
    						TemplateContext context, 
    						NodeContext currContext) throws IOException
    {
    	return childExited(null, context, currContext);
    }

    /**
     * Called when a child node (that was returned in renderBitMore) was exited having completed.
     * By doing this we are giving the parent node a chance to tell the renderer what the next 
     * node will be.
     * 
     * In this case we simply see if there are any more nodes to recurse into and return them.
     * 
     * @param childNode
     * @param context
     * @param currContext
     * @return null if this node is ALSO to be exited, otherwise a new child node to be pushed 
     * onto the renderer stack.
     */
	public Node childExited(Node childNode, TemplateContext context, NodeContext currContext) 
	{
    	if (currContext instanceof NodeListContext)
    	{
    		NodeListContext nlContext = (NodeListContext)currContext;
    		if (nlContext.iterator != null && nlContext.iterator.hasNext())
    		{
    			return nlContext.iterator.next();
    		}
    	}
    	return null;
	}
}

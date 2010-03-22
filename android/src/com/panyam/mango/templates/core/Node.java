package com.panyam.mango.templates.core;

import java.io.*;

/**
 * A parse tree node is responsible for rendering a bit of templated content.
 *
 * basically at the tokenizer level we know what the name of a node is.
 * But any parsing must be done by particular node factories or node
 * parsers.  So for a variable node, we use VariableNode parsers and for
 * other nodes we provide the ability to extend and inherit the node parser
 * classes to do the work.
 *
 * To answer how a node name gets associated with a node at run time, the
 * answer is that objective C allows you to use classes as first class
 * objects.  So a particular node's object is good enough for us!
 *
 * Another alternative is to simply have a NodeLibrary class where all
 * methods with a particular prefix (eg node or node_) will be treated as
 * Node parsers or creators.
 */
public class Node
{
    /**
     * Creates a new node.
     */
    public Node()
    {
    }
    
    /**
     * Gets the node name.
     */
    public String nodeName()
    {
        return "";
    }
    
    /**
     * Get the number of children.
     * 
     * @return
     */
    public int childNodeCount()
    {
    	return 0;
    }

    /**
     * Get the child node at a given index.
     * 
     * @param index
     * @return
     */
    public Node getChildNode(int index)
    {
    	return null;
    }

    /**
     * This method begins the incremental rendering process.  
     * Returns a nodeContext which will have to be passed into repeated calls to render.
     * 
     * @param context
     * @param contextStack	The stack containing the contexts of the parent nodes.
     * @return
     */
    public NodeContext createNodeContext(TemplateContext context, NodeContext topContext)
    {
    	// create the default context
    	return new NodeContext(this, topContext);
    }

    public static NodeList MakeNodeList(Node ... nodes)
    {
    	java.util.LinkedList<Node> out = new java.util.LinkedList<Node>();
    	for (int i = 0;i < nodes.length;i++)
    	{
    		out.add(nodes[i]);
    	}
    	return new NodeList(out);
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
    						NodeContext topContext) throws IOException
    {
    	return null;
    }

    /**
     * Called when a child node (that was returned in renderBitMore) was exited having completed.
     * By doing this we are giving the parent node a chance to tell the renderer what the next 
     * node will be.
     * @param childNode
     * @param context
     * @param currContext
     * @return null if this node is ALSO to be exited, otherwise a new child node to be pushed 
     * onto the renderer stack.
     */
	public Node childExited(Node childNode, TemplateContext context, NodeContext currContext) 
	{
		return null;
	}

	/**
	 * Utility class to compare two nodes.
	 * 
	 * @param node1
	 * @param node2
	 * @return
	 */
	public static boolean CompareNodes(Node node1, Node node2)
	{
		if (node1 == node2)
		{
			return true;
		}
		else if (node1 == null)
		{
			return false;
		}
		return node1.equals(node2);
	}
}


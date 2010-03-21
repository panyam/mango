package com.panyam.mango.templates.core;

/**
 * NodeContexts are what make incremental rendering possible.  
 * They hold information about the rendering state of a node at any given time.
 * @author Sri Panyam
 */
public class NodeContext 
{
    public Node node;
    public NodeContext parent;
	protected int level;
	
	/**
	 * Create with a node and a parent context.
	 * @param node
	 * @param parent
	 */
	public NodeContext(Node node, NodeContext parent)
	{
        this.node = node;
        this.parent = parent;
        level = parent == null ? 0 : parent.level + 1;
	}
	
	/**
	 * @return The level of the context within the stack.
	 */
	int level()
	{
		return level;
	}
}

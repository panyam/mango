 package com.panyam.mango.templates.tags;

import com.panyam.mango.templates.core.*;

/**
 * FilterTagNodes are base classes for all tag nodes which can apply certain 
 * operations on Nodes before a rendering operation is done.  Classic example
 * is the Extends node which applies new blocks to existing blocks in an 
 * existing template.  So the filtering is happening on the child contents
 * of the Extends tag.
 *
 * Another way to achieve this would be have each class maintain its own renderer,
 * For example in the Extends tag, renderBitMore could manually query its children,
 * get the next node and then modify block nodes.  But the manual querying is a 
 * process best done by the renderer for the sake of cleanliness and possible
 * optimisations that may be possible because of a global view that the renderer 
 * has.
 * 
 * @author Sri
 */
public interface NodeFilter 
{
	/**
	 * Filters a given node.
	 * 
	 * @param node	Input node to be filtered or transformed.
	 * 
	 * @return Returns the same node to let it through, a different node for 
	 * a modified one or null to suppress it.
	 */
	public Node filterNode(Node node, TemplateContext context, NodeContext currContext);
}

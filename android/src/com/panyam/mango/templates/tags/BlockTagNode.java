package com.panyam.mango.templates.tags;

import java.io.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.utils.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.variables.*;

/**
 * A tag for doing for loops.
 * Loops would be as:
 *
 * {% for (item1, item2, item3...itemn) in sourceVariable %}
 * {% empty %}
 * {% endfor %}
 * @author root
 */
public class BlockTagNode extends TagNode
{
	// Name of the block - optional
	String blockName;
	Node blockContent;

    private final static String []ENDBLOCK = new String[] { "endblock", null };

    /**
     * Default constructor
     */
    public BlockTagNode()
    {
        this(null);
    }

    /**
     * Constructor with just the block tag name.
     */
    public BlockTagNode(String name)
    {
    	this(name, null);
    }

    /**
     * Constructor with name and block contents.
     */
    public BlockTagNode(String name, Node content)
    {
    	blockName = name;
    	blockContent = content;
    }

    /**
     * Extracts the tag node from the parser.
     */
    public boolean initWithParser(Parser parser, TemplateLoader loader) throws ParserException
    {
    	Token token = parser.expectTokenInList(TokenLists.IDENT_OR_STRING_OR_CLOSETAG);
    	if (token.tokenType == TokenType.TOKEN_CLOSE_TAG)
    	{
    		blockName = null;
    	}
    	else 
    	{
    		blockName = token.tokenValue.toString();
    	}
    	blockContent = parser.parseTillNodeInList(loader, ENDBLOCK);
        return true;
    }

    /**
     * Compares specifically with another tag node.
     * We can safely assume that here another is neither this nor null.
     * @param another
     * @return true if objects are equal.
     */
    public boolean equalsTagNode(TagNode another)
    {
        if (!(another instanceof BlockTagNode))
            return false;

        BlockTagNode ftNode = (BlockTagNode)another;

        return ((blockContent != null && blockContent.equals(ftNode.blockContent)) ||
            (blockContent == ftNode.blockContent));
    }

    /**
     * Renders the for loop.
     */
    public Node renderBitMore(Writer writer, TemplateContext context, NodeContext currContext) throws IOException
    {
    	return blockContent;
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
}

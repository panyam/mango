package com.panyam.mango.templates.tags;

import java.io.*;

import java.util.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.utils.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.variables.*;


/**
 * Special variables to extract info about the for loops.
 * 
 * @author Sri Panyam
 */
class ForLoopVariable extends Variable
{
	/**
	 * Tells how many grandparents are we looking up.
	 * 0 Implies immediate parent.
	 */
	int parentCount;
	
	public ForLoopVariable()
	{
		parentCount = 0;
	}
	
	/**
	 * Does a bit of optimisation on the value of the "next" variable 
	 * by folding all parentloops into a counter.
	 */
    public Variable setNextVariable(String value, boolean isquoted)
    {
    	if (value.equals("parentloop"))
    	{
    		parentCount++;
    		return null;
    	}
    	return super.setNextVariable(value, isquoted);
    }
	
    public Object resolve(TemplateContext context, NodeContext currContext)
    {
    	// find the first ForLoop anywhere along the node context stack!!
    	int parentsLeft = parentCount;
    	NodeContext tempContext = currContext;
    	while (parentsLeft >= 0)
    	{
	    	while (tempContext != null && !(tempContext instanceof ForTagNodeContext))
	    		tempContext = tempContext.parent;
	    	if (tempContext != null)
	    	{
	    		parentsLeft--;
	    		if (parentsLeft >= 0)
	    			tempContext = tempContext.parent;
	    	}
    	}

    	if (tempContext != null && nextVar != null)
        {
            ForTagNodeContext ftnContext = (ForTagNodeContext)tempContext;
            if (nextVar.value().equals("counter"))
            {
                return ftnContext.getOneBasedCounter();
            }
            else if (nextVar.value().equals("counter0"))
            {
                return ftnContext.getCounter();
            }
            else if (nextVar.value().equals("first"))
            {
                return ftnContext.isFirst();
            }
            else if (nextVar.value().equals("last"))
            {
                return ftnContext.isLast();
            }
            return 0;
        }
        return null;
    }
}


class ForTagNodeContext extends NodeContext
{
    protected boolean isFirst;
    protected boolean isLast;
    protected int currIndex;
    protected boolean isEmpty;
    protected VariableIterator iterator;
    protected ArrayList<Object>				itemValues;

    public ForTagNodeContext(ForTagNode node, NodeContext parent) 
    {
        super(node, parent);
        setSource(null);
    }

    public void setSource(Object sourceObject)
    {
    	isEmpty = true;
        if (sourceObject != null)
        {
            isFirst = true;
            isLast = false;
            currIndex = 0;
            iterator = new VariableIterator(sourceObject);
            isEmpty = !iterator.hasNext();
        }
    }
    
    /**
     * Unpacks numValues values from the next value in the iterator and
     * returns the number of values unpacked.
     * @param numValues
     * @return
     */
    public int unpackValues(int numValues)
    {
    	if (iterator == null || !iterator.hasNext())
    	{
    		// reached the end of the line so return 0;
    		return 0;
    	}

    	if (itemValues == null)
    	{
    		isFirst = true;
    		currIndex = 0;
    		itemValues = new ArrayList<Object>();
    	}
    	else
    	{
    		isFirst = false;
    		currIndex++;
    	}

    	for (int i = 0, count = itemValues.size();i < count;i++)
    		itemValues.set(i, null);
    	for (int i = itemValues.size(); i < numValues;i++)
    		itemValues.add(null);
    	
    	int outCount = iterator.unpackValues(numValues, itemValues);

    	if (!iterator.hasNext())
    		isLast = true;

    	// clear the item values and reset them to null
        return outCount;
    }

    public boolean isFirst()
    {
        return isFirst;
    }

    public boolean isLast()
    {
        return isLast;
    }

    public int getCounter()
    {
        return currIndex;
    }

    public int getOneBasedCounter()
    {
        return currIndex + 1;
    }
}


/**
 * A tag for doing for loops.
 * Loops would be as:
 *
 * {% for (item1, item2, item3...itemn) in sourceVariable %}
 * {% empty %}
 * {% endfor %}
 * @author root
 */
public class ForTagNode extends TagNode
{
    protected ArrayList<Variable>   items;
    public Variable                 sourceVariable;
    /**
     * The child nodes for the this tag, since tags can have hierarchies.
     */
    public Node childNodes;
    public Node emptyNodes;

    private final static String []EMPTY_OR_ENDFOR = new String[] { "empty", "endfor" };
    private final static String []ENDFOR = new String[] { "endfor" };

    /**
     * Creates a ForTagNode directly without parsing from the input.
     */
    public ForTagNode()
    {
        this(null, null, null);
    }

    /**
     * Creates a ForTagNode directly without parsing from the input.
     */
    public ForTagNode(Variable sourceVar)
    {
        this(sourceVar, null, null);
    }

    /**
     * Creates a ForTagNode directly without parsing from the input.
     */
    public ForTagNode(Variable sourceVar, NodeList children)
    {
        this(sourceVar, children, null);
    }

    /**
     * Creates a ForTagNode directly without parsing from the input.
     */
    public ForTagNode(Variable sourceVar, NodeList children, NodeList empty)
    {
        sourceVariable = sourceVar;
        childNodes = children;
        emptyNodes = empty;
    }

    /**
     * Extracts the tag node from the parser.
     */
    public boolean initWithParser(Parser parser, TemplateLoader loader) throws ParserException
    {
        parseItemList(parser);
        parseSourceVariable(parser);
        parseTillEndTag(parser, loader);
        return true;
    }

    /**
     * Parse the list of items before the "in".
     */
    public void parseItemList(Parser parser) throws ParserException
    {
        // now read the tokens
        Token token = parser.expectTokenInList(TokenLists.IDENT_OR_OPEN_PAREN);
        if (token.tokenType == TokenType.TOKEN_OPEN_PAREN)
        {
            token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
            while (true)
            {
                String varValue = token.tokenValue.toString();
                Variable nextVar = new Variable(varValue, token.tokenType == TokenType.TOKEN_QUOTED_STRING, null);
                addItem(nextVar);
                token = parser.expectTokenInList(TokenLists.COMA_OR_CLOSE_PAREN);
                if (token.tokenType == TokenType.TOKEN_CLOSE_PAREN)
                    break ;
                else if (token.tokenType == TokenType.TOKEN_COMA)
                    token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
            }
        }
        else if (token.tokenType == TokenType.TOKEN_IDENTIFIER) 
        {
            String varValue = token.tokenValue.toString();
            Variable nextVar = new Variable(varValue, token.tokenType == TokenType.TOKEN_QUOTED_STRING, null);
            addItem(nextVar);
        }
        else
        {
            parser.throwError("Internal Error.  This case should have been caught by expectTokensInList");
        }
        
        // now read and discard the "in" token - we treat this just as an identifier
        token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
        if (!token.tokenValue.toString().equalsIgnoreCase("in"))
        {
            parser.throwError("Expected 'in', but found '" + token.tokenValue + "'");
        }
    }
    
    /**
     * 
     * @param parser
     */
    protected void parseSourceVariable(Parser parser) throws ParserException
    {
        sourceVariable = ParseUtils.parseVariable(parser);
        parser.expectToken(TokenType.TOKEN_CLOSE_TAG);
    }

    /**
     * Parses for the child nodes (and empty node) until the "endfor" is found.
     * @param parser
     */
    protected void parseTillEndTag(Parser parser, TemplateLoader loader) throws ParserException
    {
        childNodes = parser.parseTillNodeInList(loader, EMPTY_OR_ENDFOR);
        // see what the node name was if it was "empty" then read again
        Token token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
        String nodeName = token.tokenValue.toString(); 
        parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
        if (nodeName.equals("empty"))
        {
            // read till end-tag variable
            emptyNodes = parser.parseTillNodeInList(loader, ENDFOR);
            token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
            parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
        }
    }

    /**
     * Adds a new variable to the item list.
     * @param var
     */
    public void addItem(Variable var)
    {
        if (items == null)
            items = new ArrayList<Variable>();
        items.add(var);
    }

    /**
     * Compares specifically with another tag node.
     * We can safely assume that here another is neither this nor null.
     * @param another
     * @return true if objects are equal.
     */
    public boolean equalsTagNode(TagNode another)
    {
        if (!(another instanceof ForTagNode))
            return false;

        ForTagNode ftNode = (ForTagNode)another;
        
        if ((sourceVariable != null && sourceVariable.equals(ftNode.sourceVariable)) ||
            (sourceVariable == ftNode.sourceVariable))
        {
            return CompareUtils.IterablesEqual(items, ftNode.items) &&
            		CompareNodes(emptyNodes, ftNode.emptyNodes) && 
            			CompareNodes(childNodes, ftNode.childNodes); 
        }
        return false;
    }

    /**
     * Called when an instance of this tagnode is registered.
     * @param tagLib
     * @param instance
     */
    public static void onClassRegistered()
    {
        // now register the special variable class as well...
        // so the next time a forloop gets called it will do its magic
        // on the parent items.
        VariableLibrary.getSharedInstance().registerObjectClass("forloop", ForLoopVariable.class);
    }

    public NodeContext createNodeContext(TemplateContext context, NodeContext parentContext)
    {
    	ForTagNodeContext ftnContext = null;
    	if (sourceVariable != null && items != null)
    	{
        	ftnContext = new ForTagNodeContext(this, parentContext);
    		ftnContext.setSource(sourceVariable.resolve(context, parentContext));
    		
    		// push null values on the context stack for the variables referred by the items
			for (Iterator<Variable> iter = items.iterator(); iter.hasNext();)
			{
				Variable var = iter.next();
				context.pushValue(var.value(), null);
			}
    	}
    	return ftnContext;
    }

    /**
     * Renders the for loop.
     */
    public Node renderBitMore(Writer writer, TemplateContext context, NodeContext currContext) throws IOException
    {
    	if (currContext instanceof ForTagNodeContext)
    	{
    		ForTagNodeContext ftnContext = (ForTagNodeContext)currContext;
    	
    		// see if the context can unpack the number of values 
    		// as we have in the items array.
    		return nodeEntered(context, ftnContext, null);
    	}
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
		if (currContext instanceof ForTagNodeContext)
			return nodeEntered(context, (ForTagNodeContext)currContext, childNode);
		return null;
	}

	/**
     * "Enters" the node either from a parent node or a child node.
     * 
     * @param context
     * @param ftnContext
     * @param fromNode
     * @return
     */
    protected Node nodeEntered(TemplateContext context, ForTagNodeContext ftnContext, Node fromNode)
    {
    	if (ftnContext.isEmpty)
    	{
    		if (fromNode == null)
    			return emptyNodes;
    	}
    	else
    	{
	    	// update the values of all values in the items
			int numVariables = ftnContext.unpackValues(items.size()); 
			if (numVariables > 0)
			{
				// push all the values onto the context stack
				for (int i = 0, count = items.size();i < count;i++)
				{
					Object itemValue = ftnContext.itemValues.get(i);
					Variable var = items.get(i);
					context.setValue(var.value(), itemValue);
				}
				return childNodes;
			}
	
			// we are exiting the node so pop the values out of the context
			for (Iterator<Variable> iter = items.iterator(); iter.hasNext();)
			{
				Variable var = iter.next();
				context.popValue(var.value());
			}
    	}
		return null;
    }
}

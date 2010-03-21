package com.panyam.mango.templates.tags;

import java.io.*;
import java.util.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.core.expressions.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.utils.*;

/**
 * Node for rendering if/elseif/else nodes.
 * 
 * @author Sri Panyam
 */
public class IfTagNode extends TagNode 
{
	protected List<Expression>	expressions;
	protected List<Node>			ifNodes;
	protected Node 					elseNode;

    private final static String []ELSE_OR_ELSEIF_OR_ENDIF = new String[] { "else", "elseif", "endif" };
    private final static String []ENDIF = new String[] { "endif" };

	public IfTagNode() 
	{
		expressions = null;
		ifNodes = null;
		elseNode = null;
	}

    /**
     * Extracts an ifnode from the parser.
     *
     * The parser at this stage should have just read the "{{" and the "if"
     * tokens and will be pointing to the first part of the condition.
     * 
     * @param parser
     * @return
     * @throws ParserException
     */
    public boolean initWithParser(Parser parser, TemplateLoader loader) throws ParserException
    {
    	expressions = null;
    	ifNodes = null;
    	elseNode = null;

    	String nodeName = "";
    	do
    	{
            parser.getTokenizer().setCheckIdentifierOperators(true);
            Expression condition = ExpressionParser.parseExpression(parser);
            parser.getTokenizer().setCheckIdentifierOperators(false);
            parser.expectToken(TokenType.TOKEN_CLOSE_TAG);
            Node childNode = parser.parseTillNodeInList(loader, ELSE_OR_ELSEIF_OR_ENDIF);

            // read the name of the node
            Token token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
            nodeName = token.tokenValue.toString(); 

            addExpression(condition, childNode);
            if (nodeName.equals("else"))
            {
                parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
                elseNode = parser.parseTillNodeInList(loader, ENDIF);
                token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
                parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
            }
            else if (nodeName.equals("endif"))
            {
                parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
                // done parsing the node
            }
        } while (nodeName.equals("elseif"));

    	return true;
    }
    
	/**
	 * Add a conditional node.
	 * @param condition
	 * @param nodeList
	 */
	public void addExpression(Expression condition, Node node)
	{
		if (expressions == null)
		{
			expressions = new LinkedList<Expression>();
			ifNodes = new LinkedList<Node>();
		}
		expressions.add(condition);
		ifNodes.add(node);
	}
	
	public boolean equalsTagNode(TagNode another)
	{
        if (!(another instanceof IfTagNode))
            return false;

        IfTagNode itNode = (IfTagNode)another;
        if (Node.CompareNodes(elseNode, itNode.elseNode))
        {
        	return CompareUtils.IterablesEqual(expressions, itNode.expressions) &&
        			CompareUtils.IterablesEqual(ifNodes, itNode.ifNodes);
        }
        return false;
	}

    /**
     * Renders by returning the matching child node if any.
     */
    public Node renderBitMore(Writer writer, TemplateContext context, NodeContext currContext) throws IOException
    {
    	Iterator<Node> nodeIter = ifNodes.iterator();
    	Iterator<Expression> exprIter = expressions.iterator();
    	while (exprIter.hasNext())
    	{
    		Expression expr = exprIter.next();
    		Node node = nodeIter.next();
    		if (CompareUtils.IsTrue(ExpressionEvaluator.getDefaultEvaluator().evaluate(expr, context, currContext)))
    		{
    			return node;
    		}
    	}
    	return elseNode;
    }
}

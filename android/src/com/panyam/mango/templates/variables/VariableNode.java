package com.panyam.mango.templates.variables;

import java.io.IOException;
import java.io.Writer;
import java.util.*;

import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.utils.*;
import com.panyam.mango.templates.filters.*;
import com.panyam.mango.templates.core.*;

/**
 * Extracts a variable out of the parser.
 *
 * Variable Nodes have the following structure:
 *
 * VariableNode :=      OPEN_VARIABLE_NODE var_exp CLOSE_VARIABLE_NODE 
 *                  |   OPEN_VARIABLE_NODE var_exp filter_list CLOSE_VARIABLE_NODE 
 *                  ;
 *
 * var_exp  :=      ident
 *              |   ident DOT var_exp
 *              ;
 *
 * filter_list  := filter_exp
 *              |   filter_exp FILTER_SEPERATOR filter_list
 *              ;
 *
 * filter_exp   := ident 
 *              |  ident COLON ident
 *              |  ident COLON OPEN_PAREN filter_arg_list CLOSE_PAREN
 *              ;
 *
 * filter_arg_list  :=  ident 
 *                  |   ident COMA filter_arg_list
 *                  ;
 */
public class VariableNode extends Node
{
    protected Variable              variable;
    protected ArrayList<FilterNode> filterNodes;

    /**
     * Gets a variable node from a parser.
     */
    public VariableNode(Parser parser) throws ParserException
    {
        variable        = null;
        filterNodes     = null;
        parseVariableNode(parser);
    }
    
    /**
     * Creates a VariableNode by directly setting the variable and filters
     * instead of parsing.
     * 
     * @param variable
     * @param filters
     */
    public VariableNode(Variable variable)
    {
        this(variable, null);
    }
    
    /**
     * Creates a VariableNode by directly setting the variable and filters
     * instead of parsing.
     * 
     * @param variable
     * @param filters
     */
    public VariableNode(Variable variable, ArrayList<FilterNode> nodes)
    {
        this.variable = variable;
        this.filterNodes = nodes;
    }
    
    /**
     * Tells if this object is equal to another.
     */
    public boolean equals(Object another)
    {
        if (another == this)
            return true;
        if (another == null || !(another instanceof VariableNode))
            return false;
        VariableNode anotherVarNode = (VariableNode)another;
        if (!anotherVarNode.variable.equals(variable))
            return false;
        return CompareUtils.IterablesEqual(filterNodes, anotherVarNode.filterNodes);
    }

    /**
     * Reads the variable expression part of the node.
     * 
     * This is identifer ( DOT identifier ) *
     * 
     * @param parser
     */
    protected void parseVariableNode(Parser parser) throws ParserException
    {
        variable = ParseUtils.parseVariable(parser);
        // read the next token - it should be a close or a filter starter
        Token token = parser.peekToken();
        if (token.tokenType == TokenType.TOKEN_FILTER_SEPERATOR)
        {
            filterNodes = ParseUtils.parseFilterList(parser);
            token = parser.peekToken();
        }
        
        if (token == null || token.tokenType != TokenType.TOKEN_CLOSE_VARIABLE)
        {
            parser.throwError("Expected '}}', but found '" + (token == null ? "EOF" : token) + "'");
        }
        else
        {
            // otherwise read and discard the '}}'
            parser.getToken();
        }
    }
    
    /**
     * Adds a new filter node programmatically.
     * @param filterNode
     */
    public void addFilterNode(FilterNode filterNode)
    {
        if (filterNodes == null)
            filterNodes = new ArrayList<FilterNode>();
        filterNodes.add(filterNode);
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
    public Node renderBitMore(Writer writer, TemplateContext context, NodeContext currContext) throws IOException
	{
    	Object resolvedValue = variable.resolve(context, currContext);
    	if (resolvedValue != null)
    	{
    		if (filterNodes != null)
    		{
        		for (Iterator<FilterNode> iter = filterNodes.iterator();iter.hasNext();)
        		{
        			FilterNode filterNode = iter.next();
        			resolvedValue = filterNode.applyFilter(resolvedValue, context);
        		}
    		}
    		if (resolvedValue != null)
    			writer.write(resolvedValue.toString());
    	}
    	return null;
    }
}


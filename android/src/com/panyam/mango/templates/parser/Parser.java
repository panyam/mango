package com.panyam.mango.templates.parser;

import java.lang.reflect.InvocationTargetException;
import java.util.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.tags.*;
import com.panyam.mango.templates.variables.*;
import com.panyam.mango.templates.*;

public class Parser
{
    protected Tokenizer     	tokenizer       = null;
    protected Token         	currToken       = null;
    protected Token         	peekedToken     = null;
    protected Stack<String[]> 	endNodeStack    = new Stack<String[]>();

    // private final static TagNode endTagFoundNode = new TagNode();

    /**
     * Constructs a parser with a string input.
     */
    public Parser(Tokenizer tok)
    {
        this.tokenizer   = tok;
        this.currToken   = new Token();
    }

    /**
     * Gets the tokenizer used by the parser.
     * @return
     */
    public Tokenizer getTokenizer()
    {
    	return tokenizer;
    }
    
    /**
     * Creates an error with an error message.
     */
    public void throwError(String message) throws ParserException
    {
        throwError(-1, message);
    }

    /**
     * Creates an error with a code and error message.
     */
    public void throwError(int code, String message) throws ParserException
    {
    	throw new ParserException(code, message);
    }

    /**
     * Gets a token and throws an error if it doesnt match an expected token.
     * @param tokenType    The token type which we are expecting.
     * @return The extracted token if it matches the expected type.
     */
    public Token expectToken(TokenType tokenType) throws ParserException
    {
        return expectToken(tokenType, false);
    }

    /**
     * Gets a token and throws an error if it doesnt match an expected token.
     * @param tokenType    The token type which we are expecting.
     * @param peekOnly    Tells whether to only peek the token instead of extracting it.
     * @return The extracted token if it matches the expected type.
     */
    public Token expectToken(TokenType tokenType, boolean peekOnly) throws ParserException
    {
        Token token = getToken(peekOnly);
        if (token == null)
            throwError("Expected " + tokenType + " but found EOF instead!!");
        if (token.tokenType == TokenType.TOKEN_ERROR)
            throwError(token.tokenValue.toString());
        if (token.tokenType != tokenType)
            throwError("Expected " + tokenType + ", Found " + token.tokenType + " instead.");

        return token;
    }


    /**
     * Gets a token and throws an error if it doesnt match an expected token.
     * @param tokens    The list of tokens which we are ok with.
     * @return The extracted token if it matches the expected type.
     */
    public Token expectTokenInList(TokenType tokens[]) throws ParserException
    {
        return expectTokenInList(tokens, false);
    }

    /**
     * Gets a token and throws an error if it is not one of the expected token types.
     * @param tokens    The list of tokens which we are ok with.
     * @param peekOnly    Whether we are only peeking or extracting the token as well.
     * @return The extracted token if it matches the expected type.
     */
    public Token expectTokenInList(TokenType tokens[], boolean peekOnly) throws ParserException
    {
        Token token = getToken(peekOnly);
        if (token == null)
        {
       		throwError("Unexpected EOF. ");
        }
        
        if (token.tokenType == TokenType.TOKEN_ERROR)
        {
            throwError(token.tokenValue.toString());
        }
        
        for (int i = 0;i < tokens.length;i++)
        {
            if (token.tokenType == tokens[i])
                return token;
        }
        
        StringBuffer tokensString = new StringBuffer("");
        for (int i = 0;i < tokens.length;i++)
        {
            if (i != 0)
                tokensString.append(", ");
            tokensString.append("'" + tokens[i] + "'");
        }
        throwError("Expected one of [" + tokensString + "], Found " + token.tokenType + " instead.");
        return null;
    }

    /**
     * Peeks at the next token.
     * @return     The peeked token.
     */
    public Token peekToken() throws ParserException
    {
        return getToken(true);
    }

    /**
     * Gets the next token.
     * @return     The token extracted.
     */
    public Token getToken() throws ParserException
    {
        return getToken(false);
    }
    
    /**
     * Get the next token ignoring comments.
     */
    public Token getToken(boolean peekOnly) throws ParserException
    {
        // do we have a cached token?
        if (peekedToken != null)
        {
            Token out = peekedToken;
            if (!peekOnly)
            {
                // clear the peeked token so next time we do a clean extract
                peekedToken = null;
            }
            return out;
        }

        boolean result;
        do
        {
            result = tokenizer.nextToken(currToken);
        } while (result && currToken.tokenType == TokenType.TOKEN_COMMENT);

        if (!result)    // EOF
            return null;

        // check errors:
        /*
        if (currToken.tokenType == TokenType.TOKEN_ERROR)
        {
            throwError(currToken.tokenValue.toString());
            // handle error somehow
            return null;
        }
        */

        // if we are peeking then save the peeked token
        if (peekOnly)
            peekedToken = currToken;

        return currToken;
    }

    /**
     * Discards tokens till a particular token.
     * @param lastToken
     */
    public void discardTokensTill(TokenType lastToken) throws ParserException
    {
    	Token token = getToken();
    	while (token.tokenType != lastToken)
    		token = getToken();
    }
    
    /**
     * Parses the entire input and returns a parse tree.
     */
    public Node parse(TemplateLoader loader) throws ParserException
    {
    	LinkedList<Node> nodeList = null;
    	Node firstNode = null;
        Node nextNode  = parseNode(loader);
        int nodeCount = 0;
        while (nextNode != null)
        {
        	if (firstNode == null)
        	{
        		firstNode = nextNode;
        	}
        	else
        	{
	        	if (nodeList == null)
	        	{
	        		nodeList = new LinkedList<Node>();
	        		nodeList.add(firstNode);
	        	}
	        	nodeList.add(nextNode);
        	}
        	nodeCount++;
            nextNode  = parseNode(loader);
        }

        // just an optimisation to directly return a node if 
        // there is only one item instead of a node list
        if (nodeCount <= 1)
        {
        	return firstNode;
        }
        else
        {
        	return new NodeList(nodeList);
        }
    }

    /**
     * Reads the next node whether it be a freetext node, a variable node 
     * or a tag node and returns it.  If no more nodes are left or an error 
     * was found, then a null is returned.
     */
    public Node parseNode(TemplateLoader loader) throws ParserException
    {
        Token token = getToken();
        if (token != null)
        {
            if (token.tokenType == TokenType.TOKEN_FREETEXT)
            {
                // easy
                return new FreeTextNode(token.tokenValue.toString());
            }
            else if (token.tokenType == TokenType.TOKEN_OPEN_VARIABLE)
            {
                return new VariableNode(this);
            }
            else if (token.tokenType == TokenType.TOKEN_OPEN_TAG)
            {
            	// see if the tag is part of the end node stack
            	if (!endNodeStack.empty())
            	{
            		token = expectToken(TokenType.TOKEN_IDENTIFIER, true);
            		String []nameList = endNodeStack.peek(); 
            		for (int i = 0;nameList[i] != null;i++)
            		{
            			if (nameList[i].equals(token.tokenValue.toString()))
            			{
            				// we are at an end tag so pop the endtag list and return an endtag indicator
            				endNodeStack.pop();
            				return null;
            			}
            		}
            	}
            	// its a normal (non-end) tag so extract it as usual
            	try
            	{
            		return TagNode.extractWithParser(this, loader);
            	} catch (InvocationTargetException ite)
            	{
            		Throwable target = ite.getTargetException();
            		if (target instanceof ParserException)
            			throw (ParserException)target;
            		else
                		ite.printStackTrace();
            		String message = target.getMessage();
                    throwError(message);
            	}
            }
            throwError(-1, "Invalid token found: " + token.tokenType);
        }
        return null;
    }
    
    /**
     * This is called by a TagNode (or its derivative) to parse "upto" a certain 
     * tag node in the input stream.  For example in a "for loop" node, after reading
     * the initial {% for x in blah %}, the tag will want to read everything upto 
     * an "empty" or "endfor" node and store the resulting nodes as child nodes.
     * So for this the parser must be handed back control to read upto that point.
     * This function does that.
     * Also this itself can be recursive, so if there is a forloop inside a forloop,
     * then the first empty (or end) node that is encountered must be given to the 
     * second forloop and not the first one.
     * 
     * @param nodeList
     * @return
     */
    public Node parseTillNodeInList(TemplateLoader loader, String []nameList) throws ParserException
    {
    	int stackSize = endNodeStack.size();
    	endNodeStack.push(nameList);
    	Node parsedNodes = parse(loader);
    	if (stackSize != endNodeStack.size())	// if the end node was not popped the sizes wont match!
    		throwError("End nodes were not found");
    	return parsedNodes;
    }
}


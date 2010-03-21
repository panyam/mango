package com.panyam.mango.templates.utils;

import java.util.ArrayList;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.filters.*;
import com.panyam.mango.templates.variables.*;

/**
 * Utility class for parsing standard things.
 * 
 * @author Sri Panyam
 */
public final class ParseUtils 
{
    /**
     * Parse a variable expression.
     * @param parser
     * @return
     */
    public static Variable parseVariable(Parser parser) throws ParserException
    {
        Variable firstVar = null;
        Variable lastVar = null;
        Token token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
        while (true)
        {
            String varValue = token.tokenValue.toString();
            boolean isQuoted = token.tokenType == TokenType.TOKEN_QUOTED_STRING;
            if (firstVar == null)
            {
            	// see if the variable library returns a "special" variable
                Variable nextVar = isQuoted ? null : VariableLibrary.getSharedInstance().makeNewInstance(varValue);
                if (nextVar == null)
                {
                    nextVar = new Variable(varValue, isQuoted);
                }
                firstVar = lastVar = nextVar;
            }
            else
            {
            	Variable nextVar = lastVar.setNextVariable(varValue, isQuoted);
            	if (nextVar != null)
            	{
                    lastVar = nextVar;
            	}
            }
            
            // peek at the next token...
            token = parser.peekToken();
            if (token != null && token.tokenType == TokenType.TOKEN_DOT)
            {
                parser.getToken();    // discard the DOT
                token = parser.expectTokenInList(TokenLists.IDENT_OR_STRING);
            }
            else
            {
                break ;
            }
        }
        return firstVar;
    }

    /**
     * Parses a filter including the final }} which indicates the end of the variable node.
     * @param parser
     */
    public static ArrayList<FilterNode> parseFilterList(Parser parser) throws ParserException
    {
        ArrayList<FilterNode> output = null;
        Token token = parser.peekToken();
        while (token.tokenType == TokenType.TOKEN_FILTER_SEPERATOR)
        {
            parser.getToken();    // Discard the '|'
            FilterNode filterNode = parseFilterExpression(parser);
            if (output == null)
                output = new ArrayList<FilterNode>();
            output.add(filterNode);
            token = parser.peekToken();
        }
        return output;
    }
    
    /**
     * Parses each filter expression in the filter list.  This assumes that the next 
     * token being read will be an identifier indicating the name of the filter.
     * 
     * Filter expressions are of the form:
     * ident
     * ident COLON value
     * ident COLON OPEN_PAREN value_list CLOSE_PAREN
     * @param parser
     */
    public static FilterNode parseFilterExpression(Parser parser) throws ParserException
    {
        Token token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
        String filterName = token.tokenValue.toString();
        Filter filter = FilterLibrary.getSharedInstance().makeNewInstance(filterName);
        if (filter == null)
            parser.throwError("Filter not found: " + filterName);
        FilterNode newFilter = new FilterNode(filter);

        token = parser.peekToken();

        if (token != null && token.tokenType == TokenType.TOKEN_COLON)
        {
            // consume the token
            parser.getToken();
            parseFilterArguments(parser, newFilter);
        }
        return newFilter;
    }

    /**
     * Parses the arguments of a filter expression.  This assumes that next token
     * that will be read is either a "(" or a variable.
     * @param parser
     */
    public static void parseFilterArguments(Parser parser, FilterNode filterNode) throws ParserException
    {
        // now read the tokens
        Token token = parser.expectTokenInList(TokenLists.IDENT_STRING_OR_OPEN_PAREN);
        if (token.tokenType == TokenType.TOKEN_OPEN_PAREN)
        {
            token = parser.expectTokenInList(TokenLists.IDENT_OR_STRING);
            while (true)
            {
                String varValue = token.tokenValue.toString();
                Variable nextVar = new Variable(varValue, token.tokenType == TokenType.TOKEN_QUOTED_STRING, null);
                filterNode.addArgument(nextVar);
                token = parser.expectTokenInList(TokenLists.COMA_OR_CLOSE_PAREN);
                if (token.tokenType == TokenType.TOKEN_CLOSE_PAREN)
                    break ;
                else if (token.tokenType == TokenType.TOKEN_COMA)
                    token = parser.expectTokenInList(TokenLists.IDENT_OR_STRING);
            }
        }
        else if (token.tokenType == TokenType.TOKEN_IDENTIFIER || 
                token.tokenType == TokenType.TOKEN_QUOTED_STRING)
        {
            String varValue = token.tokenValue.toString();
            Variable nextVar = new Variable(varValue, token.tokenType == TokenType.TOKEN_QUOTED_STRING, null);
            filterNode.addArgument(nextVar);
        }
        else
        {
            parser.throwError("Internal Error.  This case should have been caught by expectTokensInList");
        }
    }
}

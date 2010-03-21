/**
 * 
 */
package com.panyam.mango.templates.test;

import junit.framework.TestCase;

import java.io.*;
import java.util.*;
import com.panyam.mango.templates.parser.*;

/**
 * 
 * 
 * @author root
 *
 */
public class TokenizerTests extends TestCase 
{
    class ExpectedToken
    {
        public TokenType tokenType;
        public String          tokenValue;

        public ExpectedToken(TokenType tType, String tValue)
        {
            tokenType = tType;
            tokenValue = tValue;
        }
    }

    Vector<ExpectedToken>   expectedTokens;
    Tokenizer               tokenizer;

    /**
     * @param name
     */
    public TokenizerTests(String name) {
        super(name);
    }

    /* (non-Javadoc)
     * @see junit.framework.TestCase#setUp()
     */
    protected void setUp() throws Exception {
        super.setUp();
	    expectedTokens = new Vector<ExpectedToken>();
    }

    /* (non-Javadoc)
     * @see junit.framework.TestCase#tearDown()
     */
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    /**
     * Sets up the tokenizer with an input string.
     */
    protected void setUpWithInputString(String input)
    {
	    tokenizer = new Tokenizer(new BufferedReader(new StringReader(input)));
    }

    protected void expectToken(TokenType type, String value)
    {
        ExpectedToken expectedToken = new ExpectedToken(type, value);
        expectedTokens.add(expectedToken);
    }

    protected void satisfyExpectation(int expectation)
    {
    	Token token = new Token();
        assertTrue("No tokens left, but expectations left.", tokenizer.hasTokensAvailable());
        boolean foundToken = tokenizer.nextToken(token);
        assertTrue("No tokens left, but expectations left.", foundToken);
        ExpectedToken expectedToken = expectedTokens.elementAt(expectation);
        assertTrue("Expectation: " + expectation + 
        			", Expected TokenType: " + expectedToken.tokenType + 
        			", But Found: " + token.tokenType, 
                     expectedToken.tokenType == token.tokenType);
        if (expectedToken.tokenValue != null)
        {
        	String expectedTokenValue = expectedToken.tokenValue;
        	String tokenValue = token.tokenValue.toString();
            assertEquals("Expectation: " + expectation + 
            			", Expected TokenValue: <" + expectedToken.tokenValue + ">" + 
            			", But Found: <" + token.tokenValue + ">",
            			expectedTokenValue, tokenValue);
        }
    }

    /**
     * Goes through the expectations and ensures that all expectations
     * on the tokens extracted are satisfied.
     */
    protected void satisfyExpectations()
    {
        for (int expectation = 0, numExpectations = expectedTokens.size();
            expectation < numExpectations; ++expectation)
        {
        	satisfyExpectation(expectation);
        }
    }

    /**
     * Tests the creation of a tokenizer.
     */
    public void testTokenizerCreate()
    {
    }

    /**
     * test case to see if an empty string returns an EOF token
     */
    public void testEmptyTokenizer()
    {
        setUpWithInputString("");
        satisfyExpectations();
    }


    /**
     * test case to see if an empty string returns an EOF token
     */
    public void testOnlyFreeText()
    {
        setUpWithInputString("Hello World");
        expectToken(TokenType.TOKEN_FREETEXT, "Hello World");
        satisfyExpectations();
    }


    public void testEmptyCommentOnly()
    {
        setUpWithInputString("{##}");
        expectToken(TokenType.TOKEN_COMMENT, null);
        satisfyExpectations();
    }

    public void testOnlyComments()
    {
        setUpWithInputString("{#A comment#}");
        expectToken(TokenType.TOKEN_COMMENT, null);
        satisfyExpectations();
    }

    public void testCommentsWithSpaces()
    {
        setUpWithInputString("{#   A comment  with spaces  #}");
        expectToken(TokenType.TOKEN_COMMENT, null);
        satisfyExpectations();
    }


    public void testMultiLineComments()
    {
        setUpWithInputString("{#   A comment  \nwith \nspaces  #}");
        expectToken(TokenType.TOKEN_COMMENT, null);
        satisfyExpectations();
    }

    public void testCommentsBetweenText()
    {
        setUpWithInputString("Part1OfText{#TheComment#}Part2OfText");
        expectToken(TokenType.TOKEN_FREETEXT, "Part1OfText");
        expectToken(TokenType.TOKEN_COMMENT, null);
        expectToken(TokenType.TOKEN_FREETEXT, "Part2OfText");
        satisfyExpectations();
    }

    public void testUnterminatedComments()
    {
        setUpWithInputString("{#This comment has no close token");
        expectToken(TokenType.TOKEN_ERROR, null);
        satisfyExpectations();
    }


    // tests empty nodes
    public void testEmptyNodes()
    {
        setUpWithInputString("{{}}{%%}{##}");
        expectToken(TokenType.TOKEN_OPEN_VARIABLE, null);
        expectToken(TokenType.TOKEN_CLOSE_VARIABLE, null);
        expectToken(TokenType.TOKEN_OPEN_TAG, null);
        expectToken(TokenType.TOKEN_CLOSE_TAG, null);
        expectToken(TokenType.TOKEN_COMMENT, null);
        satisfyExpectations();
    }



    // tests to do with variables and tags
    public void testSingleVariable()
    {
        setUpWithInputString("{{variable}}");
        expectToken(TokenType.TOKEN_OPEN_VARIABLE, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "variable");
        expectToken(TokenType.TOKEN_CLOSE_VARIABLE, null);
        satisfyExpectations();
    }

    // tests to do with variables and tags
    public void testSingleVariableWithSpaces()
    {
        setUpWithInputString("{{ variable }}");
        expectToken(TokenType.TOKEN_OPEN_VARIABLE, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "variable");
        expectToken(TokenType.TOKEN_CLOSE_VARIABLE, null);
        satisfyExpectations();
    }

    // tests to do with variables and tags
    public void testMultipleIdentifiers()
    {
        setUpWithInputString("{{ abc  de f }}");
        expectToken(TokenType.TOKEN_OPEN_VARIABLE, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "abc");
        expectToken(TokenType.TOKEN_IDENTIFIER, "de");
        expectToken(TokenType.TOKEN_IDENTIFIER, "f");
        expectToken(TokenType.TOKEN_CLOSE_VARIABLE, null);
        satisfyExpectations();
    }


    public void testMultipleTokensInNode()
    {
        setUpWithInputString("{{ a . b . c. d | filter:( a, b, c) }}");
        expectToken(TokenType.TOKEN_OPEN_VARIABLE, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "a");
        expectToken(TokenType.TOKEN_DOT, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "b");
        expectToken(TokenType.TOKEN_DOT, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "c");
        expectToken(TokenType.TOKEN_DOT, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "d");
        expectToken(TokenType.TOKEN_FILTER_SEPERATOR, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "filter");
        expectToken(TokenType.TOKEN_COLON, null);
        expectToken(TokenType.TOKEN_OPEN_PAREN, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "a");
        expectToken(TokenType.TOKEN_COMA, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "b");
        expectToken(TokenType.TOKEN_COMA, null);
        expectToken(TokenType.TOKEN_IDENTIFIER, "c");
        expectToken(TokenType.TOKEN_CLOSE_PAREN, null);
        // expectToken(TokenType.TOKEN_ERROR, null);
        expectToken(TokenType.TOKEN_CLOSE_VARIABLE, null);
        satisfyExpectations();
    }
    
    public void testTwoEmptyTags()
    {
        setUpWithInputString("{% %}{% %}");
        expectToken(TokenType.TOKEN_OPEN_TAG, null);
        expectToken(TokenType.TOKEN_CLOSE_TAG, null);
        expectToken(TokenType.TOKEN_OPEN_TAG, null);
        expectToken(TokenType.TOKEN_CLOSE_TAG, null);
        satisfyExpectations();
    }
    
    public void testFreeTextThenTag()
    {
        setUpWithInputString("Hello World{% %}");
        expectToken(TokenType.TOKEN_FREETEXT, null);
        expectToken(TokenType.TOKEN_OPEN_TAG, null);
        expectToken(TokenType.TOKEN_CLOSE_TAG, null);
        satisfyExpectations();
    }
    
    public void testCheckIdentifierOperators()
    {
    	setUpWithInputString("{{ in in and and }}");
    	expectToken(TokenType.TOKEN_OPEN_VARIABLE, null);
    	expectToken(TokenType.TOKEN_IDENTIFIER, "in");
        satisfyExpectations();

        tokenizer.setCheckIdentifierOperators(true);
    	expectToken(TokenType.TOKEN_IN, null);
        satisfyExpectation(2);

        tokenizer.setCheckIdentifierOperators(false);
    	expectToken(TokenType.TOKEN_IDENTIFIER, "and");
        satisfyExpectation(3);

        tokenizer.setCheckIdentifierOperators(true);
    	expectToken(TokenType.TOKEN_AND, null);
        satisfyExpectation(4);
    }
}


package com.panyam.mango.templates.parser;

public enum TokenType {
    TOKEN_UNKNOWN,
    TOKEN_ERROR,
    TOKEN_EOF,						
    TOKEN_FREETEXT,
    TOKEN_QUOTED_STRING,
    TOKEN_IDENTIFIER,				
    TOKEN_COMMENT,					// {# ... #}
    TOKEN_OPEN_VARIABLE,			// {{
    TOKEN_CLOSE_VARIABLE,			// }}
    TOKEN_OPEN_TAG,					// {%
    TOKEN_CLOSE_TAG,				// %}

    TOKEN_DOT,						// "."
    TOKEN_FILTER_SEPERATOR,         // "|"
    TOKEN_COLON,                    // ":"
    TOKEN_COMA,						// ","
    TOKEN_OPEN_PAREN,				// "("
    TOKEN_CLOSE_PAREN,				// ")"
    TOKEN_LT,						// "<"
    TOKEN_LE,						// <=
    TOKEN_GT,						// ">"
    TOKEN_GE,						// ">="
    TOKEN_EQ,						// "=="
    TOKEN_NE,						// "!="
    TOKEN_IN,						// "in"
    TOKEN_AND,						// "and"
    TOKEN_OR,						// "or"
    TOKEN_NOT,						// "not"
    TOKEN_LAST;						// last one - do not use or add after this

    /*
    private final int precedence;
    
    TokenType(int precedence)
    {
    	this.precedence = precedence;
    }
    
    TokenType()
    {
    	this(0);
    }
    
    public int precedence()
    {
    	return precedence;
    }
    */
}


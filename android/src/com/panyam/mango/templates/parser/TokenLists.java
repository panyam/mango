package com.panyam.mango.templates.parser;

/**
 * A few set token lists which are used through out the parsing stages.
 */
public class TokenLists
{
    /**
     * Expected token list for identifier or string only.
     */
    public static final TokenType COLON_OR_CLOSE_VARIABLE[] = new TokenType[] {
            TokenType.TOKEN_COLON, 
            TokenType.TOKEN_CLOSE_VARIABLE,
    };

    /**
     * Expected token list for identifier or string only.
     */
    public static final TokenType IDENT_OR_STRING[] = new TokenType[] {
            TokenType.TOKEN_IDENTIFIER, 
            TokenType.TOKEN_QUOTED_STRING,
    };

    /**
     * Tokens that can be expected when reading the variable name expression.
     */
    public static final TokenType IDENT_OR_OPEN_PAREN[] = new TokenType[] {
            TokenType.TOKEN_IDENTIFIER, 
            TokenType.TOKEN_OPEN_PAREN,
    };

    /**
     * Tokens that can be expected when reading the variable name expression.
     */
    public static final TokenType IDENT_STRING_OR_OPEN_PAREN[] = new TokenType[] {
            TokenType.TOKEN_IDENTIFIER, 
            TokenType.TOKEN_QUOTED_STRING,
            TokenType.TOKEN_OPEN_PAREN,
    };

    /**
     * Tokens that can be expected when reading the variable name expression.
     */
    public static final TokenType COMA_OR_CLOSE_PAREN[] = new TokenType[] {
            TokenType.TOKEN_COMA,
            TokenType.TOKEN_CLOSE_PAREN,
    };
    
    /**
     * Tokens that can be expected when reading the variable name expression.
     */
    public static final TokenType IDENT_TOKENS[] = new TokenType[] {
            TokenType.TOKEN_DOT, 
            TokenType.TOKEN_CLOSE_VARIABLE,
            TokenType.TOKEN_FILTER_SEPERATOR
    };
    
    /**
     * Tokens that can be expected when reading filter lists.
     */
    public static final TokenType FILTER_LIST_TOKENS[] = new TokenType[] {
            TokenType.TOKEN_CLOSE_VARIABLE,
            TokenType.TOKEN_FILTER_SEPERATOR
    };
}


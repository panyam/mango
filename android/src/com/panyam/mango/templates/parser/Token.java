package com.panyam.mango.templates.parser;

public class Token {
    public TokenType tokenType;
    public StringBuffer tokenValue;
    
    private static final Token EOF_TOKEN    = new Token(TokenType.TOKEN_EOF, null);
    /**
     * Returns the EOF token.
     * @return
     */
    public static Token EOFToken()
    {
        return EOF_TOKEN;
    }
    
    /**
     * Creates an empty token.
     */
    public Token()
    {
        this(TokenType.TOKEN_UNKNOWN, null);
    }
    
    /**
     * Creates an empty token.
     */
    public Token(TokenType tType)
    {
        this(tType, null);
    }

    /**
     * Creates the token.
     */
    public Token(TokenType tType, String value)
    {
        tokenType = tType;
        setTokenValue(value);
    }
    
    /**
     * Sets the value of the token.
     * @param value String to set as the value of the token.
     */
    public void setTokenValue(String value)
    {
        if (value == null)
            value = "";
        tokenValue = new StringBuffer(value);
    }
    
    /**
     * Appends text to the token value.
     * @param value    String to be appended
     */
    public void appendToToken(String value)
    {
        tokenValue.append(value);
    }
    
    /**
     * Appends a single character to the string.
     * @param chValue
     */
    public void appendCharToToken(int chValue)
    {
        tokenValue.append((char)chValue);
    }
    
    public String toString()
    {
        return "(" + tokenType + "," + tokenValue + ")";
    }
}

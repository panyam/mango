package com.panyam.mango.templates.parser;
import java.io.*;

/**
 * Tokenizes an input stream and returns tokens one at a time.
 * 
 * @author Sri Panyam
 */
public class Tokenizer 
{
    protected enum NodeType
    {   
        NODETYPE_NONE,
        NODETYPE_COMMENT,
        NODETYPE_VARIABLE,
        NODETYPE_TAG
    };

    /**
     * Input stream that will be tokenized.
     */
    protected BufferedReader inputReader;
    
    // Tells which node the tokenizer is inside.
    protected NodeType    insideNode;
    protected int        nodeEndChar;        // character that will end the node
    protected    TokenType        nodeCloseToken;        // token that should be read for a node close
    protected     boolean     insideQuotes;        // are we inside a quoted string?
    protected     boolean     insideIdentifier;    // whether we are reading an identifier
    protected     int        quoteType;          // single or double

    // Current input buffer read from the input stream
    protected static final    int MAX_PUSHED_CHARS = 64;
    protected int[]         pushedChars    = new int[MAX_PUSHED_CHARS];
    protected int         pushedCharsLen;
    protected int         currLine;
    protected int         currColumn;
    protected boolean    checkReservedWords;
    
    /**
     * Creates a tokenizer with an input stream.
     * @param stream    Input stream from which the tokens will be scanned.
     */
    public Tokenizer(BufferedReader reader)
    {
        setReader(reader);
    }
    
    /**
     * Sets the input stream that will be tokenized.
     * @param stream
     */
    public void setReader(BufferedReader reader)
    {
        inputReader             = reader;
        insideNode              = NodeType.NODETYPE_NONE;
        insideQuotes            = false;
        insideIdentifier        = false;
        pushedCharsLen          = 0;
        currLine                = 0;
        currColumn              = 0;
    }
    
    /**
     * true if there are more tokens.
     * @return true if more tokens are available, false otherwise.
     */
    public boolean hasTokensAvailable()
    {
        if (pushedCharsLen > 0)
            return true;
        // try doing a read then
        try
        {
            int nextChar = inputReader.read();
            ungetChar(nextChar);
            return true;
        }
        catch (EOFException eofExc)
        {
        }
        catch (IOException ioExc)
        {
        }
        return false;
    }
    
    /**
     * Returns whether operators like "in", "and", "or" and "not" should be 
     * returned as their own type or as identifiers.
     */
    public boolean checkReservedWords()
    {
        return checkReservedWords;
    }

    /**
     * Sets whether operators like "in", "and", "or" and "not" should be 
     * returned as their own type or as identifiers.
     * @param check
     */
    public void setCheckReservedWords(boolean check)
    {
        checkReservedWords = check;
    }

    /**
     * Scans for the next token.
     * 
     * @param token    The token which gets filled.
     * @return true if a token was found, false if eof.
     */
    public boolean nextToken(Token token)
    {
        token.tokenType = TokenType.TOKEN_UNKNOWN;
        token.setTokenValue("");
        
        int char1 = nextChar();
        while (char1 >= 0)
        {
            if (insideNode == NodeType.NODETYPE_NONE)
            {
                // we are doing free text
                if (char1 == '{')
                {
                    // starting a node, variable or comment
                    int char2 = nextChar();
                    nodeEndChar = char2;
                    if (char2 == '#')
                    {
                        insideNode = NodeType.NODETYPE_COMMENT;
                        token.tokenType = TokenType.TOKEN_COMMENT;
                    }
                    else if (char2 == '{')
                    {
                        nodeEndChar = '}';
                        insideNode = NodeType.NODETYPE_VARIABLE;
                        nodeCloseToken = TokenType.TOKEN_CLOSE_VARIABLE;
                        token.tokenType = TokenType.TOKEN_OPEN_VARIABLE;
                    }
                    else if (char2 == '%')
                    {
                        insideNode = NodeType.NODETYPE_TAG;
                        nodeCloseToken = TokenType.TOKEN_CLOSE_TAG;
                        token.tokenType = TokenType.TOKEN_OPEN_TAG;
                    }

                    // we have reached a node and freetext is not empty
                    // then return it
                    if (insideNode != NodeType.NODETYPE_NONE)
                    {
                        if (token.tokenValue.length() > 0)
                        {
                            // push the two characters back
                            // so they can be read again
                            ungetChar(char2);
                            ungetChar(char1);
                            insideNode = NodeType.NODETYPE_NONE;
                            token.tokenType = TokenType.TOKEN_FREETEXT;
                            return true;
                        }
                        else if (insideNode != NodeType.NODETYPE_COMMENT)
                        {
                            // return the node start token
                            return true;
                        }
                    }
                    else
                    {
                        // nothing so append to buffer and continue
                        token.appendCharToToken(char1);
                        if (char2 >= 0)
                            token.appendCharToToken(char2);
                    }
                }
                else
                {
                    // append to freetext buffer
                    token.appendCharToToken(char1);
                }
            }
            else if (insideNode == NodeType.NODETYPE_COMMENT)
            {
                // skip everything until the end of comment
                if (char1 == '#')
                {
                    int char2 = nextChar();
                    if (char2 == '}')
                    {
                        token.tokenType = TokenType.TOKEN_COMMENT;
                        insideNode = NodeType.NODETYPE_NONE;
                        return true;
                    }
                }
            }
            else
            {
                // we are inside a node, now quoted strings, dots and all are
                // significant
                if (insideQuotes)
                {
                    if (char1 == quoteType)
                    {
                        // finished quotes
                        insideQuotes = false;
                        return true;
                    }
                    else
                    {
                        if (char1 == '\\')
                        {
                            char1 = nextChar();
                            if (char1 == '\n')
                            {
                                token.appendCharToToken('\n');
                            }
                            else if (char1 == '\r')
                            {
                                token.appendCharToToken('\r');
                            }
                            else if (char1 == '\t')
                            {
                                token.appendCharToToken('\t');
                            }
                            else if (char1 == '\'')
                            {
                                token.appendCharToToken('\'');
                            }
                            else if (char1 == '"')
                            {
                                token.appendCharToToken('"');
                            }
                            else if (char1 == 'f')
                            {
                                token.appendCharToToken('\f');
                            }
                            else if (char1 == 'u')
                            {
                                throw new IllegalArgumentException("Cannot yet do unicode.");
                            }
                            else if (char1 < 0)
                            {
                                token.tokenType = TokenType.TOKEN_ERROR;
                                return false;
                            }
                            else
                            {
                                token.appendCharToToken('\\');
                                token.appendCharToToken(char1);
                            }
                        }
                        else
                        {
                            token.appendCharToToken(char1);
                        }
                    }
                }
                else if (insideIdentifier)
                {
                    if (Character.isLetterOrDigit(char1) || char1 == '_')
                    {
                        token.appendCharToToken(char1);
                    }
                    else
                    {
                        // finished identifier
                        token.tokenType = TokenType.TOKEN_IDENTIFIER;
                        insideIdentifier = false;
                        ungetChar(char1);
                        
                        // check for specific identifiers:
                        if (checkReservedWords)
                        {
                            String ident = token.tokenValue.toString();
                            if (ident.equals("not"))
                            {
                                token.tokenType = TokenType.TOKEN_NOT;
                            }
                            else if (ident.equals("and"))
                            {
                                token.tokenType = TokenType.TOKEN_AND;
                            }
                            else if (ident.equals("or"))
                            {
                                token.tokenType = TokenType.TOKEN_OR;
                            }
                            else if (ident.equals("in"))
                            {
                                token.tokenType = TokenType.TOKEN_IN;
                            }
                        }
                        return true;
                    }
                }
                else if (char1 == '"' || char1 == '\'')
                {
                    // inside quotes everything else is secondary
                    quoteType           = char1;
                    insideQuotes        = true;
                    token.tokenType    = TokenType.TOKEN_QUOTED_STRING;
                }
                else if (Character.isLetterOrDigit(char1) || char1 == '_')
                {
                    ungetChar(char1);
                    insideIdentifier    = true;
                    token.tokenType    = TokenType.TOKEN_IDENTIFIER;
                }
                else if (Character.isWhitespace(char1))
                {
                    // do nothing - skip spaces
                }
                else if (char1 == '.')
                {
                    token.tokenType = TokenType.TOKEN_DOT;
                    return true;
                }
                else if (char1 == '|')
                {
                    token.tokenType = TokenType.TOKEN_FILTER_SEPERATOR;
                    return true;
                }
                else if (char1 == ',')
                {
                    token.tokenType = TokenType.TOKEN_COMA;
                    return true;
                }
                else if (char1 == '|')
                {
                    token.tokenType = TokenType.TOKEN_FILTER_SEPERATOR;
                    return true;
                }
                else if (char1 == ':')
                {
                    token.tokenType = TokenType.TOKEN_COLON;
                    return true;
                }
                else if (char1 == '(')
                {
                    token.tokenType = TokenType.TOKEN_OPEN_PAREN;
                    return true;
                }
                else if (char1 == ')')
                {
                    token.tokenType = TokenType.TOKEN_CLOSE_PAREN;
                    return true;
                }
                else if (char1 == nodeEndChar)
                {
                    // coming out of a node
                    int char2 = nextChar();
                    if (char2 == '}')
                    {
                        token.tokenType = nodeCloseToken;
                        insideNode = NodeType.NODETYPE_NONE;
                        return true;
                    }
                    else
                    {
                        ungetChar(char2);
                    }
                }
                else if (char1 == '<' || char1 == '>')
                {
                    int char2 = nextChar();
                    if (char2 == '=')
                    {
                        token.tokenType = char1 == '<' ? TokenType.TOKEN_LE : TokenType.TOKEN_GE;
                    }
                    else
                    {
                        ungetChar(char2);
                        token.tokenType = char1 == '<' ? TokenType.TOKEN_LT : TokenType.TOKEN_GT;
                    }
                    return true;
                }
                else if (char1 == '!' || char1 == '=')
                {
                    int char2 = nextChar();
                    if (char2 == '=')
                    {
                        token.tokenType = char1 == '!' ? TokenType.TOKEN_NE : TokenType.TOKEN_EQ;
                        return true;
                    }
                    return false;
                }
                else
                {
                    throw new IllegalArgumentException("Invalid character: " + char1 + " - " + (char)char1);
                }
            }
            char1 = nextChar();
        }

        if (insideIdentifier)
        {
            // we were reading an identifier so return it first
            insideIdentifier = false;
            return true;
        }

        token.tokenType = TokenType.TOKEN_EOF;
        if (insideNode == NodeType.NODETYPE_NONE)
        {
            if (token.tokenValue.length() > 0)
            {
                token.tokenType = TokenType.TOKEN_FREETEXT;
                return true;
            }
        }
        else
        {
            // return unterminated node
            token.tokenType = TokenType.TOKEN_ERROR;
            token.setTokenValue("Reached EOF without terminating node.");
            return true;
        }
        return false;
    }
    
    /**
     * Peeks at the next character.
     * 
     * @return
     */
    protected int peekChar()
    {
        int out = nextChar();
        ungetChar(out);
        return out;
    }
    
    /**
     * Reads the next character.
     * @return
     */
    protected int nextChar()
    {
        // is there a char we ungetted?
        int outChar = -1;
        if (pushedCharsLen > 0)
        {
            outChar = pushedChars[--pushedCharsLen];
        }   
        else
        {
            try 
            {
                outChar = inputReader.read();
            } 
            catch (IOException e) 
            {
                return -1;
            }
        }
        if (outChar == '\n')
        {
            currLine++;
            currColumn = 0;
        }
        currColumn++;
        return outChar;
    }

    /**
     * Ungets a character so the next read will return this.
     */
    protected void ungetChar(int character)
    {
        pushedChars[pushedCharsLen++] = character;
    }
}

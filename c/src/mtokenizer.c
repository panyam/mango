
#include "merror.h"
#include "minputsource.h"
#include "mstringbuffer.h"
#include "mtokenizer.h"
#include "mmemutils.h"

#define BRACE   '{'
enum
{
    NODETYPE_NONE,
    NODETYPE_COMMENT,
    NODETYPE_VARIABLE,
    NODETYPE_TAG
};

/**
 * Gets the next character.
 */
int mango_tokenizer_next_char(MangoTokenizer *tokenizer)
{
    // is there a character we ungetted?
    int outChar = -1;
    if (tokenizer->pushedCharsLen > 0)
    {
        outChar = tokenizer->pushedChars[--tokenizer->pushedCharsLen];
    }
    else
    {
        return tokenizer->inputSource->nextChar(tokenizer->inputSource);
    }
    if (outChar == '\n')
    {
        tokenizer->currLine++;
        tokenizer->currColumn = 0;
    }
    tokenizer->currColumn++;
    return outChar;
}

/**
 * "Ungets" a character that was read, making it available on the next
 * read.
 */
void mango_tokenizer_unget_char(MangoTokenizer *tokenizer, int ch)
{
    assert("Unget character stack is full" && tokenizer->pushedCharsLen < MAX_PUSHED_CHARS);
    tokenizer->pushedChars[tokenizer->pushedCharsLen++] = ch;
}

/**
 * Create a tokenizer from an input stream.
 *
 * \param   input   Input stream for the tokenizer.
 */
MangoTokenizer *mango_tokenizer_new(MangoInputSource *input)
{
    MangoTokenizer *tokenizer = NEW(MangoTokenizer);
    assert(tokenizer != NULL);
    mango_tokenizer_reset(tokenizer, input);
    return tokenizer;
}

/**
 * Destroy a tokenizer.
 *
 * \param   tokenizer   Tokenizer to destroy and free.
 */
void mango_tokenizer_free(MangoTokenizer *tokenizer)
{
    if (tokenizer != NULL)
        free(tokenizer);
}

/**
 * Resets the tokenizer with another stream.
 *
 * \param   input   New input stream to reset with.
 */
void mango_tokenizer_reset(MangoTokenizer *tokenizer, MangoInputSource *input)
{
    tokenizer->inputSource          = input;
    tokenizer->maxStringSize        = -1;
    tokenizer->_insideNode          = NODETYPE_NONE;
    tokenizer->_insideQuotes        = false;
    tokenizer->_insideIdentifier    = false;
    tokenizer->pushedCharsLen       = 0;
    tokenizer->currLine             = 0;
    tokenizer->currColumn           = 0;
}

/**
 * Tells if there are any tokens left.
 *
 * \param   tokenizer
 */
BOOL mango_tokenizer_has_tokens(MangoTokenizer *tokenizer)
{
    if (tokenizer->pushedCharsLen > 0)
    {
        return true;
    }
    else 
    {
        int nextChar = mango_tokenizer_next_char(tokenizer);
        mango_tokenizer_unget_char(tokenizer, nextChar);
        return true;
    }
    return false;
}

/**
 * Gets the next token->
 * The token is set into the token parameter.
 *
 * Returns true if a token was found, false if EOF or ERROR (which will be
 * the token type as well).
 *
 * The reason we are doing this instead of creating new tokens is each
 * token creation must be followed by a destruction and this seems very
 * wasteful from a memory management standpoint as we only need one token
 * look ahead at a time.  So might as well have a single token object and
 * reuse it till the entire tokenizing (and parsing) is complete rather
 * than creating and destroying a gazzilion tokens.  Same goes with using a
 * mutable string as the token value instead of creating and destroying
 * strings.
 *
 * \param   tokenizer
 * \param   token       Token to be populated with.
 */
BOOL mango_tokenizer_next_token(MangoTokenizer *tokenizer,
                                MangoToken *token,
                                MangoError **error)
{
    token->tokenType = TOKEN_UNKNOWN;
    // the buffer only gets created once in the entire parser run
    mango_token_set_value(token, "");

    int char1 = mango_tokenizer_next_char(tokenizer);
    while (char1 > 0)
    {
        if (tokenizer->_insideNode == NODETYPE_NONE)
        {
            // we are doing free text
            if (char1 == BRACE)
            {
                // starting a node, variable or comment
                int char2 = mango_tokenizer_next_char(tokenizer);
                tokenizer->_nodeEndChar = char2;
                if (char2 == '#')
                {
                    tokenizer->_insideNode = NODETYPE_COMMENT;
                    token->tokenType = TOKEN_COMMENT;
                }
                else if (char2 == BRACE)
                {
                    tokenizer->_nodeEndChar = '}';
                    tokenizer->_insideNode = NODETYPE_VARIABLE;
                    tokenizer->_nodeCloseToken = TOKEN_CLOSE_VARIABLE;
                    token->tokenType = TOKEN_OPEN_VARIABLE;
                }
                else if (char2 == '%')
                {
                    tokenizer->_insideNode = NODETYPE_TAG;
                    tokenizer->_nodeCloseToken = TOKEN_CLOSE_TAG;
                    token->tokenType = TOKEN_OPEN_TAG;
                }

                // we have reached a node and freetext is not empty
                // then return it
                if (tokenizer->_insideNode != NODETYPE_NONE)
                {
                    if (token->tokenValue->length > 0)
                    {
                        // push the two characters back 
                        // so they can be read again
                        mango_tokenizer_unget_char(tokenizer, char2);
                        mango_tokenizer_unget_char(tokenizer, char1);
                        tokenizer->_insideNode = NODETYPE_NONE;
                        token->tokenType = TOKEN_FREETEXT;
                        return true;
                    }
                    else if (tokenizer->_insideNode != NODETYPE_COMMENT)
                    {
                        // return the node start token
                        return true;
                    }
                }
                else 
                {
                    // nothing so append to buffer and continue
                    mango_token_append_char(token, char1);
                    if (char2 >= 0)
                        mango_token_append_char(token, char2);
                }
            }
            else
            {
                // append to freetext buffer
                mango_token_append_char(token, char1);
            }
        }
        else if (tokenizer->_insideNode == NODETYPE_COMMENT)
        {
            // skip everything until the end of comment
            if (char1 == '#')
            {
                int char2 = mango_tokenizer_next_char(tokenizer);
                if (char2 == '}')
                {
                    token->tokenType = TOKEN_COMMENT;
                    tokenizer->_insideNode = NODETYPE_NONE;
                    return true;
                }
            }
        }
        else 
        {
            // we are inside a node, now quoted strings, dots and all are
            // significant
            if (tokenizer->_insideQuotes)
            {
                if (char1 == tokenizer->_quoteType)
                {
                    // finished quotes
                    tokenizer->_insideQuotes = false;
                    return true;
                }
                else
                {
                    if (char1 == '\\')
                    {
                        char1 = mango_tokenizer_next_char(tokenizer);
                        if (char1 == '\n')
                        {
                            mango_token_append_char(token, '\n');
                        }
                        else if (char1 == '\r')
                        {
                            mango_token_append_char(token, '\r');
                        }
                        else if (char1 == '\t')
                        {
                            mango_token_append_char(token, '\t');
                        }
                        else if (char1 == '\'')
                        {
                            mango_token_append_char(token, '\'');
                        }
                        else if (char1 == '"')
                        {
                            mango_token_append_char(token, '"');
                        }
                        else if (char1 == 'f')
                        {
                            mango_token_append_char(token, '\f');
                        }
                        else if (char1 == 'u')
                        {
                            assert("Cannot yet do unicode" && false);
                        }
                        else if (char1 == 'u')
                        {
                            assert("Cannot yet do unicode" && false);
                        }
                        else if (char1 < 0)
                        {
                            token->tokenType = TOKEN_ERROR;
                            mango_error_set(error, -1, "Invalid character: %c/%d.", char1, char1);
                            return false;
                        }
                        else
                        {
                            mango_token_append_char(token, '\\');
                            mango_token_append_char(token, char1);
                        }
                    }
                    else
                    {
                        mango_token_append_char(token, char1);
                    }
                }
            }
            else if (tokenizer->_insideIdentifier)
            {
                if (isalnum(char1))
                {
                    mango_token_append_char(token, char1);
                }
                else
                {
                    // finished identifier
                    token->tokenType = TOKEN_IDENTIFIER;
                    tokenizer->_insideIdentifier = false;
                    mango_tokenizer_unget_char(tokenizer, char1);
                    return true;
                }
            }
            else if (char1 == '"' || char1 == '\'')
            {
                // inside quotes everything else is secondary
                tokenizer->_quoteType           = char1;
                tokenizer->_insideQuotes        = true;
                token->tokenType    = TOKEN_QUOTED_STRING;
            }
            else if (isalnum(char1))
            {
                mango_tokenizer_unget_char(tokenizer, char1);
                tokenizer->_insideIdentifier    = true;
                token->tokenType    = TOKEN_IDENTIFIER;
            }
            else if (isspace(char1))
            {
                // do nothing - skip spaces
            }
            else if (char1 == '.')
            {
                token->tokenType = TOKEN_DOT;
                return true;
            }
            else if (char1 == '|')
            {
                token->tokenType = TOKEN_FILTER_SEPERATOR;
                return true;
            }
            else if (char1 == ',')
            {
                token->tokenType = TOKEN_COMA;
                return true;
            }
            else if (char1 == '|')
            {
                token->tokenType = TOKEN_FILTER_SEPERATOR;
                return true;
            }
            else if (char1 == ':')
            {
                token->tokenType = TOKEN_COLON;
                return true;
            }
            else if (char1 == '(')
            {
                token->tokenType = TOKEN_OPEN_PAREN;
                return true;
            }
            else if (char1 == ')')
            {
                token->tokenType = TOKEN_CLOSE_PAREN;
                return true;
            }
            else if (char1 == tokenizer->_nodeEndChar)
            {
                // coming out of a node
                int char2 = mango_tokenizer_next_char(tokenizer);
                if (char2 == '}')
                {
                    token->tokenType = tokenizer->_nodeCloseToken;
                    tokenizer->_insideNode = NODETYPE_NONE;
                    return true;
                }
                else
                {
                    mango_tokenizer_unget_char(tokenizer, char2);
                }
            }
            else
            {
                fprintf(stderr, "Invalid Character: %c/%d", char1, char1);
                assert(false);
            }
        }
        char1 = mango_tokenizer_next_char(tokenizer);
    }

    token->tokenType = TOKEN_EOF;
    if (tokenizer->_insideNode == NODETYPE_NONE)
    {
        if (token->tokenValue->length > 0)
        {
            token->tokenType = TOKEN_FREETEXT;
            return true;
        }
    }
    else
    {
        // return unterminated node
        token->tokenType = TOKEN_ERROR;
        mango_token_set_value(token, "Reached EOF without terminating node.");
        mango_error_set(error, -1, "Reached EOF without terminating node.");
        return true;
    }
    return false;
}


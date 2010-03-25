
#include "merror.h"
#include "mtokenizer.h"
#include "mparser.h"

/**
 * Create a new parser given a tokenizer.
 *
 * \param   tokenizer   Tokenizer to initialise with.
 * \returns A new parser.  Must be freed with free.
 */
MangoParser *mango_parser_new(MangoTokenizer *tokenizer)
{
    MangoParser *parser = (MangoParser *)calloc(1, sizeof(MangoParser));
    parser->tokenizer = tokenizer;
    parser->currToken   = (MangoToken *)calloc(1, sizeof(MangoToken));
    return parser;
}

/**
 * Gets or Peeks at the next token ignore comments.
 */
const MangoToken *mango_parser_next_token(MangoParser *parser,
                                          BOOL peekOnly,
                                          MangoError **error)
{
    // do we have a cached token?
    if (parser->peekedToken != NULL)
    {
        MangoToken *out = parser->peekedToken;
        if (!peekOnly)
        {
            // clear the peeked token so next time we do a clean extract
            // what about its memory?  do we free it?
            parser->peekedToken = NULL;
        }
        return out;
    }

    BOOL result;
    do
    {
        result = mango_tokenizer_next_token(parser->tokenizer, parser->currToken, error);
    } while (result && parser->currToken->tokenType == TOKEN_COMMENT);

    if (!result)    // EOF
        return NULL;

    // if we are peeking then save the peeked token
    if (peekOnly)
        parser->peekedToken = parser->currToken;

    return parser->currToken;
}

/**
 * Gets the next token.
 */
const MangoToken *mango_parser_get_token(MangoParser *parser, MangoError **error)
{
    return mango_parser_next_token(parser, false, error);
}

/**
 * Peeks at the next token.
 */
const MangoToken *mango_parser_peek_token(MangoParser *parser, MangoError **error)
{
    return mango_parser_next_token(parser, true, error);
}

/**
 * Enforces that the next token is of a given type.
 * \param   tokenType   The token type being expected.
 * \param   peekOnly    Whether to only peek at the token instead of
 *                      extracting it from the stream.
 * \param   error       Output variable indicating any errors that may have
 *                      occurred.
 *
 * \return  The next token.  This object is readonly and must be copied by
 * the caller if required.
 */
const MangoToken *mango_parser_expect_token(MangoParser *parser,
                                            MangoTokenType tokenType,
                                            BOOL peekOnly,
                                            MangoError **error)
{
    const MangoToken *token = mango_parser_next_token(parser, peekOnly, error);
    if (token == NULL)
    {
        mango_error_set(error, -1, "Expected %d but found EOF instead!", tokenType);
        return NULL;
    }
    if (token->tokenType == TOKEN_ERROR)
    {
        return NULL;
    }
    if (token->tokenType != tokenType)
    {
        mango_error_set(error, -1, "Expected %d, Found %d instead.", tokenType, token->tokenType);
        return NULL;
    }
    return token;
}

/**
 * Gets a token and throws an error if it is not one of the expected token types.
 * \param tokens    List of tokens (terminated by TOKEN_UNKNOWN) which we
 *                  are ok with.
 * \param peekOnly  Whether we are only peeking or extracting the token as well.
 * \return The extracted token if it matches any of the expected type.
 */
const MangoToken *mango_parser_expect_token_in_list(MangoParser *parser,
                                                    MangoTokenType *tokens,
                                                    BOOL peekOnly,
                                                    MangoError **error)
{
    const MangoToken *token = mango_parser_next_token(parser, peekOnly, error);
    if (token == NULL)
    {
        mango_error_set(error, -1, "Unexpected EOF");
        return NULL;
    }
    if (token->tokenType == TOKEN_ERROR)
    {
        return NULL;
    }
    
    for (int i = 0;tokens[i] != TOKEN_UNKNOWN;i++)
    {
        if (token->tokenType == tokens[i])
            return token;
    }
    
    mango_error_set(error, -1, "Did not find expected token, Found: %d", token->tokenType);
    return NULL;
}

/**
 * Discards tokens till the specified token is found.
 *
 * \param   parser      Parser which will be discarding the tokens.
 * \param   lastToken   Token to discard until.
 */
void mango_parser_discard_till_token(MangoParser *parser,
                                     MangoTokenType lastToken,
                                     MangoError **error)
{
    const MangoToken *token = mango_parser_next_token(parser, false, error);
    while (token->tokenType != lastToken)
        token = mango_parser_next_token(parser, false, error);
}


/**
 * Parses a node.
 *
 * \param   parser  Parser doing the parsing.
 * \param   loader  The template loader driving this instance.
 * \param   error   Error to be set if any.
 *
 * \return  A Node instance.
 */
MangoNode *mango_parser_parse(MangoParser *parser,
                              MangoTemplateLoader *loader,
                              MangoError **error)
{
    MangoList *nodeList;
    MangoNode *firstNode = NULL;
    MangoNode *nextNode = mango_parser_parse_node(parser, loader, error);
    int nodeCount = 0;
    while (nextNode != NULL)
    {
        if (firstNode == NULL)
        {
            firstNode = nextNode;
        }
        else
        {
            if (nodeList == NULL)
            {
                nodeList = mango_list_new();
                mango_list_add(nodeList, firstNode);
            }
            mango_list_add(nodeList, nextNode);
        }
        nodeCount++;
        nextNode  = parseNode(parser, loader, error);
    }

    // just an optimisation to directly return a node if 
    // there is only one item instead of a node list
    if (nodeCount <= 1)
    {
        return firstNode;
    }
    else
    {
        return mango_nodelist_new(nodeList);
    }
}


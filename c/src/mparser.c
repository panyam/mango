
#include <string.h>
#include "merror.h"
#include "mtokenizer.h"
#include "mtemplateloader.h"
#include "mparser.h"
#include "mparsercontext.h"
#include "mrawlist.h"
#include "mstringbuffer.h"
#include "mstringfactory.h"
#include "mfreetext.h"
#include "mvarnode.h"
#include "mtagnode.h"
#include "mnodelist.h"

/**
 * Create a new parser given a tokenizer.
 *
 * \param   tokenizer   Tokenizer to initialise with.
 * \returns A new parser.  Must be freed with free.
 */
MangoParser *mango_parser_new(MangoTokenizer *tokenizer)
{
    MangoParser *parser     = (MangoParser *)calloc(1, sizeof(MangoParser));
    parser->tokenizer       = tokenizer;
    parser->currToken       = (MangoToken *)calloc(1, sizeof(MangoToken));
    parser->endNodeStack    = mango_rawlist_new();
    return parser;
}

/**
 * Destroys a parser created with mango_parser_new.
 *
 * \param   parser  Parser to be destroyed.
 */
void mango_parser_free(MangoParser *parser)
{
    if (parser->currToken != NULL)
        mango_token_free(parser->currToken);
    free(parser);
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
 * \param   error       Output var indicating any errors that may have
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
        mango_error_set(error, -1, "Expected %s but found EOF instead!", MangoTokenStrings[tokenType]);
        return NULL;
    }
    if (token->tokenType == TOKEN_ERROR)
    {
        return NULL;
    }
    if (token->tokenType != tokenType)
    {
        mango_error_set(error, -1, "Expected %s, Found %s instead.", MangoTokenStrings[tokenType], MangoTokenStrings[token->tokenType]);
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
 * \param   ctx     Parser context containing necessary items.
 * \param   error   Error to be set if any.
 *
 * \return  A Node instance.
 */
MangoNode *mango_parser_parse(MangoParserContext *ctx, MangoError **error)
{
    MangoRawList *  nodeList    = NULL;
    MangoNode *     firstNode   = NULL;
    MangoNode *     nextNode    = mango_parser_parse_node(ctx, error);
    int             nodeCount   = 0;
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
                nodeList = mango_rawlist_new();
                mango_rawlist_push_back(nodeList, firstNode);
            }
            mango_rawlist_push_back(nodeList, nextNode);
        }
        nodeCount++;
        nextNode    = mango_parser_parse_node(ctx, error);
    }

    // just an optimisation to directly return a node if 
    // there is only one item instead of a node list
    if (nodeCount <= 1)
    {
        return firstNode;
    }
    else
    {
        return (MangoNode *)mango_nodelist_new(nodeList);
    }
}

/**
 * Parses the next node off the stream.
 *
 * \param   ctx     Parser context containing necessary items.
 * \param   error   Error to be set if any.
 *
 * \return  The node read off the stream, NULL if none exist.
 */
MangoNode *mango_parser_parse_node(MangoParserContext *ctx, MangoError **error)
{
    MangoParser *parser = ctx->parser;
    const MangoToken *token = mango_parser_get_token(parser, error);
    if (token != NULL)
    {
        if (token->tokenType == TOKEN_FREETEXT)
        {
            // easy
            MangoString *val = mango_stringfactory_from_buffer(ctx->strfactory, token->tokenValue);
            return (MangoNode *)mango_freetext_new(val);
        }
        else if (token->tokenType == TOKEN_OPEN_VARIABLE)
        {
            return (MangoNode *)mango_varnode_extract_with_parser(ctx, error);
        }
        else if (token->tokenType == TOKEN_OPEN_TAG)
        {
            // see if the tag is part of the end node stack
            if (parser->endNodeStack != NULL && !mango_rawlist_is_empty(parser->endNodeStack))
            {
                token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, true, error);
                char **nameList = mango_rawlist_front(parser->endNodeStack);
                for (int i = 0;nameList[i] != NULL;i++)
                {
                    if (mango_stringbuffer_compare(token->tokenValue, nameList[i], strlen(nameList[i])) == 0)
                    {
                        // we are at an end tag so pop the endtag list and return an endtag indicator
                        mango_rawlist_remove_front(parser->endNodeStack);
                        return NULL;
                    }
                }
            }
            // its a normal (non-end) tag so extract it as usual
            return (MangoNode *)mango_tagnode_extract_with_parser(ctx, error);
        }
        mango_error_set(error, -1, "Invalid token found: %d", token->tokenType);
    }
    return NULL;
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
 * \param   ctx     Parser context containing necessary items.
 * \param   names   NULL terminated list of names that can act as terminal nodes.
 * \param   error   Error value to be written to in case of error.
 */
MangoNode *mango_parser_parse_till(MangoParserContext *ctx,
                                   const char **names,
                                   MangoError **error)
{
    MangoParser *parser = ctx->parser;
    int stackSize = parser->endNodeStack->size;
    mango_rawlist_push_front(parser->endNodeStack, names);
    MangoNode *parsedNodes = mango_parser_parse(ctx, error);
    if (stackSize != parser->endNodeStack->size)	// if the end node was not popped the sizes wont match!
    {
        if (parsedNodes != NULL)
        {
            mango_error_set(error, -1, "End nodes do not match");
        }
        else
        {
            mango_error_set(error, -1, "Unexpected EOF encountered without reaching end node.");
        }
    }
    return parsedNodes;
}


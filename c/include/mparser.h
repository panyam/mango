
#ifndef __MANGO_PARSER_H__
#define __MANGO_PARSER_H__

#include "mfwddefs.h"

/**
 * Mango parser.
 */
struct MangoParser
{
    MangoTokenizer  *   tokenizer;
    MangoToken *        currToken;
    MangoToken *        peekedToken;
    MangoList *         endNodeStack;
};

/**
 * Create a new parser given a tokenizer.
 *
 * \param   tokenizer   Tokenizer to initialise with.
 * \returns A new parser.  Must be freed with free.
 */
extern MangoParser *mango_parser_new(MangoTokenizer *tokenizer);

/**
 * Gets or Peeks at the next token ignore comments.
 */
extern const MangoToken *mango_parser_next_token(MangoParser *parser,
                                                 BOOL peekOnly,
                                                 MangoError **error);

/**
 * Gets the next token.
 */
extern const MangoToken *mango_parser_get_token(MangoParser *parser, 
                                                MangoError **error);

/**
 * Peeks the next token.
 */
extern const MangoToken *mango_parser_peek_token(MangoParser *parser,
                                                 MangoError **error);

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
extern const MangoToken *mango_parser_expect_token(MangoParser *parser,
                                                   MangoTokenType tokenType,
                                                   BOOL peekOnly,
                                                   MangoError **error);

/**
 * Gets a token and throws an error if it is not one of the expected token types.
 * \param tokens    List of tokens (terminated by TOKEN_UNKNOWN) which we
 *                  are ok with.
 * \param peekOnly  Whether we are only peeking or extracting the token as well.
 * \return The extracted token if it matches any of the expected type.
 */
extern const MangoToken *mango_parser_expect_token_in_list(MangoParser *parser,
                                                           MangoTokenType *tokens,
                                                           BOOL peekOnly,
                                                           MangoError **error);

/**
 * Discards tokens till the specified token is found.
 *
 * \param   parser      Parser which will be discarding the tokens.
 * \param   lastToken   Token to discard until.
 */
extern void mango_parser_discard_till_token(MangoParser *parser,
                                            MangoTokenType lastToken,
                                            MangoError **error);

/**
 * Parses a node.
 *
 * \param   parser  Parser doing the parsing.
 * \param   loader  The template loader driving this instance.
 * \param   error   Error to be set if any.
 *
 * \return  A Node instance.
 */
extern MangoNode *mango_parser_parse(MangoParser *parser,
                                     MangoTemplateLoader *loader,
                                     MangoError **error);

#if 0
    /**
     * Reads the next node whether it be a freetext node, a variable node 
     * or a tag node and returns it.  If no more nodes are left or an error 
     * was found, then a NULL is returned.
     */
    public Node parseNode(TemplateLoader loader) throws ParserException
    {
        Token token = getToken();
        if (token != NULL)
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
            		for (int i = 0;nameList[i] != NULL;i++)
            		{
            			if (nameList[i].equals(token.tokenValue.toString()))
            			{
            				// we are at an end tag so pop the endtag list and return an endtag indicator
            				endNodeStack.pop();
            				return NULL;
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

#endif

#endif


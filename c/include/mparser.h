
#ifndef __MANGO_PARSER_H__
#define __MANGO_PARSER_H__

#include "mfwddefs.h"
#include "mtokenizer.h"

#ifdef __cplusplus
extern "C" {
#endif

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
 * \returns A new parser.
 */
extern MangoParser *mango_parser_new(MangoTokenizer *tokenizer);

/**
 * Destroys a parser created with mango_parser_new.
 *
 * \param   parser  Parser to be destroyed.
 */
extern void mango_parser_free(MangoParser *parser);

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
 * Parses an input stream and returns a list of nodes.
 *
 * \param   parser  Parser doing the parsing.
 * \param   loader  The template loader driving this instance.
 * \param   error   Error to be set if any.
 *
 * \return  A Node instance.
 */
extern MangoNode *mango_parser_parse(MangoParser *parser,
                                     MangoTemplateLoader *loader,
                                     MangoError **error,
                                     MangoLibrary *tagParserLib);

/**
 * Parses the next node off the stream.
 *
 * \param   parser  Parser doing the parsing.
 * \param   loader  The template loader driving this instance.
 * \param   error   Error to be set if any.
 *
 * \return  A Node instance.
 */
extern MangoNode *mango_parser_parse_node(MangoParser *parser,
                                          MangoTemplateLoader *loader,
                                          MangoError **error,
                                          MangoLibrary *tagParserLib);

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
 * \param   parser  Parser doing the parsing.
 * \param   loader  Template loader
 * \param   names   NULL terminated list of names that can act as terminal nodes.
 * \param   error   Error value to be written to in case of error.
 */
extern MangoNode *mango_parser_parse_till(MangoParser *parser,
                                          MangoTemplateLoader *loader,
                                          const char **name_list,
                                          MangoError **error,
                                          MangoLibrary *tagParserLib);

#ifdef __cplusplus
}
#endif

#endif


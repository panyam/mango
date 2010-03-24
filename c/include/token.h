
#ifndef MANGO_TOKEN_H
#define MANGO_TOKEN_H

/**
 * Different token types allowed by the tokenizer.
 */
typedef enum {
    TOKEN_UNKNOWN   =   -2,
    TOKEN_ERROR     =   -1,
    TOKEN_EOF,
    TOKEN_FREETEXT,
    TOKEN_QUOTED_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_DOT,
    TOKEN_FILTER_SEPERATOR,			// "|"
    TOKEN_COLON,					// ":"
	TOKEN_COMA,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_COMMENT,
    TOKEN_OPEN_VARIABLE,
    TOKEN_CLOSE_VARIABLE,
    TOKEN_OPEN_TAG,
    TOKEN_CLOSE_TAG,
} MangoTokenType;

/**
 * Tokens returned by the tokenizer.
 */
typedef struct MangoToken
{
    MangoTokenType      tokenType;
    MangoString *       tokenValue;
} MangoToken;

/**
 * Creates a new token given the type and value.
 *
 * \param   type    Type of the token
 * \param   value   Value of the token.
 */
extern MangoToken mango_token_create(TokenType type, MangoString *value);

/**
 * Destroy a mango token.
 *
 * \param   token   Token to be destroyed.
 */
extern void mango_token_destroy(MangoToken *token);

/**
 * Append another character to a token's value.
 *
 * \param   token   Token to add the character to.
 * \param   ch      Character to add.
 */
extern void mango_token_append_char(MangoToken *token, int ch);

/**
 * Set the value of a mango token.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   Value to set to.
 */
extern void mango_token_set_value(MangoToken *token, MangoString *value);

/**
 * Create an EOF token.
 */
extern MangoToken mango_token_eof();

/**
 * Create an error token.
 *
 * \param   message Message of the error token.
 */
extern MangoToken mango_token_error(MangoString *message);

#endif


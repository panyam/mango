
#ifndef __MANGO_TOKEN_H__
#define __MANGO_TOKEN_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

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
struct MangoToken
{
    /**
     * Token type
     */
    MangoTokenType      tokenType;

    /**
     * Implementation specific data associated with the token.
     */
    MangoString *       tokenValue;
};

/**
 * Creates a new token given the token type and value.
 *
 * \param   tokType     Token type
 * \param   tokValue    Value of the token.
 * \param   tokLen      Length of the token value.
 *
 * \return  The new token instance.
 */
extern MangoToken *mango_token_new(MangoTokenType tokType, const char *tokValue, int tokLen);

/**
 * Frees the mango token.
 */
extern void mango_token_free(MangoToken *token);

/**
 * Sets the value of the token.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   New value of the token.
 */
extern void mango_token_set_value(MangoToken *token, const char *value);

/**
 * Appends a character to the token value.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   Character to be appended
 */
extern void mango_token_append_char(MangoToken *token, char value);

#ifdef __cplusplus
}
#endif

#endif


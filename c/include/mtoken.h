
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
    void *              tokenData;

    /**
     * Gets the size of the token value.
     */
    size_t (*tokenSize)(void *);

    /**
     * Append a character to the token's value.
     *
     * \param   token   Token to add the character to.
     * \param   ch      Character to add.
     */
    void (*appendChar)(void *, int ch);

    /**
     * Set the value of a mango token.
     *
     * \param   token   Token whose value is to be set.
     * \param   value   Value to set to.
     */
    void (*setValue)(void *token, void *);
};

#ifdef __cplusplus
}
#endif

#endif


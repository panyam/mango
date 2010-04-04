
#include "mstring.h"
#include "mtoken.h"
#include "mmemutils.h"
#include <string.h>

const char *MangoTokenStrings[TOKEN_COUNT] = {
    "TOKEN_UNKNOWN",
    "TOKEN_ERROR",
    "TOKEN_EOF",
    "TOKEN_FREETEXT",
    "TOKEN_QUOTED_STRING",
    "TOKEN_IDENTIFIER",
    "TOKEN_DOT",
    "TOKEN_FILTER_SEPERATOR",
    "TOKEN_COLON",
    "TOKEN_COMA",
    "TOKEN_OPEN_PAREN",
    "TOKEN_CLOSE_PAREN",
    "TOKEN_COMMENT",
    "TOKEN_OPEN_VARIABLE",
    "TOKEN_CLOSE_VARIABLE",
    "TOKEN_OPEN_TAG",
    "TOKEN_CLOSE_TAG",
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
MangoToken *mango_token_new(MangoTokenType tokType, const char *tokValue, int tokLen)
{
    MangoToken *token   = NEW(MangoToken);
    token->tokenType    = tokType;
    token->tokenValue   = mango_string_with_capacity(tokLen + 1);
    mango_string_set(token->tokenValue, tokValue, tokLen);
    return token;
}

/**
 * Frees the mango token.
 */
void mango_token_free(MangoToken *token)
{
    if (token->tokenValue != NULL)
        mango_string_free(token->tokenValue);
    free(token);
}

/**
 * Sets the value of the token.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   New value of the token.
 */
void mango_token_set_value(MangoToken *token, const char *value)
{
    int length = strlen(value);
    if (token->tokenValue == NULL)
    {
        token->tokenValue = mango_string_with_capacity(length + 1);
    }
    mango_string_set(token->tokenValue, value, length);
}

/**
 * Appends a character to the token value.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   Character to be appended
 */
void mango_token_append_char(MangoToken *token, char value)
{
    int length = 1;
    if (token->tokenValue == NULL)
    {
        token->tokenValue = mango_string_with_capacity(length + 1);
    }
    mango_string_append_char(token->tokenValue, value);
}

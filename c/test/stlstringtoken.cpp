
#include "stlstringtoken.h"
#include <string.h>

size_t stl_string_token_size(MangoToken *);
void stl_string_token_append_char(MangoToken *token, int ch);
void stl_string_token_set_value(MangoToken *token, void *);
void *stl_string_token_value(MangoToken *token);

/**
 * Initialises a token given the type and value.
 *
 * \param   tType   Token type
 * \param   tValue  Token value
 */
void init_stl_string_token(StlStringToken *token, MangoTokenType tType, const char *input)
{
    token->tokenBase.tokenType  = tType;
    token->tokenBase.tokenSize  = stl_string_token_size;
    token->tokenBase.appendChar = stl_string_token_append_char;
    token->tokenBase.setValue   = stl_string_token_set_value;
    token->tokenValue.str(input ? input : "");
    token->tokenSize = input ? strlen(input) : 0;
}

/**
 * Gets the size of the token value.
 */
size_t stl_string_token_size(MangoToken *token)
{
    return ((StlStringToken *)token)->tokenSize;
}

/**
 * Append a character to the token's value.
 *
 * \param   token   Token to add the character to.
 * \param   ch      Character to add.
 */
void stl_string_token_append_char(MangoToken *token, int ch)
{
    ((StlStringToken *)token)->tokenSize++;
    ((StlStringToken *)token)->tokenValue << (char)ch;
}

/**
 * Set the value of a mango token.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   Value to set to.
 */
void stl_string_token_set_value(MangoToken *token, void *value)
{
    ((StlStringToken *)token)->tokenSize = strlen((const char *)value);
    ((StlStringToken *)token)->tokenValue.str((const char *)value);
}


#include "mtoken.h"
#include "stlstringtoken.h"
#include <string.h>

size_t stl_string_token_size(void *);
void stl_string_token_append_char(void *token, int ch);
void stl_string_token_set_value(void *token, void *);
void *stl_string_token_value(void *token);

/**
 * Initialises a token given the type and value.
 *
 * \param   tType   Token type
 * \param   tValue  Token value
 */
MangoToken *stl_string_token_new(MangoTokenType tType, const char *input)
{
    MangoToken *token   = (MangoToken *)calloc(1, sizeof(MangoToken));
    token->tokenType    = tType;
    token->tokenData    = new StlStringTokenData(input);
    token->appendChar   = stl_string_token_append_char;
    token->setValue     = stl_string_token_set_value;
    token->tokenSize    = stl_string_token_size;
}

/**
 * Destroys a mango token that was created with stl_string_token_new.
 */
void stl_string_token_free(MangoToken *token)
{
    if (token != NULL)
    {
        if (token->tokenData != NULL)
            delete ((StlStringTokenData *)token->tokenData);
        free(token);
    }
}

/**
 * Gets the size of the token value.
 */
size_t stl_string_token_size(void *tokendata)
{
    return ((StlStringTokenData *)tokendata)->tokenSize;
}

/**
 * Append a character to the token's value.
 *
 * \param   token   Token to add the character to.
 * \param   ch      Character to add.
 */
void stl_string_token_append_char(void *tokendata, int ch)
{
    ((StlStringTokenData *)tokendata)->tokenSize++;
    ((StlStringTokenData *)tokendata)->tokenValue << (char)ch;
}

/**
 * Set the value of a mango token.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   Value to set to.
 */
void stl_string_token_set_value(void *tokendata, void *value)
{
    ((StlStringTokenData *)tokendata)->tokenSize = strlen((const char *)value);
    ((StlStringTokenData *)tokendata)->tokenValue.str((const char *)value);
}

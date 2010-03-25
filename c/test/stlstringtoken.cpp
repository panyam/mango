
#include "stlstringtoken.h"

int stl_string_token_size(MangoToken *);
void stl_string_token_append_char(MangoToken *token, int ch);
void stl_string_token_set_value(MangoToken *token, void *);
void *stl_string_token_value(MangoToken *token);

/**
 * Initialises a token given the type and value.
 *
 * \param   tType   Token type
 * \param   tValue  Token value
 */
void init_stl_string_token(MangoToken *token, MangoTokenType tType, const char *input)
{
    token->tokenType  = tType;
    token->tokenSize  = stl_string_token_size;
    token->appendChar = stl_string_token_append_char;
    token->setValue   = stl_string_token_set_value;

    ((StlStringToken *)token)->tokenValue.str(input ? input : "");
}

/**
 * Gets the size of the token value.
 */
int stl_string_token_size(MangoToken *)
{
    return 0;
}

/**
 * Append a character to the token's value.
 *
 * \param   token   Token to add the character to.
 * \param   ch      Character to add.
 */
void stl_string_token_append_char(MangoToken *token, int ch)
{
}

/**
 * Set the value of a mango token.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   Value to set to.
 */
void stl_string_token_set_value(MangoToken *token, void *)
{
}

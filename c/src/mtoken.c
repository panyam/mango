
#include "mtoken.h"

/**
 * Append another character to a token's value.
 *
 * \param   token   Token to add the character to.
 * \param   ch      Character to add.
 */
void mango_token_append_char(MangoToken *token, int ch)
{
}

/**
 * Set the value of a mango token.
 *
 * \param   token   Token whose value is to be set.
 * \param   value   Value to set to.
 */
void mango_token_set_value(MangoToken *token, MangoString *value)
{
}

/**
 * Create an EOF token.
 */
MangoToken mango_token_eof()
{
    MangoToken token;
    return token;
}

/**
 * Create an error token.
 *
 * \param   message Message of the error token.
 */
MangoToken mango_token_error(MangoString *message)
{
    MangoToken token;
    return token;
}



#ifndef __STL_STRING_TOKEN_H__
#define __STL_STRING_TOKEN_H__

#include "mfwddefs.h"
#include "mtoken.h"
#include <string.h>
#include <string>
#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Stl String implementation of the token.
 */
class StlStringTokenData
{
public:
    //! Constructor.
    StlStringTokenData(const char *value = NULL)
    {
        tokenValue.str(value ? value : "");
        tokenSize = value ? strlen(value) : 0;
    }

public:
    size_t              tokenSize;
    std::stringstream   tokenValue;
};

/**
 * Creates a new token given the type and value.
 *
 * \param   tType   Token type
 * \param   tValue  Token value
 */
extern MangoToken *stl_string_token_new(MangoTokenType tType = TOKEN_UNKNOWN, const char *input = NULL);

/**
 * Destroys a mango token that was created with stl_string_token_new.
 */
extern void stl_string_token_free(MangoToken *token);

#ifdef __cplusplus
}
#endif

#endif


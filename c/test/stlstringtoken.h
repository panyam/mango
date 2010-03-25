
#ifndef __STL_STRING_TOKEN_H__
#define __STL_STRING_TOKEN_H__

#include "mfwddefs.h"
#include "mtoken.h"
#include <string>
#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Stl String implementation of the token.
 */
typedef struct StlStringToken
{
    MangoToken          tokenBase;  // el-cheapo inheritance
    size_t              tokenSize;
    std::stringstream   tokenValue;
} StlStringToken;

/**
 * Initialises a token given the type and value.
 *
 * \param   tType   Token type
 * \param   tValue  Token value
 */
extern void init_stl_string_token(StlStringToken *token, MangoTokenType tType = TOKEN_UNKNOWN, const char *input = NULL);

#ifdef __cplusplus
}
#endif

#endif


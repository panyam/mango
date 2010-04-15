
#ifndef __MANGO_TOKEN_LISTS_H__
#define __MANGO_TOKEN_LISTS_H__

#include "mfwddefs.h"
#include "mtoken.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A few null terminated token lists.
 */
extern MangoTokenType IDENT_OR_STRING[3];
extern MangoTokenType COMA_OR_CLOSE_PAREN[3];
extern MangoTokenType IDENT_OR_OPEN_PAREN[3];
extern MangoTokenType IDENT_STRING_OR_OPEN_PAREN[4];

#ifdef __cplusplus
}
#endif

#endif


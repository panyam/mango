
#ifndef __MANGO_SINGLETONS_H__
#define __MANGO_SINGLETONS_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the shared filter library instance.
 */
extern MangoTable *mango_filter_library_singleton();

/**
 * Get the shared tag parser library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
extern MangoTable *mango_tagparser_library_singleton();

/**
 * Get the shared var library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
extern MangoTable *mango_var_library_singleton();

#ifdef __cplusplus
}
#endif

#endif


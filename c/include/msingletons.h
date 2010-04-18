
#ifndef __MANGO_SINGLETONS_H__
#define __MANGO_SINGLETONS_H__

#include "mfwddefs.h"
#include "mlibrary.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the shared filter library instance.
 */
extern MangoLibrary *mango_filter_library_singleton();

/**
 * Get the shared tag parser library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
extern MangoLibrary *mango_tagparser_library_singleton();

/**
 * Get the shared variable library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
extern MangoLibrary *mango_variable_library_singleton();

#ifdef __cplusplus
}
#endif

#endif


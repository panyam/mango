
#ifndef __MANGO_SINGLETONS_H__
#define __MANGO_SINGLETONS_H__

#include "mfwddefs.h"
#include "mlibrary.h"
#include "mfilterlibrary.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the shared filter library instance.
 */
extern MangoFilterLibrary *mango_filter_library_singleton();


/**
 * Get the shared tag library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
extern MangoLibrary *mango_tag_library_singleton(MangoStringTable *mstable);

/**
 * Get the shared variable library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
extern MangoLibrary *mango_variable_library_singleton(MangoStringTable *mstable);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_FILTER_LIBRARY_H__
#define __MANGO_FILTER_LIBRARY_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets a filter by a given name.
 *
 * \param   name    Name of the object class to be created.
 * \param   library Library where the creator methods are stored.  If NULL
 *                  the default instance is used.
 *
 * \return  The filter by a given name or NULL if it does not exist.
 */
extern MangoFilter *mango_filter_library_get(const MangoString *name, MangoLibrary *library);

#ifdef __cplusplus
}
#endif

#endif


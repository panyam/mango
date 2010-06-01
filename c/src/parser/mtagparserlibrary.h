
#ifndef __MANGO_TAGPARSER_LIBRARY_H__
#define __MANGO_TAGPARSER_LIBRARY_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets a tagparser by a given name.
 *
 * \param   name    Name of the object class to be created.
 * \param   library Library where the creator methods are stored.
 *
 * \return  The tagparser by a given name or NULL if it does not exist.
 */
const MangoTagParser *mango_tagparser_library_get(const MangoString *name, MangoLibrary *library);

#ifdef __cplusplus
}
#endif

#endif


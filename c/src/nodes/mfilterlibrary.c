
#include "mangopub.h"

/**
 * Gets a filter by a given name.
 *
 * \param   name    Name of the object class to be created.
 * \param   library Library where the creator methods are stored.
 *
 * \return  The filter by a given name or NULL if it does not exist.
 */
MangoFilter *mango_filter_library_get(const MangoString *name, MangoTable *library)
{
    if (library == NULL)
        library = mango_filter_library_singleton();

    return (MangoFilter *)OBJ_GETSTRATTR(library, name);
}

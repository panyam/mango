
#include "mfilterlibrary.h"
#include "msingletons.h"
#include "mbintree.h"
#include "mlibrary.h"

/**
 * Gets a filter by a given name.
 *
 * \param   name    Name of the object class to be created.
 * \param   library Library where the creator methods are stored.
 *
 * \return  The filter by a given name or NULL if it does not exist.
 */
const MangoFilter *mango_filter_library_get(const MangoString *name, 
                                            const MangoLibrary *library)
{
    if (library == NULL)
        library = mango_filter_library_singleton();

    return (const MangoFilter *)mango_library_get(library, name);
}

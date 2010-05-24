
#include "mfilterlibrary.h"
#include "msingletons.h"
#include "mbintree.h"
#include "mtable.h"

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

    return (MangoFilter *)mango_table_get(library, name);
}


#include "mtagparserlibrary.h"
#include "msingletons.h"
#include "mtagparser.h"

/**
 * Gets a tagparser by a given name.
 *
 * \param   name    Name of the object class to be created.
 * \param   library Library where the creator methods are stored.
 *
 * \return  The tagparser by a given name or NULL if it does not exist.
 */
const MangoTagParser *mango_tagparser_library_get(const MangoString *name, 
                                                  const MangoLibrary *library)
{
    if (library == NULL)
        library = mango_tagparser_library_singleton(NULL);

    return (const MangoTagParser *)mango_library_get(library, name);
}


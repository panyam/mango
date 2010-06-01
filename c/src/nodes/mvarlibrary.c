
#include "mangopub.h"

/**
 * A "special" var library.
 * Creates an instance of a special var.
 *
 * \param   name    Name of the var instance to be created.
 * \param   library Library where the var creators are stored.  If NULL
 *                  the default instance is used.
 *
 * \return  The var for a given name or NULL if it does not exist.
 */
MangoVar *mango_var_library_new_instance(const MangoString *name, MangoLibrary *library)
{
    if (library == NULL)
        library = mango_var_library_singleton();
    return (MangoVar *)OBJ_GETSTRATTR(library, name);
}


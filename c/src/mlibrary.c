
#define _GNU_SOURCE
#include <string.h>
#include "mlibrary.h"

/**
 * Creates a new mango library.
 * \param name  Name of the library.
 * \return  A new MangoLibrary instance.
 */
MangoLibrary *mango_library_new(const char *name)
{
    MangoLibrary *mlib = (MangoLibrary *)calloc(1, sizeof(MangoLibrary *));
    mlib->libType = strdup(name == NULL ? "" : name);
    return mlib;
}

/**
 * Frees a library created with the above new method.
 * \param   library Library to be destroyed.
 */
void mango_library_free(MangoLibrary *library)
{
    if (library->libType != NULL)
        free(library->libType);
    free(library);
}

/**
 * Registers a new creator method for a new type of object.
 * \param   library Library where the new creator is to be registered.
 * \param   name    Name of the creator to be registered.
 * \param   func    Creator method to be used.
 */
void mango_library_register(MangoLibrary *library, const char *name, CreatorFunc func)
{
}

/**
 * Creates a new instance of a particular object by invoking the registered
 * creator method in the library.
 *
 * \param   library Library where the creator methods are stored.
 * \param   name    Name of the object class to be created.
 * \param   ...     Parameters to be passed to the creator.
 *
 * \return  A new instance of the object created by the registered creator
 * method or NULL if a creator was not found for the name.
 */
void *mango_library_new_instance(MangoLibrary *library, const char *name, ...)
{
    return NULL;
}


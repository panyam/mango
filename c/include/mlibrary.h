
#ifndef __MANGO_LIBRARY_H__
#define __MANGO_LIBRARY_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*CreatorFunc)(const char *name, ...);

/**
 * A generic library that acts as a factory of objects.
 */
struct MangoLibrary
{
    //! Type of library - eg filter, tag etc
    char *      libType;
    MangoList * creators;
};

/**
 * Creates a new mango library.
 * \param name  Name of the library.
 * \return  A new MangoLibrary instance.
 */
extern MangoLibrary *mango_library_new(const char *name);

/**
 * Frees a library created with the above new method.
 * \param   library Library to be destroyed.
 */
extern void mango_library_free(MangoLibrary *library);

/**
 * Registers a new creator method for a new type of object.
 * \param   library Library where the new creator is to be registered.
 * \param   name    Name of the creator to be registered.
 * \param   func    Creator method to be used.
 */
extern void mango_library_register(MangoLibrary *library,
                                   const char *name,
                                   CreatorFunc func);

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
extern void *mango_library_new_instance(MangoLibrary *library,
                                        const char *name,
                                        ...);

#ifdef __cplusplus
}
#endif

#endif


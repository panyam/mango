
#ifndef __MANGO_LIBRARY_H__
#define __MANGO_LIBRARY_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A generic library that acts as a factory of objects.
 */
struct MangoLibrary
{
    //! Type of library - eg filter, tag etc
    MangoString *   name;

    //! Items in the library ordered by their name
    MangoBinTree *  entries;
};

/**
 * Creates a new mango library.
 * \param name  Name of the library.
 * \return  A new MangoLibrary instance.
 */
extern MangoLibrary *mango_library_new(const MangoString *name);

/**
 * Frees a library created with the above new method.
 * \param   library Library to be destroyed.
 */
extern void mango_library_free(MangoLibrary *library, void (*deletor)(void *));

/**
 * Registers a new creator method for a new type of object.
 * \param   library Library where the new creator is to be registered.
 * \param   name    Name of the creator to be registered.
 * \param   entry   Entyr to be registered.
 */
extern void mango_library_register(MangoLibrary *library,
                                   const MangoString *name,
                                   void *entry);

/**
 * Gets a registered entry.
 * \param   library Library where the entry is to be found
 * \param   name    Name of the entry to be registered.
 * \param   func    Creator method to be used.
 */
extern void *mango_library_get(const MangoLibrary *library, const MangoString *name);

#ifdef __cplusplus
}
#endif

#endif


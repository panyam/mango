
#ifndef __MANGO_LIBRARY_H__
#define __MANGO_LIBRARY_H__

#include "core/mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoLibrary, MangoObject,
    /**
     * The table for each section.
     */
    MangoTable *entries;
);

/**
 * Create a new mango library.
 */
MangoLibrary *mango_library_new();

/**
 * Register an object in the library.
 * \param   library         Library in which the object is being registered.
 * \param   key             Key assocaited with the object being registered.
 * \param   obj             Object being registered.
 * \param   onRegistered    Callback to call after the object is registered.
 */
extern BOOL mango_library_register(MangoLibrary *library,
                                   MangoString *key,
                                   MangoObject *obj,
                                   void (*onRegistered)(MangoObject *));

/**
 * Fetch an object registered under a certain key.
 */
MangoObject *mango_library_get(MangoLibrary *library, MangoString *key);

#ifdef __cplusplus
}
#endif

#endif


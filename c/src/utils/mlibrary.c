
#include "mangopub.h"

void mango_library_dealloc(MangoLibrary *library);

DECLARE_PROTO_FUNC("Library", MangoPrototype, mango_library_prototype,
    __proto__.deallocFunc       = (ObjectDeallocFunc)mango_library_dealloc;
    __proto__.getStrAttrFunc    = (ObjectGetStrAttrFunc)mango_library_get;
);

/**
 * Create a new mango library.
 */
MangoLibrary *mango_library_new(int numSections)
{
    MangoLibrary *library = ZNEW(MangoLibrary);
    OBJ_INIT(library, mango_library_prototype());
    return library;
}

/**
 * Register an object in the library.
 * \param   library         Library in which the object is being registered.
 * \param   key             Key assocaited with the object being registered.
 * \param   obj             Object being registered.
 * \param   onRegistered    Callback to call after the object is registered.
 */
BOOL mango_library_register(MangoLibrary *library,
                            MangoString *key,
                            MangoObject *obj,
                            void (*onRegistered)(MangoObject *))
{
    if (library == NULL)
        return false;

    if (library->entries == NULL)
        library->entries = (MangoTable *)mango_treetable_new();

    TABLE_PUT(library->entries, key, obj);
    if (onRegistered != NULL)
        onRegistered(obj);
    return true;
}

/**
 * Fetch an object registered under a certain key.
 */
MangoObject *mango_library_get(MangoLibrary *library, MangoString *key)
{
    if (library == NULL || library->entries == NULL)
        return NULL;

    return OBJ_GETSTRATTR(library->entries, key);
}

/**
 * Dealloc a library entry when its refcount reaches 0.
 */
void mango_library_dealloc(MangoLibrary *library)
{
    OBJ_DECREF(library->entries);
    mango_object_dealloc(OBJ(library));
}


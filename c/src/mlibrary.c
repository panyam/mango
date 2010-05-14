
#include <stdarg.h>
#include "mlibrary.h"
#include "mmemutils.h"
#include "mbintree.h"
#include "mstring.h"

typedef struct MangoLibraryEntry
{
    MangoString *   name;
    void *          entry;
} MangoLibraryEntry;

int libentry_name_cmp(const MangoString *name1, const MangoLibraryEntry *mle2)
{
    return mango_string_compare(name1, mle2->name);
}

int libentry_cmp(const MangoLibraryEntry *mle1, const MangoLibraryEntry *mle2)
{
    return mango_string_compare(mle1->name, mle2->name);
}

/**
 * Creates a new mango library.
 * \param name  Name of the library.
 * \return  A new MangoLibrary instance.
 */
MangoLibrary *mango_library_new()
{
    MangoLibrary *mlib  = ZNEW(MangoLibrary);
    mlib->entries       = mango_bintree_new();
    return mlib;
}

/**
 * Frees a library created with the above new method.
 * \param   library Library to be destroyed.
 */
void mango_library_free(MangoLibrary *library, void (*deletor)(void *))
{
    if (library->entries != NULL)
        mango_bintree_free(library->entries, deletor);
    free(library);
}

/**
 * Registers a new entry.
 * \param   library Library where the new entry is to be registered.
 * \param   name    Name of the entry to be registered.
 * \param   func    Creator method to be used.
 */
void mango_library_register(MangoLibrary *library, const MangoString *name, void *entry)
{
    if (library->entries == NULL)
    {
        library->entries = mango_bintree_new();
    }

    MangoBinTreeNode *node = mango_bintree_find(library->entries, name, (CompareFunc)libentry_name_cmp);
    if (node == NULL)
    {
        MangoLibraryEntry *newentry = NEW(MangoLibraryEntry);
        newentry->name  = OBJ_INCREF(name);
        newentry->entry = entry;
        mango_bintree_insert(library->entries, newentry, (CompareFunc)libentry_cmp);
    }
}

/**
 * Gets a registered entry.
 * \param   library Library where the entry is to be found
 * \param   name    Name of the entry to be registered.
 * \param   func    Creator method to be used.
 */
void *mango_library_get(const MangoLibrary *library, const MangoString *name)
{
    void *entry = NULL;
    if (library->entries != NULL)
    {
        MangoBinTreeNode *node = mango_bintree_find(library->entries, name, (CompareFunc)libentry_name_cmp);
        if (node != NULL)
            entry = node->data;
    }
    return entry;
}


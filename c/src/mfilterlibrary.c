
#include "mfilterlibrary.h"
#include "mbintree.h"
#include "mmemutils.h"
#include "mfilter.h"
#include "mstring.h"

typedef struct FilterNode
{
    MangoString *   name;
    MangoFilter *   filter;
} FilterNode;

int filter_node_compare(const void *a, const void *b)
{
    FilterNode *fna = (FilterNode *)a;
    FilterNode *fnb = (FilterNode *)b;
}

/**
 * Creates a new mango filter library.
 * \param name  Name of the library.
 * \return  A new MangoLibrary instance.
 */
MangoFilterLibrary *mango_filter_library_new()
{
    return ZNEW(MangoFilterLibrary);
}

/**
 * Frees the filter library created with the above new method.
 * \param   library Filter library to be destroyed.
 */
void mango_filter_library_free(MangoFilterLibrary *library)
{
    assert("Filter Library cannot be freed yet.");
}

/**
 * Registers a new creator method for a new type of object.
 * \param   library     Library where the new creator is to be registered.
 * \param   name        Name of the filter to be registered.
 * \param   initFunc    Initialiser function.
 */
void mango_filter_library_register(MangoFilterLibrary *library,
                                   const MangoString *name,
                                   InitFilterFunc initFunc)
{
    if (library->filters == NULL)
        library->filters = mango_bintree_new();
}

/**
 * Gets a filter by a given name.
 *
 * \param   library Library where the creator methods are stored.
 * \param   name    Name of the object class to be created.
 *
 * \return  The filter by a given name or NULL if it does not exist.
 */
MangoFilter *mango_filter_library_get(MangoLibrary *library, const MangoString *name)
{
    assert("Not implemented" && false);
    return NULL;
}

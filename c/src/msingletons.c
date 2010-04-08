#include "msingletons.h"
#include <string.h>
#include "mstring.h"

/**
 * Get the shared filter library instance.
 */
MangoFilterLibrary *mango_filter_library_singleton()
{
    static MangoFilterLibrary *filter_library = NULL;

    if (filter_library == NULL)
    {
        filter_library = mango_filter_library_new();
    }

    return filter_library;
}

/**
 * Get the shared tag library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
MangoLibrary *mango_tag_library_singleton(MangoStringTable *mstable)
{
    static MangoLibrary *tag_library = NULL;

    if (tag_library == NULL)
    {
        tag_library = mango_library_new(mango_string_new("Tags", -1, mstable));
    }

    return tag_library;
}

/**
 * Get the shared variable library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
MangoLibrary *mango_variable_library_singleton(MangoStringTable *mstable)
{
    static MangoLibrary *variable_library = NULL;

    if (variable_library == NULL)
    {
        variable_library = mango_library_new(mango_string_new("Variables", -1, mstable));
    }

    return variable_library;
}


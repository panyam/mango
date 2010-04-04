#include "msingletons.h"
#include <string.h>
#include "mstring.h"

/**
 * Get the shared filter library instance.
 */
MangoLibrary *mango_filter_library_singleton()
{
    static MangoLibrary *filter_library = NULL;

    if (filter_library == NULL)
    {
        filter_library = mango_library_new(mango_string_from_buffer("Filters", strlen("Filters")));
    }

    return filter_library;
}

/**
 * Get the shared tag library instance.
 */
MangoLibrary *mango_tag_library_singleton()
{
    static MangoLibrary *tag_library = NULL;

    if (tag_library == NULL)
    {
        tag_library = mango_library_new(mango_string_from_buffer("Tags", strlen("Tags")));
    }

    return tag_library;
}

/**
 * Get the shared variable library instance.
 */
MangoLibrary *mango_variable_library_singleton()
{
    static MangoLibrary *variable_library = NULL;

    if (variable_library == NULL)
    {
        variable_library = mango_library_new(mango_string_from_buffer("Variables", strlen("Variables")));
    }

    return variable_library;
}


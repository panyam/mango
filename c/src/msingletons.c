#include "msingletons.h"

/**
 * Get the shared filter library instance.
 */
MangoLibrary *mango_filter_library_singleton()
{
    static MangoLibrary *filter_library = NULL;

    if (filter_library == NULL)
    {
        filter_library = mango_library_new("Filters");
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
        tag_library = mango_library_new("Tags");
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
        variable_library = mango_library_new("Variable");
    }

    return variable_library;
}


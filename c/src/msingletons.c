#include "msingletons.h"
#include "mstring.h"

/**
 * Get the shared filter library instance.
 */
MangoLibrary *mango_filter_library_singleton()
{
    static MangoLibrary *filter_library = NULL;

    if (filter_library == NULL)
    {
        filter_library = mango_library_new();
    }

    return filter_library;
}

/**
 * Get the shared tag parser library instance.
 */
MangoLibrary *mango_tagparser_library_singleton()
{
    static MangoLibrary *tag_parser_library = NULL;

    if (tag_parser_library == NULL)
    {
        tag_parser_library = mango_library_new();
    }

    return tag_parser_library;
}

/**
 * Get the shared variable library instance.
 */
MangoLibrary *mango_variable_library_singleton()
{
    static MangoLibrary *variable_library = NULL;

    if (variable_library == NULL)
    {
        variable_library = mango_library_new();
    }

    return variable_library;
}


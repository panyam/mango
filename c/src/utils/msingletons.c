#include "mangopub.h"

/**
 * Get the shared filter library instance.
 */
MangoLibrary *mango_filter_library_singleton()
{
    static MangoLibrary *filter_library = NULL;

    if (filter_library == NULL)
    {
        filter_library = (MangoLibrary *)mango_library_new();
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
        tag_parser_library = (MangoLibrary *)mango_library_new();
    }

    return tag_parser_library;
}

/**
 * Get the shared var library instance.
 */
MangoLibrary *mango_var_library_singleton()
{
    static MangoLibrary *var_library = NULL;

    if (var_library == NULL)
    {
        var_library = (MangoLibrary *)mango_library_new();
    }

    return var_library;
}


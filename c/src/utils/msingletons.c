#include "mangopub.h"

/**
 * Get the shared filter library instance.
 */
MangoTable *mango_filter_library_singleton()
{
    static MangoTable *filter_library = NULL;

    if (filter_library == NULL)
    {
        filter_library = (MangoTable *)mango_treetable_new();
    }

    return filter_library;
}

/**
 * Get the shared tag parser library instance.
 */
MangoTable *mango_tagparser_library_singleton()
{
    static MangoTable *tag_parser_library = NULL;

    if (tag_parser_library == NULL)
    {
        tag_parser_library = (MangoTable *)mango_treetable_new();
    }

    return tag_parser_library;
}

/**
 * Get the shared var library instance.
 */
MangoTable *mango_var_library_singleton()
{
    static MangoTable *var_library = NULL;

    if (var_library == NULL)
    {
        var_library = (MangoTable *)mango_treetable_new();
    }

    return var_library;
}


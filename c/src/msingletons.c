#include "msingletons.h"
#include "mstring.h"

/**
 * Get the shared filter library instance.
 */
MangoLibrary *mango_filter_library_singleton(MangoStringTable *mstable)
{
    static MangoLibrary *filter_library = NULL;

    if (filter_library == NULL)
    {
        filter_library = mango_library_new(mango_string_new("Filters", -1, mstable));
    }

    return filter_library;
}

/**
 * Get the shared tag parser library instance.
 * \param   mstable String table from which pooled strings are fetched.
 */
MangoLibrary *mango_tagparser_library_singleton(MangoStringTable *mstable)
{
    static MangoLibrary *tag_parser_library = NULL;

    if (tag_parser_library == NULL)
    {
        tag_parser_library = mango_library_new(mango_string_new("TagParsers", -1, mstable));
    }

    return tag_parser_library;
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


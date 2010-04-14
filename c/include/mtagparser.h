
#ifndef __MANGO_TAGPARSER_H__
#define __MANGO_TAGPARSER_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Parsers responsible for parsing tags.  Custom tags can be parsed by
 * extending this structure.
 */
struct MangoTagParser
{
    /**
     * Data for the parser.
     */
    void *parser_data;

    //! Deletes the tag parser data
    void (*deleteFunc)(MangoTagParser *parser);

    //! Parses the node
    MangoNode *(*parserFunc)(MangoTagParser *       tagparser,
                             MangoParser *          parser,
                             MangoTemplateLoader *  loader,
                             MangoError **          error);
};

#ifdef __cplusplus
}
#endif

#endif


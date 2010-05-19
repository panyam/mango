
#ifndef __MANGO_TAGPARSER_H__
#define __MANGO_TAGPARSER_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Base prototype for all tag parsers.
 */
INHERIT_STRUCT(MangoTagParserPrototype, MangoPrototype,
    //! Parses the node
    MangoTagNode *(*parserFunc)(MangoTagParser *       tagparser,
                                MangoParserContext *   ctx,
                                MangoError **          error);
);

/**
 * Super class of all tag parsers.
 */
DECLARE_CLASS(MangoTagParser, MangoTagParserPrototype);

#ifdef __cplusplus
}
#endif

#endif


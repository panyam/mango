
#ifndef __MANGO_TAGPARSER_H__
#define __MANGO_TAGPARSER_H__

#include "core/mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

//! Parses the node
typedef MangoTagNode *(*TagParserFunc)(MangoTagParser * tagparser,
                                       MangoParser *    parser,
                                       MangoContext *   ctx,
                                       MangoError **    error);
/**
 * Base prototype for all tag parsers.
 */
INHERIT_STRUCT(MangoTagParserPrototype, MangoPrototype,
    //! Parses the node
    MangoTagNode *(*parserFunc)(MangoTagParser *    tagparser,
                                MangoParser *       parser,
                                MangoContext *      ctx,
                                MangoError **       error);
);

/**
 * Super class of all tag parsers.
 */
DECLARE_CLASS(MangoTagParser, MangoTagParserPrototype);

#ifdef __cplusplus
}
#endif

#endif


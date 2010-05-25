
#ifndef __MANGO_PARSER_CONTEXT_H__
#define __MANGO_PARSER_CONTEXT_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Mango parser context.
 */
struct MangoParserContext
{
    MangoParser *           parser;
    MangoTable *            filterlib;
    MangoTable *            taglib;
    MangoTable *            varlib;
    MangoStringFactory *    strfactory;
    MangoTemplateLoader *   loader;
};

#ifdef __cplusplus
}
#endif

#endif


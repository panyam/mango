
#ifndef __MANGO_FREE_TEXT_H__
#define __MANGO_FREE_TEXT_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoFreeTextNode, MangoNode,
    MangoString *value;
);

/**
 * Initialises a free text node.
 */
extern MangoFreeTextNode *mango_freetext_init(MangoFreeTextNode *mftNode, MangoString *value);

#ifdef __cplusplus
}
#endif

#endif


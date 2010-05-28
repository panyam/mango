
#ifndef __MANGO_FREE_TEXT_H__
#define __MANGO_FREE_TEXT_H__

#include "mnode.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoFreeTextNode, MangoNode,
    MangoString *value;
);

/**
 * Creates a freetext node.
 */
extern MangoFreeTextNode *mango_freetext_new(MangoString *value);

/**
 * Initialises a free text node.
 */
extern MangoFreeTextNode *mango_freetext_init(MangoFreeTextNode *mftNode, MangoString *value);

/**
 * Tells if two free text nodes are equal.
 */
extern BOOL mango_freetext_are_equal(const MangoFreeTextNode *mftn1, const MangoFreeTextNode *mftn2);

/**
 * Compares two free text nodes.
 */
extern int mango_freetext_compare(const MangoFreeTextNode *mftn1, const MangoFreeTextNode *mftn2);

/**
 * Dealloc's a freetext node.
 */
extern void mango_freetext_dealloc(MangoFreeTextNode *mftnode);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_NODE_H__
#define __MANGO_NODE_H__

#include "mobject.h"
#include "mclasses.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Declare empty node prototype.
 */
INHERIT_STRUCT(MangoNodePrototype, MangoPrototype);

/**
 * A mango node object.
 */
DECLARE_CLASS(MangoNode, MangoNodePrototype);

/**
 * Initialises a mango node.
 */
extern MangoNode *mango_node_init(MangoNode *node, MangoNodePrototype *prototype);

/**
 * Dealloc's a node.
 */
extern void mango_node_dealloc(MangoNode *node);

#ifdef __cplusplus
}
#endif

#endif


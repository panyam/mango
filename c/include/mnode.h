
#ifndef __MANGO_NODE_H__
#define __MANGO_NODE_H__

#include "mobject.h"
#include "mclasses.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Typedef of a few callback types.
 */
typedef int (*NodeCountFunc)(void *nodeData);
typedef MangoNode *(*NodeChildFunc)(void *nodeData, unsigned index);

INHERIT_STRUCT(MangoNodePrototype, MangoPrototype,
    /**
     * Returns the node count.
     */
    int (*nodeCountFunc)(void *nodeData);
);

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


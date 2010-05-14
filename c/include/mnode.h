
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

    /**
     * Returns a child node at a given index.
     */
    MangoNode *(*getChildNodeFunc)(void *nodeData, unsigned index);
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
 * Returns the number of child nodes of a node.
 */
extern int mango_node_childcount(MangoNode *node);

/**
 * Gets a particular child node.
 */
extern MangoNode *mango_node_childat(MangoNode *node, unsigned index);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_NODE_LIST_H__
#define __MANGO_NODE_LIST_H__

#include "mnode.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoNodeList, MangoNode,
    MangoLinkedList *nodes;
);

/**
 * Creates a new list node with a bunch of nodes.
 */
extern MangoNodeList *mango_nodelist_new(MangoLinkedList *nodes);

/**
 * Creates a new mango node list.
 */
extern MangoNodeList *mango_nodelist_init(MangoNodeList *nodelist, MangoLinkedList *nodes, MangoNodePrototype *prototype);

/**
 * Create a node list from a variable number of node arguments.
 */
extern MangoNodeList *mango_nodelist_from_nodes(int numNodes, ...);

/**
 * Called when a nodelist is to be dealloced.
 */
extern void mango_nodelist_dealloc(MangoNodeList *nodelist);

/**
 * Returns the number of child nodes of a node.
 */
extern unsigned mango_nodelist_childcount(MangoNodeList *nodelist);

/**
 * Gets a particular child node.
 */
extern MangoNode *mango_nodelist_childat(MangoNodeList *nodelist, unsigned index);

#ifdef __cplusplus
}
#endif

#endif


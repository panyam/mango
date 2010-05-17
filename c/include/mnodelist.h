
#ifndef __MANGO_NODE_LIST_H__
#define __MANGO_NODE_LIST_H__

#include "mnode.h"

INHERIT_STRUCT(MangoNodeList, MangoNode,
    MangoList *nodes;
);

/**
 * Creates a new list node with a bunch of nodes.
 */
extern MangoNodeList *mango_nodelist_new(MangoList *nodes);

/**
 * Creates a new mango node list.
 */
extern MangoNodeList *mango_nodelist_init(MangoNodeList *nodelist, MangoList *nodes, MangoNodePrototype *prototype);

/**
 * Create a node list from a variable number of node arguments.
 */
extern MangoNodeList *mango_nodelist_from_nodes(int numNodes, ...);

/**
 * Called when a nodelist is to be dealloced.
 */
extern void mango_nodelist_dealloc(MangoNodeList *nodelist);

#endif


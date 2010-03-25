
#ifndef __MANGO_NODE_LIST_H__
#define __MANGO_NODE_LIST_H__

/**
 * Creates a new mango node list.
 */
extern MangoNode *mango_nodelist_new(MangoList *nodes);

/**
 * Create a node list from a variable number of node arguments.
 */
extern MangoNode *mango_nodelist_from_nodes(int numNodes, ...);

#endif



#ifndef __MANGO_NODE_H__
#define __MANGO_NODE_H__

#include "mfwddefs.h"

/**
 * A mango node object.
 */
struct MangoNode
{
    void    *node_data;

    /**
     * Returns the node count.
     */
    int (*nodeCount)(void *node_data);

    /**
     * Returns a child node at a given index.
     */
    MangoNode *(*getChildNode)(void *node_data, int index);
};

#endif


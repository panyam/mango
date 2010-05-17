
#include <stdarg.h>
#include "mmemutils.h"
#include "mnodelist.h"
#include "mnode.h"
#include "mlist.h"

/**
 * Get the size of the node list.
 * \param   nodelist    The node list whose size is to be returned.
 * \return Number of child nodes in the nodelist.
 */
unsigned mango_nodelist_size(MangoNodeList *nodelist)
{
    return mango_list_size(nodelist->nodes);
}

/**
 * Get the child at a given index.
 * \param   nodelist    The node list whose child is to be extracted.
 * \param   index       Index at which the child is to be extracted.
 * \return A MangoNode at the given index.
 */
MangoNode *mango_nodelist_child_at(MangoNodeList *nodelist, unsigned index)
{
    return mango_list_item_at(nodelist->nodes, index);
}

/**
 * The prototype for mango node lists.
 */
MangoNodePrototype *mango_nodelist_prototype()
{
    DECLARE_PROTO_VARIABLE("MangoNodeList", MangoNodePrototype, nodeListPrototype,
        nodeListPrototype.nodeCountFunc     = (NodeCountFunc)mango_nodelist_size;
        nodeListPrototype.getChildNodeFunc  = (NodeChildFunc)mango_nodelist_child_at;
        ((MangoPrototype *)&nodeListPrototype)->deallocFunc = mango_nodelist_dealloc;
    );
}

/**
 * Creates a new list node with a bunch of nodes.
 */
MangoNodeList *mango_nodelist_new(MangoList *nodes)
{
    MangoNodeList *nodelist = NEW(MangoNodeList *);
    return mango_nodelist_init(nodelist, nodes, mango_nodelist_prototype());
}

/**
 * Creates a new mango node list.
 */
MangoNodeList *mango_nodelist_init(MangoNodeList *nodelist, MangoList *nodes, MangoNodePrototype *prototype)
{
    mango_node_init((MangoNode *)nodelist, prototype);
    nodelist->nodes     = nodes;
    return nodelist;
}

/**
 * Create a node list from a variable number of node arguments.
 */
MangoNodeList *mango_nodelist_from_nodes(int numNodes, ...)
{
    MangoList *nodes = mango_list_new();

    va_list ap;
    va_start(ap, numNodes);
    for (int i = 0;i < numNodes;i++)
    {
        MangoNode *node = va_arg(ap, MangoNode *);
        mango_list_push_back(nodes, node);
    }
    return mango_nodelist_new(nodes);
}

/**
 * Dealloc's a node.
 */
void mango_nodelist_dealloc(MangoNodeList *nodelist)
{
    // simply call node's dealloc
    mango_node_dealloc((MangoNode *)nodelist);
}


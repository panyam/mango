
#include <stdarg.h>
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
    DECLARE_PROTO_INITIALISER("MangoNodeList", MangoNodePrototype, nodeListPrototype,
        nodePrototype.nodeCountFunc     = mango_nodelist_size;
        nodePrototype.getChildNodeFunc  = mango_nodelist_child_at;
    );
}

/**
 * Creates a new mango node list.
 */
MangoNodeList *mango_nodelist_init(MangoNodeList *nodelist, MangoList *nodes, MangoNodePrototype *prototype)
{
    mango_node_init((MangoNode *)nodelist, prototype);
    // ((MangoObject *)nodelist)->__prototype__    = mango_nodelist_prototype();
    nodelist->nodes                             = nodes;
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


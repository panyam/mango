
#include "mangopub.h"

/**
 * The prototype for mango node lists.
 */
DECLARE_PROTO_FUNC(mango_nodelist_prototype, MangoNodePrototype, mango_node_prototype(), 
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_nodelist_dealloc;
);

/**
 * Creates a new list node with a bunch of nodes.
 */
MangoNodeList *mango_nodelist_new(MangoLinkedList *nodes)
{
    MangoNodeList *nodelist = NEW(MangoNodeList);
    return mango_nodelist_init(nodelist, nodes, mango_nodelist_prototype());
}

/**
 * Creates a new mango node list.
 */
MangoNodeList *mango_nodelist_init(MangoNodeList *nodelist, MangoLinkedList *nodes, MangoNodePrototype *prototype)
{
    if (prototype == NULL)
        prototype = mango_nodelist_prototype();
    mango_node_init((MangoNode *)nodelist, prototype);
    nodelist->nodes     = nodes;
    return nodelist;
}

/**
 * Create a node list from a variable number of node arguments.
 */
MangoNodeList *mango_nodelist_from_nodes(int numNodes, ...)
{
    MangoLinkedList *nodes = (MangoLinkedList *)mango_linkedlist_new();

    va_list ap;
    va_start(ap, numNodes);
    for (int i = 0;i < numNodes;i++)
    {
        MangoNode *node = va_arg(ap, MangoNode *);
        LIST_INSERT_AT(nodes, node, -1);
    }
    return mango_nodelist_new(nodes);
}

/**
 * Dealloc's a node.
 */
void mango_nodelist_dealloc(MangoNodeList *nodelist)
{
    OBJ_DECREF(nodelist->nodes);

    // simply call node's dealloc
    mango_node_dealloc((MangoNode *)nodelist);
}

/**
 * Get the size of the node list.
 * \param   nodelist    The node list whose size is to be returned.
 * \return Number of child nodes in the nodelist.
 */
unsigned mango_nodelist_childcount(MangoNodeList *nodelist)
{
    return COLLECTION_SIZE(nodelist->nodes);
}

/**
 * Get the child at a given index.
 * \param   nodelist    The node list whose child is to be extracted.
 * \param   index       Index at which the child is to be extracted.
 * \return A MangoNode at the given index.
 */
MangoNode *mango_nodelist_childat(MangoNodeList *nodelist, unsigned index)
{
    return (MangoNode *)OBJ_GETINTATTR(nodelist->nodes, index);
}


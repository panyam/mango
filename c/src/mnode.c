#include "mnode.h"

int default_node_count(void *nodeData);
MangoNode *default_get_child_node(void *nodeData, unsigned index);

/**
 * Prototype for the mango node.
 */
MangoNodePrototype *mango_node_prototype()
{
    static MangoNodePrototype nodePrototype;
    static BOOL initialised = false;
    if (!initialised)
    {
        mango_prototype_init((MangoPrototype *)(&nodeProperty), "MangoNode");
        nodePrototype.nodeCountFunc     = default_node_count;
        nodePrototype.getChildNodeFunc  = default_get_child_node;
        initialised = true;
    }
    return &nodeProperty;
}

/**
 * Initialises a mango node.
 */
MangoNode *mango_node_init(MangoNode *node, MangoNodePrototype *prototype)
{
    // call parent initialiser
    mango_object_init((MangoObject *)node, (MangoPrototype *)prototype);
    return node;
}

/**
 * Returns the number of child nodes of a node.
 */
int mango_node_childcount(MangoNode *node)
{
    if (node->nodeData != NULL && node->nodeCountFunc != NULL)
        return node->nodeCountFunc(node->nodeData);
    return 0;
}

/**
 * Gets a particular child node.
 */
MangoNode *mango_node_childat(MangoNode *node, unsigned index)
{
    if (node->nodeData != NULL && node->getChildNodeFunc != NULL)
        return node->getChildNodeFunc(node->nodeData, index);
    return NULL;
}

int default_node_count(void *nodeData)
{
    return 0;
}

MangoNode *default_get_child_node(void *nodeData, unsigned index)
{
    return NULL;
}


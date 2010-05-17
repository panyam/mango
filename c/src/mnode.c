#include "mnode.h"

int default_node_count(void *nodeData);
MangoNode *default_get_child_node(void *nodeData, unsigned index);

/**
 * Prototype for the mango node.
 */
MangoNodePrototype *mango_node_prototype()
{
    DECLARE_PROTO_VARIABLE("Node", MangoNodePrototype, nodePrototype,
        nodePrototype.nodeCountFunc     = NULL;
        nodePrototype.getChildNodeFunc  = NULL;
        ((MangoPrototype *)&nodePrototype)->deallocFunc = mango_node_dealloc;
    );
}

/**
 * Initialises a mango node.
 */
MangoNode *mango_node_init(MangoNode *node, MangoNodePrototype *prototype)
{
    // call parent initialiser
    if (prototype == NULL)
        prototype = mango_node_prototype();
    mango_object_init((MangoObject *)node, (MangoPrototype *)prototype);
    return node;
}

/**
 * Returns the number of child nodes of a node.
 */
int mango_node_childcount(MangoNode *node)
{
    if (node->__prototype__->nodeCountFunc != NULL)
    {
        return node->__prototype__->nodeCountFunc(node);
    }
    return 0;
}

/**
 * Gets a particular child node.
 */
MangoNode *mango_node_childat(MangoNode *node, unsigned index)
{
    if (node->__prototype__->getChildNodeFunc != NULL)
    {
        return node->__prototype__->getChildNodeFunc(node, index);
    }
    return NULL;
}

/**
 * Dealloc's a node.
 */
void mango_node_dealloc(MangoNode *node)
{
    // simply call object's dealloc
    mango_object_dealloc((MangoObject *)node);
}


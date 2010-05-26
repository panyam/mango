#include "mnode.h"

int default_node_count(void *nodeData);
MangoNode *default_get_child_node(void *nodeData, unsigned index);

/**
 * Prototype for the mango node.
 */
DECLARE_PROTO_FUNC("Node", MangoNodePrototype, mango_node_prototype,
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_node_dealloc;
);

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
 * Dealloc's a node.
 */
void mango_node_dealloc(MangoNode *node)
{
    // simply call object's dealloc
    mango_object_dealloc((MangoObject *)node);
}


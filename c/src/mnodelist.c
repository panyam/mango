
#include <stdarg.h>
#include "mnodelist.h"
#include "mnode.h"
#include "mlist.h"

/**
 * Creates a new mango node list.
 */
MangoNode *mango_nodelist_new(MangoList *nodes)
{
    MangoNode *node             = mango_node_new(nodes);
    node->nodeClass             = mango_class_for_name("NodeList", true);
    node->deleteNodeData        = (DeleteNodeDataCallback)mango_list_free;
    node->nodeCount             = (NodeCountCallback)mango_list_size;
    node->getChildNode          = (GetChildNodeCallback)mango_list_item_at;

    /*
    node->createNodeContextData = default_create_node_context_data;
    node->deleteNodeContextData = default_delete_node_context_data;
    node->equalsNode            = default_node_compare;
    node->renderBitMore         = default_render_bit_more;
    node->childExited           = default_child_exited;
    */
    return node;
}

/**
 * Create a node list from a variable number of node arguments.
 */
MangoNode *mango_nodelist_from_nodes(int numNodes, ...)
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


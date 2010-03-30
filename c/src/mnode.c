#include "mnode.h"

void default_delete_node_data(void *nodeData);
int default_node_count(void *nodeData);
MangoNode *default_get_child_node(void *nodeData, unsigned index);
void *default_create_node_context_data(void *nodeData,
                                       MangoTemplateContext *templateContext,
                                       MangoNodeContext *topContext);
void default_delete_node_context_data(void *node_context);
BOOL default_node_compare(void *nodedata1, void *nodedata2);
MangoNode *default_render_bit_more(void *nodeData, 
                                   MangoTemplateContext *templateContext,
                                   MangoNodeContext *topContext);
MangoNode *default_child_exited(void *nodeData, 
                                MangoTemplateContext *templateContext,
                                MangoNodeContext *topContext);

/**
 * Creates a node with default methods.
 */
extern MangoNode *mango_node_new(void *nodeData)
{
    MangoNode *node             = (MangoNode *)calloc(1, sizeof(MangoNode));
    node->nodeClass             = mango_class_for_name("Node", true);
    node->nodeData              = nodeData;
    node->deleteNodeData        = default_delete_node_data;
    node->nodeCount             = default_node_count;
    node->getChildNode          = default_get_child_node;
    node->createNodeContextData = default_create_node_context_data;
    node->deleteNodeContextData = default_delete_node_context_data;
    node->nodeDataEquals            = default_node_compare;
    node->renderBitMore         = default_render_bit_more;
    node->childExited           = default_child_exited;
    return node;
}

/**
 * Destroys a node.
 */
void mango_node_free(MangoNode *node)
{
    if (node != NULL)
    {
        if (node->deleteNodeData != NULL)
        {
            node->deleteNodeData(node->nodeData);
        }
        free(node);
    }
}

/**
 * Compares two nodes to see if they are equal.
 *
 * \param   node1   First node in the comparison.
 * \param   node2   Second node in the comparison.
 *
 * \return  true if nodes are equal (as defined by their nodeDataEquals
 * callback), false otherwise.
 */
BOOL mango_node_equal(const MangoNode *node1, const MangoNode *node2)
{
    if (node1 == node2)
    {
        return true;
    }
    else if (node2 == NULL || node1 == NULL)
    {
        return false;
    }
    else if (node1->nodeClass == node2->nodeClass)
    {
        if (node1->nodeData == node2->nodeData)
        {
            return true;
        }
        else if (node1->nodeData == NULL || node2->nodeData == NULL)
        {
            return false;
        }
        else if (node1->nodeDataEquals != NULL)
        {
            return node1->nodeDataEquals(node1->nodeData, node2->nodeData);
        }
        else if (node2->nodeDataEquals != NULL)
        {
            return node2->nodeDataEquals(node2->nodeData, node1->nodeData);
        }
        return true;
    }
    return false;
}

void default_delete_node_data(void *nodeData)
{
    if (nodeData != NULL)
        free(nodeData);
}

int default_node_count(void *nodeData)
{
    return 0;
}

MangoNode *default_get_child_node(void *nodeData, unsigned index)
{
    return NULL;
}

void *default_create_node_context_data(void *nodeData,
                                       MangoTemplateContext *templateContext,
                                       MangoNodeContext *topContext)
{
    return NULL;
}

void default_delete_node_context_data(void *node_context)
{
    if (node_context != NULL)
        free(node_context);
}

BOOL default_node_compare(void *nodedata1, void *nodedata2)
{
    return false;
}

MangoNode *default_render_bit_more(void *nodeData, 
                                   MangoTemplateContext *templateContext,
                                   MangoNodeContext *topContext)
{
    return NULL;
}

MangoNode *default_child_exited(void *nodeData, 
                                MangoTemplateContext *templateContext,
                                MangoNodeContext *topContext)
{
    return NULL;
}


#include "mnode.h"

void default_delete_node_data(void *nodeData);
int default_node_count(void *nodeData);
MangoNode *default_get_child_node(void *nodeData, unsigned index);
BOOL default_node_compare(const void *nodedata1, const void *nodedata2);

/**
 * Creates a node with default methods.
 */
MangoNode *mango_node_new(void *nodeData)
{
    MangoNode *node             = (MangoNode *)calloc(1, sizeof(MangoNode));
    node->nodeClass             = mango_class_for_name("Node", true);
    node->nodeData              = nodeData;
    node->deleteNodeFunc        = default_delete_node_data;
    node->nodeCountFunc         = default_node_count;
    node->getChildNodeFunc      = default_get_child_node;
    node->nodeEqualsFunc        = default_node_compare;
    return node;
}

/**
 * Destroys a node.
 */
void mango_node_free(MangoNode *node)
{
    if (node != NULL)
    {
        if (node->deleteNodeFunc != NULL)
        {
            node->deleteNodeFunc(node->nodeData);
        }
        free(node);
    }
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

/**
 * Compares two nodes to see if they are equal.
 *
 * \param   node1   First node in the comparison.
 * \param   node2   Second node in the comparison.
 *
 * \return  true if nodes are equal (as defined by their nodeEqualsFunc
 * callback), false otherwise.
 */
BOOL mango_nodes_are_equal(const MangoNode *node1, const MangoNode *node2)
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
        else if (node1->nodeEqualsFunc != NULL)
        {
            return node1->nodeEqualsFunc(node1->nodeData, node2->nodeData);
        }
        else if (node2->nodeEqualsFunc != NULL)
        {
            return node2->nodeEqualsFunc(node2->nodeData, node1->nodeData);
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

BOOL default_node_compare(const void *nodedata1, const void *nodedata2)
{
    return false;
}


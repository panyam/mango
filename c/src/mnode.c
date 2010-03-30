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
    node->nodeClass             = 0;
    node->nodeData              = nodeData;
    node->deleteNodeData        = default_delete_node_data;
    node->nodeCount             = default_node_count;
    node->getChildNode          = default_get_child_node;
    node->createNodeContextData = default_create_node_context_data;
    node->deleteNodeContextData = default_delete_node_context_data;
    node->nodeEquals            = default_node_compare;
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


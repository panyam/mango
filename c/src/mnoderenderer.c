#include "mnoderenderer.h"
#include "mmemutils.h"

void *default_create_node_context_data(MangoNode *nodeData,
                                       MangoTemplateContext *templateContext,
                                       MangoNodeRenderContext *topContext);
void default_delete_node_context_data(MangoNode *node_context);
MangoNode *default_render_bit_more(MangoNode *nodeData, 
                                   MangoTemplateContext *templateContext,
                                   MangoNodeRenderContext *topContext);
MangoNode *default_child_exited(MangoNode *nodeData, 
                                MangoTemplateContext *templateContext,
                                MangoNodeRenderContext *topContext);

/**
 * Creates a node with default methods.
 */
MangoNodeRenderer *mango_node_renderer_new(void *renderData)
{
    MangoNodeRenderer *renderer = ZNEW(MangoNodeRenderer);
    return renderer;
}

void *default_create_node_context_data(MangoNode *nodeData,
                                       MangoTemplateContext *templateContext,
                                       MangoNodeRenderContext *topContext)
{
    return NULL;
}

void default_delete_node_context_data(MangoNode *node_context)
{
    if (node_context != NULL)
        free(node_context);
}

MangoNode *default_render_bit_more(MangoNode *nodeData, 
                                   MangoTemplateContext *templateContext,
                                   MangoNodeRenderContext *topContext)
{
    return NULL;
}

MangoNode *default_child_exited(MangoNode *nodeData, 
                                MangoTemplateContext *templateContext,
                                MangoNodeRenderContext *topContext)
{
    return NULL;
}


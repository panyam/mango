

#ifndef __MANGO_NODE_RENDERER_H__
#define __MANGO_NODE_RENDERER_H__

#include "mobject.h"
#include "mclasses.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Bit of context for a node for its rendering.
 */
struct MangoNodeRenderContext
{
    MangoNode *             node;
    MangoNodeRenderContext *parent;
    void *                  contextData;
};

typedef void *(*CreateNodeRenderContextDataCallback)(void *nodeData,
                                               MangoTemplateContext *templateContext,
                                               MangoNodeRenderContext *topContext);
typedef void (*DeleteNodeRenderContextDataCallback)(void *nodeContextData);
typedef MangoNode *(*NodeRenderCallback)(void *nodeData,
                                         MangoTemplateContext *templateContext,
                                         MangoNodeRenderContext *topContext);
typedef MangoNode *(*NodeChildExitedCallback)(void *nodeData,
                                              MangoTemplateContext *templateContext,
                                              MangoNodeRenderContext *topContext);

struct MangoNodeRenderer
{
    /**
     * Creates node context data for this node.
     */
    void *(*createNodeContext)(MangoNode *node,
                                   MangoTemplateContext *templateContext,
                                   MangoNodeRenderContext *topContext);

    /**
     * Deletes node context data for this node.
     */
    void (*deleteNodeContext)(void *nodeContextData);

    /**
     * Renders a bit of the node and returns the next node (if a child node
     * is being entered).
     *
     * \returns NULL if this node has finished and the control is to be
     * transferred back to the parent, "this" if this node is to be
     * continued with otherwise a child node to be rendered.
     */
    MangoNode *(*renderBitMore)(MangoNode *node, 
                                MangoTemplateContext *templateContext,
                                MangoNodeRenderContext *topContext);

    /**
     * Called when a child node (that was returned in renderBitMore) was
     * exited having completed.  By doing this we are giving the parent
     * node a chance to tell the renderer what the next node will be.
     *
     * \param   nodeData        Node data being processed.
     * \param   childNode       Child node being exited.
     * \param   templateContext
     * \param   topContext
     *
     * \return null if this node is ALSO to be exited, otherwise a new
     * child node to be pushed onto the renderer stack.
     */
    MangoNode *(*childExited)(MangoNode *node, 
                              MangoTemplateContext *templateContext,
                              MangoNodeRenderContext *topContext);
};

#ifdef __cplusplus
}
#endif

#endif


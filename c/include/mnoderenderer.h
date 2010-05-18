

#ifndef __MANGO_NODE_RENDERER_H__
#define __MANGO_NODE_RENDERER_H__

#include "mobject.h"
#include "mclasses.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * When nodes are rendered their rendering state is stored in a context.
 * This struct stores that node specific context.
 */
DECLARE_CLASS(MangoNodeRendererContext, MangoPrototype,
    MangoNode *             node;
    MangoNodeRendererContext *parent;
);


INHERIT_STRUCT(MangoNodeRendererPrototype, MangoPrototype,
    /**
     * Creates node context data for this node.
     */
    void *(*createContextFunc)(MangoNode *node,
                               MangoTemplateContext *templateContext,
                               MangoNodeRendererContext *topContext);

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
                                MangoNodeRendererContext *topContext);

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
                              MangoNodeRendererContext *topContext);
);

DECLARE_CLASS(MangoNodeRenderer, MangoNodeRendererPrototype);

#ifdef __cplusplus
}
#endif

#endif


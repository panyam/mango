
#ifndef __MANGO_NODE_H__
#define __MANGO_NODE_H__

#include "mobject.h"
#include "mclasses.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * When nodes are rendered their rendering state is stored in a context.
 * This struct stores that node specific context.
 */
DECLARE_CLASS(MangoNodeContext, MangoPrototype,
    MangoNode *         node;
    MangoNodeContext *  parent;
);

/**
 * Declare empty node prototype.
 */
INHERIT_STRUCT(MangoNodePrototype, MangoPrototype,
    /**
     * Creates node renderer context data for this node.
     */
    void *(*createContextFunc)(MangoNode *node,
                               MangoTemplateContext *templateContext,
                               MangoNodeContext *topContext);

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
                                MangoNodeContext *topContext);

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
                              MangoNodeContext *topContext);
);

/**
 * A mango node object.
 */
DECLARE_CLASS(MangoNode, MangoNodePrototype);

/**
 * Initialises a mango node.
 */
extern MangoNode *mango_node_init(MangoNode *node, MangoNodePrototype *prototype);

/**
 * Dealloc's a node.
 */
extern void mango_node_dealloc(MangoNode *node);

#ifdef __cplusplus
}
#endif

#endif


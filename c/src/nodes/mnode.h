
#ifndef __MANGO_NODE_H__
#define __MANGO_NODE_H__

#include "core/mobject.h"

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
 * Create a default node context instance.
 * \param   node    Node whose context is being created.
 * \param   parent  Context of the node's parent node.
 * \return  A NodeContext object.
 */
extern MangoNodeContext *mango_nodecontext_new(MangoNode *node, MangoNodeContext *parent);

/**
 * Declare empty node prototype.
 */
INHERIT_STRUCT(MangoNodePrototype, MangoPrototype,
    /**
     * Creates node renderer context data for this node.
     */
    MangoNodeContext *(*createContextFunc)(MangoNode *node,
                                           MangoTemplateContext *templateContext,
                                           MangoNodeContext *topContext);

    /**
     * Renders a bit of the node and returns the next node (if a child node
     * is being entered).
     *
     * \param   node        Node being renderered.
     * \param   outstream   Output stream being written to.
     * \param   tmplCtx     template context for variable resolution
     * \param   topContext  Context of the parent node.
     * \parm    error       Error to be set on failure.
     *
     * \returns NULL if this node has finished and the control is to be
     * transferred back to the parent, "this" if this node is to be
     * continued with otherwise a child node to be rendered.
     */
    MangoNode *(*renderBitMoreFunc)(MangoNode *node,
                                    MangoOutStream *outstream,
                                    MangoTemplateContext *templateContext,
                                    MangoNodeContext *topContext,
                                    MangoError **error);

    /**
     * Called when a child node (that was returned in renderBitMore) was
     * exited having completed.  By doing this we are giving the parent
     * node a chance to tell the renderer what the next node will be.
     *
     * \param   nodeData        Node data being processed.
     * \param   childNode       Child node being exited.
     * \param   templateContext
     * \param   topContext
     * \param   error           Error to be set on failure.
     *
     * \return null if this node is ALSO to be exited, otherwise a new
     * child node to be pushed onto the renderer stack.
     */
    MangoNode *(*childExitedFunc)(MangoNode *node, 
                                  MangoNode *childNode,
                                  MangoTemplateContext *templateContext,
                                  MangoNodeContext *topContext,
                                  MangoError **error);
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

/**
 * Creates node renderer context data for this node.
 */
extern MangoNodeContext *mango_node_create_context(MangoNode *node,
                                                   MangoTemplateContext *templateContext,
                                                   MangoNodeContext *topContext);

/**
 * Renders a bit of the node and returns the next node (if a child node
 * is being entered).
 *
 * \param   node        Node being renderered.
 * \param   outstream   Output stream being written to.
 * \param   tmplCtx     template context for variable resolution
 * \param   topContext  Context of the parent node.
 * \parm    error       Error to be set on failure.
 *
 * \returns NULL if this node has finished and the control is to be
 * transferred back to the parent, "this" if this node is to be
 * continued with otherwise a child node to be rendered.
 */
extern MangoNode *mango_node_render_bit_more(MangoNode *node,
                                             MangoOutStream *outstream,
                                             MangoTemplateContext *templateContext,
                                             MangoNodeContext *topContext,
                                             MangoError **error);

/**
 * Called when a child node (that was returned in renderBitMore) was
 * exited having completed.  By doing this we are giving the parent
 * node a chance to tell the renderer what the next node will be.
 *
 * \param   nodeData        Node data being processed.
 * \param   childNode       Child node being exited.
 * \param   templateContext
 * \param   topContext
 * \param   error           Error to be set on failure.
 *
 * \return null if this node is ALSO to be exited, otherwise a new
 * child node to be pushed onto the renderer stack.
 */
extern MangoNode *mango_node_child_exited(MangoNode *node,
                                          MangoNode *childNode,
                                          MangoTemplateContext *templateContext,
                                          MangoNodeContext *topContext,
                                          MangoError **error);

#ifdef __cplusplus
}
#endif

#endif


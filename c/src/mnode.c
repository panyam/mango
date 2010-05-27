#include "mnode.h"

/**
 * Create a default node context instance.
 * \param   node    Node whose context is being created.
 * \param   parent  Context of the node's parent node.
 * \return  A NodeContext object.
 */
MangoNodeContext *mango_nodecontext_new(MangoNode *node, MangoNodeContext *parent)
{
    MangoNodeContext *nc = ZNEW(MangoNodeContext);
    OBJ_INIT(nc, NULL);
    nc->node = node;
    nc->parent = parent;
    return nc;
}

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

/**
 * Creates node renderer context data for this node.
 */
MangoNodeContext *mango_node_create_context(MangoNode *node,
                                            MangoTemplateContext *templateContext,
                                            MangoNodeContext *topContext)
{
    if (node->__prototype__->createContextFunc != NULL)
        return node->__prototype__->createContextFunc(node, templateContext, topContext);
    return NULL;
}

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
MangoNode *mango_node_render_bit_more(MangoNode *node,
                                      MangoOutputStream *outstream,
                                      MangoTemplateContext *templateContext,
                                      MangoNodeContext *topContext,
                                      MangoError **error)
{
    if (node->__prototype__->renderBitMoreFunc != NULL)
        return node->__prototype__->renderBitMoreFunc(node, outstream, templateContext, topContext, error);
    return NULL;
}

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
MangoNode *mango_node_child_exited(MangoNode *node,
                                   MangoNode *childNode,
                                   MangoTemplateContext *templateContext,
                                   MangoNodeContext *topContext,
                                   MangoError **error)
{
    if (node->__prototype__->childExitedFunc != NULL)
        return node->__prototype__->childExitedFunc(node, childNode, templateContext, topContext, error);
    return NULL;
}


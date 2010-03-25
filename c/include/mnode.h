
#ifndef __MANGO_NODE_H__
#define __MANGO_NODE_H__

#include "mfwddefs.h"

/**
 * Bit of context for a node for its rendering.
 */
struct MangoNodeContext
{
    MangoNode *         node;
    MangoNodeContext *  parent;
    void *              contextData;
};

/**
 * A mango node object.
 */
struct MangoNode
{
    /**
     * The node class - this has to be unique for different types.
     */
    int     nodeClass;

    /**
     * Data associated with the node.
     */
    void    *nodeData;

    /**
     * Returns the node count.
     */
    int (*nodeCount)(void *nodeData);

    /**
     * Returns a child node at a given index.
     */
    MangoNode *(*getChildNode)(void *nodeData, int index);

    /**
     * Creates node context data for this node.
     */
    void *(*createNodeContextData)(void *nodeData,
                                   MangoTemplateContext *templateContext,
                                   MangoNodeContext *topContext);

    /**
     * Compares the node data of 2 nodes if the node classes are equal.
     */
    BOOL (*equalsNode)(void *nodedata1, void *nodedata2);

    /**
     * Renders a bit of the node and returns the next node (if a child node
     * is being entered).
     *
     * \returns NULL if this node has finished and the control is to be
     * transferred back to the parent, "this" if this node is to be
     * continued with otherwise a child node to be rendered.
     */
    (MangoNode *)(*renderBitMore)(void *nodeData, 
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
    (MangoNode *)(*childExited)(void *nodeData, 
                                MangoTemplateContext *templateContext,
                                MangoNodeContext *topContext);
};

/**
 * Creates a node with default methods.
 */
extern MangoNode *mango_node_new_default(void *nodeData);

#endif


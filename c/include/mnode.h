
#ifndef __MANGO_NODE_H__
#define __MANGO_NODE_H__

#include "mobject.h"
#include "mclasses.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Typedef of a few callback types.
 */
typedef int (*NodeCountCallback)(void *nodeData);
typedef MangoNode *(*GetChildNodeCallback)(void *nodeData, unsigned index);

/**
 * A mango node object.
 */
struct MangoNode
{
    /**
     * The node class - this has to be unique for different types.
     * The class is obtaining by the node class methods.
     */
    int     nodeClass;

    /**
     * Data associated with the node.
     */
    void    *nodeData;

    /**
     * Callback to delete the node data.
     */
    void (*deleteNodeFunc)(void *nodeData);

    /**
     * Compares the node data of 2 nodes if the node classes are equal.
     */
    BOOL (*nodeEqualsFunc)(const void *nodedata1, const void *nodedata2);

    /**
     * Returns the node count.
     */
    int (*nodeCountFunc)(void *nodeData);

    /**
     * Returns a child node at a given index.
     */
    MangoNode *(*getChildNodeFunc)(void *nodeData, unsigned index);
};

/**
 * Creates a node with default methods.
 */
extern MangoNode *mango_node_new(void *nodeData);

/**
 * Destroys a node.
 */
extern void mango_node_free(MangoNode *node);

/**
 * Returns the number of child nodes of a node.
 */
extern int mango_node_childcount(MangoNode *node);

/**
 * Gets a particular child node.
 */
extern MangoNode *mango_node_childat(MangoNode *node, unsigned index);

/**
 * Compares two nodes to see if they are equal.
 *
 * \param   node1   First node in the comparison.
 * \param   node2   Second node in the comparison.
 *
 * \return  true if nodes are equal (as defined by their nodeEquals
 * callback), false otherwise.
 */
extern BOOL mango_nodes_are_equal(const MangoNode *node1, const MangoNode *node2);

#ifdef __cplusplus
}
#endif

#endif


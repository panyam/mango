
#ifndef __MANGO_BINTREE_H__
#define __MANGO_BINTREE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A Binary tree node.
 */
struct MangoBinTreeNode
{
    void *              data;
    MangoBinTreeNode *  left;
    MangoBinTreeNode *  right;
};

/**
 * A mango error object.
 */
struct MangoBinTree
{
    MangoBinTreeNode *  root;
    size_t              size;
};

/**
 * Creates a new binary tree.
 */
extern MangoBinTree *mango_bintree_new();

/**
 * Frees the tree (and applies a deletor function to all entries).
 * \param   tree    Tree to be cleared.
 * \param   deletor Deletor method to be applied on all elements.
 */
extern void mango_bintree_free(MangoBinTree *mtree, void (*deletor)(void *));

/**
 * Clears the tree without deleting it (and applies a deletor function to all entries).
 * \param   tree    Tree to be cleared.
 * \param   deletor Deletor method to be applied on all elements.
 */
extern void mango_bintree_clear(MangoBinTree *mtree, void (*deletor)(void *));

/**
 * Inserts an item into a tree.
 *
 * \param   mtree   Tree in which to insert the item.
 * \param   data    Data to insert.
 * \param   compare Method to the item comparisons.
 * \return  The tree node matching the item.  If an item already exists, it
 * is returned instead of adding a new node.
 */
extern MangoBinTreeNode *mango_bintree_insert(MangoBinTree *mtree,
                                              void *data,
                                              CompareFunc compare);

/**
 * Returns the size of a binary tree.
 *
 * \param   mtree   Tree whose size is being queried.
 * \return  The number of nodes in the tree.
 */
extern size_t mango_bintree_size(MangoBinTree *mtree);

/**
 * Finds a node with a given item.
 * \param   mtree   Tree in which to find the item.
 * \param   data    Data to look for.
 * \param   compare Method to the item comparisons.
 * \return  The tree node matching the item or NULL if the item cannot be
 * found.
 */
extern MangoBinTreeNode *mango_bintree_find(MangoBinTree *mtree, const void *data, CompareFunc compare);

/**
 * Finds a node with a given item along with its parent.
 * \param   mtree   Tree in which to find the item.
 * \param   data    Data to look for.
 * \param   compare Method to the item comparisons.
 * \param   parent  Stores the parent pointer here.
 * \return  The tree node matching the item or NULL if the item cannot be
 * found.
 */
extern MangoBinTreeNode *mango_bintree_find_with_parent(MangoBinTree *mtree, const void *data, CompareFunc compare, MangoBinTreeNode **parent);

/**
 * Deletes a node in the binary tree.
 * \param   tree    Tree in which the node is to be deleted.
 * \param   node    Node (and its value) to be deleted.
 * \param   parent  Parent node of the node to be deleted.
 * \param   deletor Deletor function to be applied on the node's data.
 */
extern void mango_bintree_delete(MangoBinTree *tree, MangoBinTreeNode *node, MangoBinTreeNode *parent, void (*deletor)(void *));

#ifdef __cplusplus
}
#endif

#endif


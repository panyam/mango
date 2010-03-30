
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
 * Inserts an item into a tree.
 *
 * \param   mtree   Tree in which to insert the item.
 * \param   data    Data to insert.
 * \param   compare Method to the item comparisons.
 * \return  The tree node matching the item.  If an item already exists, it
 * is returned instead of adding a new node.
 */
extern MangoBinTreeNode *mango_bintree_insert(MangoBinTree *mtree, void *data, int (*compare)(const void *, const void*));

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
extern MangoBinTreeNode *mango_bintree_find(MangoBinTree *mtree, void *data, int (*compare)(const void *, const void*));

#ifdef __cplusplus
}
#endif

#endif


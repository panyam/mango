
#include "mbintree.h"

/**
 * Creates a new binary tree node.
 * \param   data    Data to set for the node.
 * \return  The new binary tree node.
 */
MangoBinTreeNode *mango_bintreenode_new(void *data)
{
    MangoBinTreeNode *node = (MangoBinTreeNode *)calloc(1, sizeof(MangoBinTreeNode));
    node->data = data;
    return node;
}

/**
 * Creates a new binary tree.
 */
MangoBinTree *mango_bintree_new()
{
    MangoBinTree *mtree = (MangoBinTree *)calloc(1, sizeof(MangoBinTree));
    return mtree;
}

/**
 * Returns the size of a binary tree.
 *
 * \param   mtree   Tree whose size is being queried.
 * \return  The number of nodes in the tree.
 */
size_t mango_bintree_size(MangoBinTree *mtree)
{
    return mtree->size;
}

/**
 * Inserts an item into a tree.
 *
 * \param   mtree   Tree in which to insert the item.
 * \param   data    Data to insert.
 * \param   compare Method to the item comparisons.
 * \return  The tree node matching the item.  If an item already exists, it
 * is returned instead of adding a new node.
 */
MangoBinTreeNode *mango_bintree_insert(MangoBinTree *mtree, void *data, int (*compare)(const void *, const void*))
{
    if (data == NULL)
        return NULL;

    if (mtree->root == NULL)
    {
        mtree->size++;
        return mtree->root = mango_bintreenode_new(data);
    }
    else
    {
        MangoBinTreeNode *curr = mtree->root;
        while (curr != NULL)
        {
            int cmp = compare(data, curr->data);
            if (cmp == 0)
            {
                return curr;
            }
            else if (cmp < 0)
            {
                if (curr->left == NULL)
                {
                    mtree->size++;
                    return curr->left = mango_bintreenode_new(data);
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {
                if (curr->right == NULL)
                {
                    mtree->size++;
                    return curr->right = mango_bintreenode_new(data);
                }
                else
                {
                    curr = curr->right;
                }
            }
        }
    }
}

/**
 * Finds a node with a given item.
 * \param   mtree   Tree in which to find the item.
 * \param   data    Data to look for.
 * \param   compare Method to the item comparisons.
 * \return  The tree node matching the item or NULL if the item cannot be
 * found.
 */
MangoBinTreeNode *mango_bintree_find(MangoBinTree *mtree, void *data, int (*compare)(const void *, const void*))
{
    MangoBinTreeNode *curr = mtree->root;
    while (curr != NULL)
    {
        int cmp = compare(data, curr->data);
        if (cmp == 0)
        {
            return curr;
        }
        else if (cmp < 0)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return NULL;
}



#include "mbintree.h"
#include "mmemutils.h"

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
 * Recursively deletes a binary tree node.
 * \param   deletor Deletor method to call on the node.
 */
void mango_bintreenode_free(MangoBinTreeNode *node, void (*deletor)(void *))
{
    if (deletor && node->data)
        deletor(node->data);
    if (node->left != NULL)
        mango_bintreenode_free(node->left, deletor);
    if (node->right != NULL)
        mango_bintreenode_free(node->right, deletor);
    free(node);
}

/**
 * Creates a new binary tree.
 */
MangoBinTree *mango_bintree_new()
{
    return ZNEW(MangoBinTree);
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
 * Frees the tree (and applies a deletor function to all entries).
 * \param   tree    Tree to be cleared.
 * \param   deletor Deletor method to be applied on all elements.
 */
void mango_bintree_free(MangoBinTree *mtree, void (*deletor)(void *))
{
    mango_bintree_clear(mtree, deletor);
    free(mtree);
}

/**
 * Clears the tree (and applies a deletor function to all entries).
 * \param   tree    Tree to be cleared.
 * \param   deletor Deletor method to be applied on all elements.
 */
void mango_bintree_clear(MangoBinTree *mtree, void (*deletor)(void *))
{
    if (mtree->root != NULL)
    {
        mango_bintreenode_free(mtree->root, deletor);
        mtree->root = NULL;
    }
    mtree->size = 0;
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
MangoBinTreeNode *mango_bintree_insert(MangoBinTree *mtree,
                                       void *data,
                                       CompareFunc compare)
                                       // int (*compare)(const void *, const void*))
{
    if (data == NULL)
        return NULL;

    MangoBinTreeNode *parent = NULL;
    MangoBinTreeNode *curr = mtree->root;
    BOOL curr_is_parents_left = false;
    while (curr != NULL)
    {
        int cmp = compare(data, curr->data);
        if (cmp == 0)
        {
            return curr;
        }
        else if (cmp < 0)
        {
            curr_is_parents_left = true;
            parent = curr;
            curr = curr->left;
        }
        else
        {
            curr_is_parents_left = false;
            parent = curr;
            curr = curr->right;
        }
    }

    mtree->size++;
    MangoBinTreeNode *newnode = mango_bintreenode_new(data);

    if (parent == NULL)
    {
        mtree->root = newnode;
    }
    else
    {
        if (curr_is_parents_left)
        {
            parent->left = newnode;
        }
        else
        {
            parent->right = newnode;
        }
    }
    return newnode;
}

/**
 * Finds a node with a given item.
 * \param   mtree   Tree in which to find the item.
 * \param   data    Data to look for.
 * \param   compare Method to the item comparisons.
 * \return  The tree node matching the item or NULL if the item cannot be
 * found.
 */
MangoBinTreeNode *mango_bintree_find(MangoBinTree *mtree,
                                     const void *data,
                                     CompareFunc compare)
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


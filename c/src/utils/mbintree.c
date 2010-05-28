
#include "mangopub.h"

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
 * Deletes a node in the binary tree.
 * \param   tree    Tree in which the node is to be deleted.
 * \param   node    Node (and its value) to be deleted.
 * \param   parent  Parent node of the node to be deleted.
 * \param   deletor Deletor function to be applied on the node's data.
 */
void mango_bintree_delete(MangoBinTree *tree, MangoBinTreeNode *node, MangoBinTreeNode *parent, void (*deletor)(void *))
{
    if (parent == NULL)
    {
        assert("Node with NULL parent MUST be the root node." && node == tree->root);
    }
    else
    {
        assert("node MUST be a child of parent" && (parent->left == node || parent->right == node));
    }

    MangoBinTreeNode **parentsChild = &(tree->root);
    if (parent != NULL)
        parentsChild = parent->left == node ? &(parent->left) : &(parent->right);

    tree->size--;

    // release the node
    if (node->data != NULL && deletor != NULL) 
    {
        deletor(node->data);
        node->data = NULL;
    }

    if (node->left != NULL && node->right != NULL)
    {
        // hardest case - find either the in order successor or the in
        // order predecessor, R and replace node's data with R and delete R
        // in order successor = left most child of right sub tree
        // in order predecessor = right most child of left subtree
        // The tree can become unbalanced if we always use one or the
        // above, so instead do it randomly or keep a counter to do this
        // alternatively...
        MangoBinTreeNode *next_parent = node;
        MangoBinTreeNode *next_node = NULL;
        BOOL use_left = true;       // TODO: Select this randomly or inconsistently
        if (use_left)
        {
            next_node = node->left;
            while (next_node->right != NULL)
            {
                next_parent = next_node;
                next_node = next_node->right;
            }
            next_parent->right = next_node->left;
        }
        else
        {
            next_node = node->right;
            while (next_node->left != NULL)
            {
                next_parent = next_node;
                next_node = next_node->left;
            }
            next_parent->left = next_node->right;
        }

        // replace node's data with next_node's data and delete next_node
        node->data = next_node->data;
        free(next_node);
    }
    else
    {
        if (node->left != NULL)
        {
            *parentsChild = node->left;
        }
        else if (node->right != NULL)
        {
            *parentsChild = node->right;
        }
        else
        {
            *parentsChild = NULL;
        }
        free(node);
    }
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
    return mango_bintree_find_with_parent(mtree, data, compare, NULL);
}

/**
 * Finds a node with a given item along with its parent.
 * \param   mtree   Tree in which to find the item.
 * \param   data    Data to look for.
 * \param   compare Method to the item comparisons.
 * \param   parent  Stores the parent pointer here.
 * \return  The tree node matching the item or NULL if the item cannot be
 * found.
 */
MangoBinTreeNode *mango_bintree_find_with_parent(MangoBinTree *mtree, const void *data, CompareFunc compare, MangoBinTreeNode **parent)
{
    if (parent != NULL) *parent = NULL;
    MangoBinTreeNode *curr = mtree->root;
    while (curr != NULL)
    {
        int cmp = compare(data, curr->data);
        if (cmp == 0)
        {
            return curr;
        }
        else
        {
            // update parent
            if (parent != NULL) *parent = curr;
            if (cmp < 0)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
    }
    return NULL;
}


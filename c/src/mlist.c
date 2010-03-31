
#include "mlist.h"

/**
 * Creates a linked list node.
 *
 * \returns A new MangoListNode instance.
 */
MangoListNode *mango_list_node_new(void *data)
{
    MangoListNode *newnode = (MangoListNode *)calloc(1, sizeof(MangoListNode));
    newnode->data = data;
    return newnode;
}

/**
 * Creates a linked list.
 *
 * \returns A new MangoList instance.
 */
MangoList *mango_list_new()
{
    return (MangoList *)calloc(1, sizeof(MangoList));
}

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 */
void mango_list_free(MangoList *mlist)
{
    if (mlist != NULL)
    {
        for (MangoListNode *temp = mlist->head;temp != NULL;)
        {
            MangoListNode *next = temp->next;
            free(temp);
            temp = next;
        }
        free(mlist);
    }
}

/**
 * Gets the number of items in the list.
 *
 * \returns A the list size.
 */
size_t mango_list_size(const MangoList *mlist)
{
    return mlist->size;
}

/**
 * Gets the node at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the node is to be retrieved.
 * \return The node at the given index.
 */
const MangoListNode *mango_list_node_at(const MangoList *mlist, int index)
{
    if (index < 0 || index >= mlist->size)
        return NULL;

    const MangoListNode *temp = mlist->head;
    for (int i = 0;i < index && temp != NULL;i++, temp = temp->next);
    return temp;
}

/**
 * Gets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \return The data at the given index.
 */
void *mango_list_item_at(const MangoList *mlist, int index)
{
    const MangoListNode *node = mango_list_node_at(mlist, index);
    return node == NULL ? NULL : node->data;
}

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
void *mango_list_front(MangoList *mlist)
{
    return mlist->head != NULL ? mlist->head->data : NULL;
}

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
void *mango_list_back(MangoList *mlist)
{
    return mlist->tail != NULL ? mlist->tail->data : NULL;
}

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
MangoListNode *mango_list_push_back(MangoList *mlist, void *data)
{
    return mango_list_insert(mlist, data, NULL);
}

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
MangoListNode *mango_list_push_front(MangoList *mlist, void *data)
{
    return mango_list_insert(mlist, data, mlist->head);
}

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
MangoListNode *mango_list_insert(MangoList *mlist, void *data, MangoListNode *beforeNode)
{
    MangoListNode *newnode = mango_list_node_new(data);
    mlist->size++;
    if (mlist->head == NULL)
    {
        mlist->head = mlist->tail = newnode;
    }
    else
    {
        if (beforeNode == NULL)
        {
            mlist->tail->next = newnode;
            newnode->prev = mlist->tail;
            mlist->tail = newnode;
        }
        else
        {
            MangoListNode *prev = beforeNode->prev;
            MangoListNode *next = beforeNode;

            newnode->prev = prev;
            newnode->next = next;

            if (prev != NULL) prev->next = newnode;
            else mlist->head = newnode;

            if (next != NULL) next->prev = newnode;
            else mlist->tail = newnode;
        }
    }
    return newnode;
}

/**
 * Removes a node from the list.
 */
void *mango_list_remove(MangoList *mlist, MangoListNode *node)
{
    void *data = node->data;
    if (mlist->size > 0)
    {
        MangoListNode *prev = node->prev;
        MangoListNode *next = node->next;
        mlist->size--;
        if (prev != NULL) prev->next = next;
        else mlist->head = next;

        if (next != NULL) next->prev = prev;
        else mlist->tail = prev;

        // erase the node
        free(node);
    }
    return data;
}

/**
 * Removes a node from the front of the list.
 */
void *mango_list_remove_front(MangoList *mlist)
{
    return mango_list_remove(mlist, mlist->head);
}

/**
 * Removes a node from the back of the list.
 */
void *mango_list_remove_back(MangoList *mlist)
{
    return mango_list_remove(mlist, mlist->tail);
}

/**
 * Tells if a list is empty or not.
 */
BOOL mango_list_is_empty(MangoList *mlist)
{
    return mlist->head == NULL;
}

/**
 * Tells if two lists are equal using a comparator function.
 */
BOOL mango_lists_are_equal(const MangoList *list1, const MangoList *list2, BOOL (*equalFn)(const void *item1, const void *item2))
{
    if (list1 == list2)
    {
        return true;
    }
    else if (list1 == NULL || list2 == NULL)
    {
        return false;
    }
    else if (list1->size != list2->size)
    {
        return false;
    }
    if (equalFn != NULL)
    {
        for (MangoListNode *n1 = list1->head, *n2=list2->head;n1 != NULL;n1=n1->next,n2=n2->next)
        {
            if (!equalFn(n1->data, n2->data))
            {
                return false;
            }
        }
    }
    return true;
}


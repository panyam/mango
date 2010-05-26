
#include "mlinkedlist.h"

/**
 * Creates a linked list node.
 *
 * \returns A new MangoListNode instance.
 */
MangoListNode *mango_rawlist_node_new(void *data)
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
MangoList *mango_rawlist_new()
{
    return (MangoList *)calloc(1, sizeof(MangoList));
}

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 */
void mango_rawlist_free(MangoList *mlist)
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
 * Clears the list and optionally deletes entries within the list with a
 * given deletor method.
 *
 * \param   mlist   List to be freed and cleared.
 * \param   deletor Method that will delete each entry.
 */
void mango_rawlist_clear(MangoList *mlist, void (*deletor)(void *))
{
    for (MangoListNode *temp = mlist->head;temp != NULL;)
    {
        MangoListNode *next = temp->next;
        if (deletor != NULL && temp->data != NULL)
            deletor(temp->data);
        free(temp);
        temp = next;
    }
    mlist->head = mlist->tail = NULL;
    mlist->size = 0;
}

/**
 * Gets the number of items in the list.
 *
 * \returns A the list size.
 */
size_t mango_rawlist_size(const MangoList *mlist)
{
    return mlist->size;
}

/**
 * Gets the node at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the node is to be retrieved.
 * \return The node at the given index.
 */
const MangoListNode *mango_rawlist_node_at(const MangoList *mlist, int index)
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
void *mango_rawlist_item_at(const MangoList *mlist, int index)
{
    const MangoListNode *node = mango_rawlist_node_at(mlist, index);
    return node == NULL ? NULL : node->data;
}

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
void *mango_rawlist_front(MangoList *mlist)
{
    return mlist->head != NULL ? mlist->head->data : NULL;
}

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
void *mango_rawlist_back(MangoList *mlist)
{
    return mlist->tail != NULL ? mlist->tail->data : NULL;
}

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
MangoListNode *mango_rawlist_push_back(MangoList *mlist, void *data)
{
    return mango_rawlist_insert(mlist, data, NULL);
}

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
MangoListNode *mango_rawlist_push_front(MangoList *mlist, void *data)
{
    return mango_rawlist_insert(mlist, data, mlist->head);
}

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
MangoListNode *mango_rawlist_insert(MangoList *mlist, void *data, MangoListNode *beforeNode)
{
    MangoListNode *newnode = mango_rawlist_node_new(data);
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
void *mango_rawlist_remove(MangoList *mlist, MangoListNode *node)
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
void *mango_rawlist_remove_front(MangoList *mlist)
{
    return mango_rawlist_remove(mlist, mlist->head);
}

/**
 * Removes a node from the back of the list.
 */
void *mango_rawlist_remove_back(MangoList *mlist)
{
    return mango_rawlist_remove(mlist, mlist->tail);
}

/**
 * Tells if a list is empty or not.
 */
BOOL mango_rawlist_is_empty(MangoList *mlist)
{
    return mlist->head == NULL;
}

/**
 * Tells if two lists are equal using a comparator function.
 */
BOOL mango_rawlists_are_equal(const MangoList *list1, const MangoList *list2, BOOL (*equalFn)(const void *item1, const void *item2))
{
    if (list1 == list2)
    {
        return true;
    }

    int size1 = list1 == NULL ? 0 : list1->size;
    int size2 = list2 == NULL ? 0 : list2->size;
    if (size1 != size2)
    {
        return false;
    }
    else if (list1 == NULL || list2 == NULL)
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


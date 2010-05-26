
#include "mlinkedlist.h"

/**
 * Creates a linked list node.
 *
 * \returns A new MangoLinkedListNode instance.
 */
MangoLinkedListNode *mango_linkedlist_node_new(void *data)
{
    MangoLinkedListNode *newnode = (MangoLinkedListNode *)calloc(1, sizeof(MangoLinkedListNode));
    newnode->data = data;
    return newnode;
}

/**
 * Creates a linked list.
 *
 * \returns A new MangoLinkedList instance.
 */
MangoLinkedList *mango_linkedlist_new()
{
    return (MangoLinkedList *)calloc(1, sizeof(MangoLinkedList));
}

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 */
void mango_linkedlist_free(MangoLinkedList *mlist)
{
    if (mlist != NULL)
    {
        for (MangoLinkedListNode *temp = mlist->head;temp != NULL;)
        {
            MangoLinkedListNode *next = temp->next;
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
void mango_linkedlist_clear(MangoLinkedList *mlist, void (*deletor)(void *))
{
    for (MangoLinkedListNode *temp = mlist->head;temp != NULL;)
    {
        MangoLinkedListNode *next = temp->next;
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
size_t mango_linkedlist_size(const MangoLinkedList *mlist)
{
    return mlist->size;
}

/**
 * Gets the node at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the node is to be retrieved.
 * \return The node at the given index.
 */
const MangoLinkedListNode *mango_linkedlist_node_at(const MangoLinkedList *mlist, int index)
{
    if (index < 0 || index >= mlist->size)
        return NULL;

    const MangoLinkedListNode *temp = mlist->head;
    for (int i = 0;i < index && temp != NULL;i++, temp = temp->next);
    return temp;
}

/**
 * Gets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \return The data at the given index.
 */
void *mango_linkedlist_item_at(const MangoLinkedList *mlist, int index)
{
    const MangoLinkedListNode *node = mango_linkedlist_node_at(mlist, index);
    return node == NULL ? NULL : node->data;
}

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
void *mango_linkedlist_front(MangoLinkedList *mlist)
{
    return mlist->head != NULL ? mlist->head->data : NULL;
}

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
void *mango_linkedlist_back(MangoLinkedList *mlist)
{
    return mlist->tail != NULL ? mlist->tail->data : NULL;
}

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
MangoLinkedListNode *mango_linkedlist_push_back(MangoLinkedList *mlist, void *data)
{
    return mango_linkedlist_insert(mlist, data, NULL);
}

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
MangoLinkedListNode *mango_linkedlist_push_front(MangoLinkedList *mlist, void *data)
{
    return mango_linkedlist_insert(mlist, data, mlist->head);
}

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
MangoLinkedListNode *mango_linkedlist_insert(MangoLinkedList *mlist, void *data, MangoLinkedListNode *beforeNode)
{
    MangoLinkedListNode *newnode = mango_linkedlist_node_new(data);
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
            MangoLinkedListNode *prev = beforeNode->prev;
            MangoLinkedListNode *next = beforeNode;

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
void *mango_linkedlist_remove(MangoLinkedList *mlist, MangoLinkedListNode *node)
{
    void *data = node->data;
    if (mlist->size > 0)
    {
        MangoLinkedListNode *prev = node->prev;
        MangoLinkedListNode *next = node->next;
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
void *mango_linkedlist_remove_front(MangoLinkedList *mlist)
{
    return mango_linkedlist_remove(mlist, mlist->head);
}

/**
 * Removes a node from the back of the list.
 */
void *mango_linkedlist_remove_back(MangoLinkedList *mlist)
{
    return mango_linkedlist_remove(mlist, mlist->tail);
}

/**
 * Tells if a list is empty or not.
 */
BOOL mango_linkedlist_is_empty(MangoLinkedList *mlist)
{
    return mlist->head == NULL;
}

/**
 * Tells if two lists are equal using a comparator function.
 */
BOOL mango_linkedlists_are_equal(const MangoLinkedList *list1, const MangoLinkedList *list2, BOOL (*equalFn)(const void *item1, const void *item2))
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
        for (MangoLinkedListNode *n1 = list1->head, *n2=list2->head;n1 != NULL;n1=n1->next,n2=n2->next)
        {
            if (!equalFn(n1->data, n2->data))
            {
                return false;
            }
        }
    }
    return true;
}


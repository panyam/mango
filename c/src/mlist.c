
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
extern void mango_list_remove(MangoList *mlist, MangoListNode *node)
{
    if (mlist->size > 0)
    {
        MangoListNode *prev = node->prev;
        MangoListNode *next = node->next;
        mlist->size--;
        if (prev != NULL) prev->next = next;
        else mlist->head = next;

        if (next != NULL) next->prev = prev;
        else mlist->tail = prev;
    }
}


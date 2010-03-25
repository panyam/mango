
#ifndef __MANGO_LIST_H__
#define __MANGO_LIST_H__

#include "mfwddefs.h"

struct MangoListNode
{
    void *          data;
    MangoListNode   *next;
    MangoListNode   *prev;
};

/**
 * A mango error object.
 */
struct MangoList
{
    MangoListNode * head;
    MangoListNode * tail;
    int             size;
};

/**
 * Creates a linked list node.
 *
 * \returns A new MangoListNode instance.
 */
extern MangoListNode *mango_list_node_new(void *data);

/**
 * Creates a linked list.
 *
 * \returns A new MangoList instance.
 */
extern MangoList *mango_list_new();

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoListNode *mango_list_push_back(MangoList *mlist, void *data);

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoListNode *mango_list_push_front(MangoList *mlist, void *data);

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
extern MangoListNode *mango_list_insert(MangoList *mlist, void *data, MangoListNode *beforeNode);

/**
 * Removes a node from the list.
 */
extern void mango_list_remove(MangoList *mlist, MangoListNode *node);

#endif


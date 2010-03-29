
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
 * Creates a new mango list.
 *
 * \returns A new MangoList instance.
 */
extern MangoList *mango_list_new();

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 */
extern void mango_list_free(MangoList *mlist);

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
extern void *mango_list_front(MangoList *mlist);

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
extern void *mango_list_back(MangoList *mlist);

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
extern void *mango_list_remove(MangoList *mlist, MangoListNode *node);

/**
 * Removes a node from the front of the list.
 */
extern void *mango_list_remove_front(MangoList *mlist);

/**
 * Removes a node from the back of the list.
 */
extern void *mango_list_remove_back(MangoList *mlist);

/**
 * Tells if a list is empty or not.
 */
extern BOOL mango_list_is_empty(MangoList *mlistd);

#endif



#ifndef __MANGO_LINKEDLIST_H__
#define __MANGO_LINKEDLIST_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoLinkedListNode
{
    void *          data;
    MangoLinkedListNode   *next;
    MangoLinkedListNode   *prev;
};

/**
 * A mango error object.
 */
struct MangoLinkedList
{
    MangoLinkedListNode * head;
    MangoLinkedListNode * tail;
    size_t          size;
};

/**
 * Creates a linked list node.
 *
 * \returns A new MangoLinkedListNode instance.
 */
extern MangoLinkedListNode *mango_linkedlist_node_new(void *data);

/**
 * Creates a new mango list.
 *
 * \returns A new MangoLinkedList instance.
 */
extern MangoLinkedList *mango_linkedlist_new();

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 */
extern void mango_linkedlist_free(MangoLinkedList *mlist);

/**
 * Clears the list and optionally deletes entries within the list with a
 * given deletor method.
 *
 * \param   mlist   List to be freed and cleared.
 * \param   deletor Method that will delete each entry.
 */
extern void mango_linkedlist_clear(MangoLinkedList *mlist, void (*deletor)(void *));

/**
 * Gets the number of items in the list.
 *
 * \returns A the list size.
 */
extern size_t mango_linkedlist_size(const MangoLinkedList *mlist);

/**
 * Gets the node at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the node is to be retrieved.
 * \return The node at the given index.
 */
extern const MangoLinkedListNode *mango_linkedlist_node_at(const MangoLinkedList *mlist, int index);

/**
 * Gets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \return The data at the given index.
 */
extern void *mango_linkedlist_item_at(const MangoLinkedList *mlist, int index);

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
extern void *mango_linkedlist_front(MangoLinkedList *mlist);

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
extern void *mango_linkedlist_back(MangoLinkedList *mlist);

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoLinkedListNode *mango_linkedlist_push_back(MangoLinkedList *mlist, void *data);

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoLinkedListNode *mango_linkedlist_push_front(MangoLinkedList *mlist, void *data);

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
extern MangoLinkedListNode *mango_linkedlist_insert(MangoLinkedList *mlist, void *data, MangoLinkedListNode *beforeNode);

/**
 * Removes a node from the list.
 */
extern void *mango_linkedlist_remove(MangoLinkedList *mlist, MangoLinkedListNode *node);

/**
 * Removes a node from the front of the list.
 */
extern void *mango_linkedlist_remove_front(MangoLinkedList *mlist);

/**
 * Removes a node from the back of the list.
 */
extern void *mango_linkedlist_remove_back(MangoLinkedList *mlist);

/**
 * Tells if a list is empty or not.
 */
extern BOOL mango_linkedlist_is_empty(MangoLinkedList *mlist);

/**
 * Tells if two lists are equal using a comparator function.
 */
extern BOOL mango_linkedlists_are_equal(const MangoLinkedList *list1, const MangoLinkedList *list2, BOOL (*equalFn)(const void *item1, const void *item2));

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_LIST_H__
#define __MANGO_LIST_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

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
    size_t          size;
};

/**
 * Creates a linked list node.
 *
 * \returns A new MangoListNode instance.
 */
extern MangoListNode *mango_rawlist_node_new(void *data);

/**
 * Creates a new mango list.
 *
 * \returns A new MangoList instance.
 */
extern MangoList *mango_rawlist_new();

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 */
extern void mango_rawlist_free(MangoList *mlist);

/**
 * Clears the list and optionally deletes entries within the list with a
 * given deletor method.
 *
 * \param   mlist   List to be freed and cleared.
 * \param   deletor Method that will delete each entry.
 */
extern void mango_rawlist_clear(MangoList *mlist, void (*deletor)(void *));

/**
 * Gets the number of items in the list.
 *
 * \returns A the list size.
 */
extern size_t mango_rawlist_size(const MangoList *mlist);

/**
 * Gets the node at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the node is to be retrieved.
 * \return The node at the given index.
 */
extern const MangoListNode *mango_rawlist_node_at(const MangoList *mlist, int index);

/**
 * Gets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \return The data at the given index.
 */
extern void *mango_rawlist_item_at(const MangoList *mlist, int index);

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
extern void *mango_rawlist_front(MangoList *mlist);

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
extern void *mango_rawlist_back(MangoList *mlist);

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoListNode *mango_rawlist_push_back(MangoList *mlist, void *data);

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoListNode *mango_rawlist_push_front(MangoList *mlist, void *data);

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
extern MangoListNode *mango_rawlist_insert(MangoList *mlist, void *data, MangoListNode *beforeNode);

/**
 * Removes a node from the list.
 */
extern void *mango_rawlist_remove(MangoList *mlist, MangoListNode *node);

/**
 * Removes a node from the front of the list.
 */
extern void *mango_rawlist_remove_front(MangoList *mlist);

/**
 * Removes a node from the back of the list.
 */
extern void *mango_rawlist_remove_back(MangoList *mlist);

/**
 * Tells if a list is empty or not.
 */
extern BOOL mango_rawlist_is_empty(MangoList *mlist);

/**
 * Tells if two lists are equal using a comparator function.
 */
extern BOOL mango_rawlists_are_equal(const MangoList *list1, const MangoList *list2, BOOL (*equalFn)(const void *item1, const void *item2));

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_RAW_LIST_H__
#define __MANGO_RAW_LIST_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoRawListNode
{
    void *          data;
    MangoRawListNode   *next;
    MangoRawListNode   *prev;
};

/**
 * A mango error object.
 */
INHERIT_STRUCT(MangoRawList, MangoObject, 
    MangoRawListNode *  head;
    MangoRawListNode *  tail;
    size_t              size;
);

/**
 * Creates a linked list node.
 *
 * \returns A new MangoRawListNode instance.
 */
extern MangoRawListNode *mango_rawlist_node_new(void *data);

/**
 * Creates a new mango list.
 *
 * \returns A new MangoRawList instance.
 */
extern MangoRawList *mango_rawlist_new();

/**
 * Initialises a raw list.
 */
extern MangoRawList *mango_rawlist_init(MangoRawList *list, MangoPrototype *proto);

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 * \param   deletor Method that will delete each entry.
 */
extern void mango_rawlist_free(MangoRawList *mlist, void (*deletor)(void *));

/**
 * Clears the list and optionally deletes entries within the list with a
 * given deletor method.
 *
 * \param   mlist   List to be freed and cleared.
 * \param   deletor Method that will delete each entry.
 */
extern void mango_rawlist_clear(MangoRawList *mlist, void (*deletor)(void *));

/**
 * Gets the number of items in the list.
 *
 * \returns A the list size.
 */
extern size_t mango_rawlist_size(const MangoRawList *mlist);

/**
 * Gets the node at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the node is to be retrieved.
 * \return The node at the given index.
 */
extern const MangoRawListNode *mango_rawlist_node_at(const MangoRawList *mlist, int index);

/**
 * Gets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \return The data at the given index.
 */
extern void *mango_rawlist_item_at(const MangoRawList *mlist, int index);

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
extern void *mango_rawlist_front(MangoRawList *mlist);

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
extern void *mango_rawlist_back(MangoRawList *mlist);

/**
 * Set the value at a given index.
 *
 * \returns The old value that was replaced.
 */
extern void *mango_rawlist_set_at(MangoRawList *mlist, int index, void *data);

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoRawListNode *mango_rawlist_push_back(MangoRawList *mlist, void *data);

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
extern MangoRawListNode *mango_rawlist_push_front(MangoRawList *mlist, void *data);

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
extern MangoRawListNode *mango_rawlist_insert(MangoRawList *mlist, void *data, MangoRawListNode *beforeNode);

/**
 * Removes a node from the list.
 */
extern void *mango_rawlist_remove(MangoRawList *mlist, MangoRawListNode *node);

/**
 * Removes a node from the front of the list.
 */
extern void *mango_rawlist_remove_front(MangoRawList *mlist);

/**
 * Removes a node from the back of the list.
 */
extern void *mango_rawlist_remove_back(MangoRawList *mlist);

/**
 * Tells if a list is empty or not.
 */
extern BOOL mango_rawlist_is_empty(MangoRawList *mlist);

/**
 * Tells if two lists are equal using a comparator function.
 */
extern BOOL mango_rawlists_are_equal(const MangoRawList *list1, const MangoRawList *list2, BOOL (*equalFn)(const void *item1, const void *item2));

#ifdef __cplusplus
}
#endif

#endif


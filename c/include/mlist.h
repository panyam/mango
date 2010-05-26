
#ifndef __MANGO_LIST_H__
#define __MANGO_LIST_H__

#include "mcollection.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ListInsertAtFunc)(MangoList *list, MangoObject *obj, int index);
typedef void (*ListSetAtFunc)(MangoList *list, int index, MangoObject *obj);
typedef void (*ListRemoveAtFunc)(MangoList *list, int index);
typedef int (*ListIndexOfFunc)(MangoList *list, MangoObject *obj, int from);
typedef int (*ListLastIndexOfFunc)(MangoList *list, MangoObject *obj, int from);

/**
 * Base interface of all lists.
 */
INHERIT_STRUCT(MangoListPrototype, MangoCollectionPrototype,
    /**
     * Set the value at a given index.
     */
    void (*setAtFunc)(MangoList *list, int index, MangoObject *obj);

    /**
     * Removes an object at a given index.
     */
    void (*removeAtFunc)(MangoList *list, int index);

    /**
     * Insert an object at a given index.
     */
    void (*insertAtFunc)(MangoList *list, MangoObject *obj, int index);

    /**
     * Return the index of an object from a particular offset in the
     * forward direction.
     */
    int (*indexOfFunc)(MangoList *list, MangoObject *obj, int from);

    /**
     * Return the last index of an object before a particular position.
     */
    int (*lastIndexOfFunc)(MangoList *list, MangoObject *obj, int from);
);

#define LIST_INSERT_AT(list, obj, index)    mango_list_insert_at((MangoList *)list, (MangoObject *)obj, index)
#define LIST_SET_AT(list, index, obj)       mango_list_set_at((MangoList *)list, index, (MangoObject *)obj)
#define LIST_PUSH_BACK(list, obj)           mango_list_push_back((MangoList *)list, (MangoObject *)obj)
#define LIST_PUSH_FRONT(list, obj)          mango_list_push_front((MangoList *)list, (MangoObject *)obj)
#define LIST_POP_BACK(list)                 mango_list_pop_back((MangoList *)list)
#define LIST_POP_FRONT(list)                mango_list_pop_front((MangoList *)list)
#define LIST_REMOVE_BACK(list)              mango_list_remove_back((MangoList *)list)
#define LIST_REMOVE_FRONT(list)             mango_list_remove_front((MangoList *)list)
#define LIST_BACK(list)                     mango_list_back((MangoList *)list)
#define LIST_FRONT(list)                    mango_list_front((MangoList *)list)

/**
 * Super class of all associative containers.
 */
DECLARE_CLASS(MangoList, MangoListPrototype);

/**
 * The default list prototype.
 */
extern MangoListPrototype *mango_list_prototype();

/**
 * Initialises an list.
 */
extern MangoList *mango_list_init(MangoList *list, MangoListPrototype *proto);

/**
 * Frees the list.
 * \param   list    List to be freed.
 */
extern void mango_list_dealloc(MangoList *list);

/**
 * Sets (and replaces) the item at a particular index.
 * \param   list    List in which the item is to be set.
 * \param   obj     Object to set at index.
 * \param   index   Index at which the item is to be set.
 */
extern void mango_list_set_at(MangoList *list, int index, MangoObject *obj);

/**
 * Inserts the item at a particular index.
 * \param   list    List in which the item is to be inserted.
 * \param   obj     Object to insert at index.
 * \param   index   Index before which the item is to be inserted (if -ve,
 *                  add at end).
 */
extern void mango_list_insert_at(MangoList *list, MangoObject *obj, int index);

/**
 * Removes the item at a particular index.
 * \param   list    List from which the item is to be removed.
 * \param   index   Index from which the item is to be removed.
 */
extern void mango_list_remove_at(MangoList *list, int index);

/**
 * Finds the first index of an object from a given position.
 * \param   list    List to search.
 * \param   obj     Object to be searched for.
 * \param   pos     Index to search form.
 * \return -1 if object is not found, otherwise index at which it is
 * located.
 */
extern int mango_list_index_of(MangoList *list, MangoObject *obj, int from);

/**
 * Adds an item at the back of the list.
 * \param   list    List to which the object is to be added.
 * \param   obj     Object to be added.
 */
extern void mango_list_push_back(MangoList *list, MangoObject *obj);

/**
 * Adds an item at the front of the list.
 * \param   list    List to which the object is to be added.
 * \param   obj     Object to be added.
 */
extern void mango_list_push_front(MangoList *list, MangoObject *obj);

/**
 * Removes an item at the back of the list.
 * \param   list    List from which the object is to be removed.
 */
extern void mango_list_remove_back(MangoList *list);

/**
 * Remove an item at the front of the list.
 * \param   list    List from which the object is to be removed.
 */
extern void mango_list_remove_front(MangoList *list);

/**
 * Pops an item at the back of the list and returns it.
 * \param   list    List from which the object is to be popped.
 */
extern MangoObject *mango_list_pop_back(MangoList *list);

/**
 * Pops an item at the front of the list and returns it.
 * \param   list    List from which the object is to be popped.
 */
extern MangoObject *mango_list_pop_front(MangoList *list);

/**
 * Finds the last index of an object from a given position.
 * \param   list    List to search.
 * \param   obj     Object to be searched for.
 * \param   pos     Index to search form.
 * \return -1 if object is not found, otherwise index at which it is
 * located.
 */
extern int mango_list_last_index_of(MangoList *list, MangoObject *obj, int from);

/**
 * Gets the item at the front of the list without removing it.
 * \param   list    List to which the object is to be retrieved.
 * \return Item at the front of the list.
 */
extern MangoObject *mango_list_front(MangoList *list);

/**
 * Gets the item at the back of the list without removing it.
 * \param   list    List to which the object is to be retrieved.
 * \return Item at the back of the list.
 */
extern MangoObject *mango_list_back(MangoList *list);

#ifdef __cplusplus
}
#endif

#endif


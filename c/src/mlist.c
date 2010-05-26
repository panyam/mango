
#include "mlist.h"

DECLARE_PROTO_FUNC("MangoList", MangoListPrototype, mango_list_prototype,
    __proto__.setAtFunc         = NULL;
    __proto__.removeAtFunc      = NULL;
    __proto__.indexOfFunc       = NULL;
    __proto__.lastIndexOfFunc   = NULL;
);

/**
 * Frees the list.
 * \param   list    List to be freed.
 */
void mango_list_dealloc(MangoList *list)
{
    mango_collection_dealloc((MangoCollection *)list);
}

/**
 * Initialises an list.
 */
MangoList *mango_list_init(MangoList *list, MangoListPrototype *proto)
{
    if (proto == NULL)
        proto = mango_list_prototype();
    mango_collection_init((MangoCollection *)list, (MangoCollectionPrototype *)proto);
    return list;
}

/**
 * Sets the item at a particular index.
 * \param   list    List in which item is to be set.
 * \param   index   Index at which the item is to be set.
 * \param   obj     Value to set to.
 */
void mango_list_set_at(MangoList *list, int index, MangoObject *obj)
{
    if (list->__prototype__->setAtFunc != NULL)
        list->__prototype__->setAtFunc(list, index, obj);
}

/**
 * Inserts the item at a particular index.
 * \param   list    List in which the item is to be inserted.
 * \param   obj     Object to insert at index.
 * \param   index   Index before which the item is to be inserted (if -ve,
 *                  add at end).
 */
void mango_list_insert_at(MangoList *list, MangoObject *obj, int index)
{
    if (list->__prototype__->insertAtFunc != NULL)
        list->__prototype__->insertAtFunc(list, obj, index);
}

/**
 * Removes the item at a particular index.
 * \param   list    List from which item is to be removed.
 * \param   index   Index at which the item is to be removed.
 */
void mango_list_remove_at(MangoList *list, int index)
{
    if (list->__prototype__->removeAtFunc != NULL)
        list->__prototype__->removeAtFunc(list, index);
}

/**
 * Finds the first index of an object from a given position.
 * \param   list    List to search.
 * \param   obj     Object to be searched for.
 * \param   pos     Index to search form.
 * \return -1 if object is not found, otherwise index at which it is
 * located.
 */
int mango_list_index_of(MangoList *list, MangoObject *obj, int from)
{
    if (list->__prototype__->indexOfFunc != NULL)
        list->__prototype__->indexOfFunc(list, obj, from);
    return -1;
}

/**
 * Finds the last index of an object from a given position.
 * \param   list    List to search.
 * \param   obj     Object to be searched for.
 * \param   pos     Index to search form.
 * \return -1 if object is not found, otherwise index at which it is
 * located.
 */
int mango_list_last_index_of(MangoList *list, MangoObject *obj, int from)
{
    if (list->__prototype__->lastIndexOfFunc != NULL)
        list->__prototype__->lastIndexOfFunc(list, obj, from);
    return -1;
}


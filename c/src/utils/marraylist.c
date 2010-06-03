#include "mangopub.h"

void mango_arraylist_dealloc(MangoArrayList *array);
void mango_arraylist_clear(MangoArrayList *array);
BOOL mango_arraylist_is_empty(MangoArrayList *array);
int mango_arraylist_size(MangoArrayList *array);
MangoObject *mango_arraylist_get_int_attr(MangoArrayList *array, int index);
void mango_arraylist_set_at(MangoArrayList *array, int index, MangoObject *newitem);
void mango_arraylist_remove_at(MangoArrayList *array, int index);
void mango_arraylist_insert_at(MangoArrayList *array, MangoObject *item, int index);
void mango_arraylist_sinsert(MangoArrayList *array, int index, MangoObject **src, int srclen);
void mango_arraylist_remove_range(MangoArrayList *array, int from, int to);
BOOL mango_arraylists_are_equal(const MangoArrayList *list1, const MangoArrayList *list2);

/**
 * The default array prototype.
 */
DECLARE_PROTO_FUNC(mango_arraylist_prototype, MangoListPrototype, MangoArrayListPrototype, 
    ((MangoPrototype *)&__proto__)->deallocFunc             = (ObjectDeallocFunc)mango_arraylist_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc              = (ObjectEqualsFunc)mango_arraylists_are_equal;
    ((MangoPrototype *)&__proto__)->getIntAttrFunc          = (ObjectGetIntAttrFunc)mango_arraylist_get_int_attr;
    ((MangoCollectionPrototype *)&__proto__)->clearFunc     = (CollectionClearFunc)mango_arraylist_clear;
    ((MangoCollectionPrototype *)&__proto__)->isEmptyFunc   = (CollectionIsEmptyFunc)mango_arraylist_is_empty;
    ((MangoCollectionPrototype *)&__proto__)->sizeFunc      = (CollectionSizeFunc)mango_arraylist_size;
    ((MangoListPrototype *)&__proto__)->insertAtFunc        = (ListInsertAtFunc)mango_arraylist_insert_at;
    ((MangoListPrototype *)&__proto__)->removeAtFunc        = (ListRemoveAtFunc)mango_arraylist_remove_at;
    ((MangoListPrototype *)&__proto__)->setAtFunc           = (ListSetAtFunc)mango_arraylist_set_at;
);

/**
 * Creates a new array with a given capacity.
 */
MangoArrayList *mango_arraylist_new()
{
    return mango_arraylist_init(NEW(MangoArrayList), mango_arraylist_prototype());
}

/**
 * Initialises an array list.
 */
MangoArrayList *mango_arraylist_init(MangoArrayList *list, MangoListPrototype *proto)
{
    if (proto == NULL)
        proto = mango_arraylist_prototype();
    mango_list_init((MangoList *)list, proto);
    list->items     = NULL;
    list->length    = 0;
    list->capacity  = 0;
    return list;
}

/*
 * Initialise an array.
 */
void mango_arraylist_reserve(MangoArrayList *array, int capacity)
{
    assert(array != NULL);

    if (capacity > array->capacity)
    {
        array->items    = realloc(array->items, sizeof(MangoObject *) * capacity);
        array->capacity = capacity;
    }
}

/*
 * Return the element at a given index.
 */
MangoObject *mango_arraylist_get_int_attr(MangoArrayList *array, int index)
{
    return array->items[index];
}

/*
 * Sets the item at a given index and returns the old item.
 */
void mango_arraylist_set_at(MangoArrayList *array, int index, MangoObject *newitem)
{
    MangoObject *olditem = array->items[index];
    if (olditem != newitem)
    {
        array->items[index] = OBJ_INCREF(newitem);
    }
    OBJ_DECREF(olditem);
}

/*
 * Insert an item at a given index in the array
 *
 * -ve index indicates an append operation
 */
void mango_arraylist_insert_at(MangoArrayList *array, MangoObject *item, int index)
{
    mango_arraylist_reserve(array, array->length + 1);
    OBJ_INCREF(item);
    if (index < 0 || index >= array->length)
    {
        array->items[array->length] = item;
    }
    else
    {
        memmove(array->items + index + 1, array->items + index, array->length - index);
        array->items[index] = item;
    }
    array->length++;
}

/*
 * Insert a set of value at a given index.
 *
 * -ve index indicates an append operation
 */
void mango_arraylist_sinsert(MangoArrayList *array, int index, MangoObject **src, int srclen)
{
    mango_arraylist_reserve(array, array->length + srclen);
    if (index >= 0 && index < array->length)
    {
        memmove(array->items + index + srclen, array->items + index, array->length - index);
    }
    memcpy(array + index, src, srclen * sizeof(MangoObject *));
    array->length += srclen;

    // increment ref count of all objects copied
    for (int i = 0;i < srclen;i++) OBJ_INCREF(src[i]);
}

/*
 * Remove an item at a given index
 */
void mango_arraylist_remove_at(MangoArrayList *array, int index)
{
    MangoObject *removed = array->items[index];
    memmove(array->items + index, array->items + index + 1, array->length - (index + 1));
    array->length--;
    if (removed != NULL)
        OBJ_DECREF(removed);
}

/*
 * Remove a range of values in an array.
 */
void mango_arraylist_remove_range(MangoArrayList *array, int from, int to)
{
    if (from > to)
    {
        int a = to;
        to = from;
        from = a;
    }
    for (int i = from;i <= to;i++) OBJ_DECREF(array->items[i]);
    memmove(array->items + from, array->items + to + 1, array->length - (to + 1));
    array->length -= (1 + to - from);
}

/*
 * Clear an array without freeing the array itself.
 */
void mango_arraylist_clear(MangoArrayList *array)
{
    if (array && array->items)
    {
        for (int i = 0;i < array->length;i++)
        {
            if (array->items[i] != NULL)
                OBJ_DECREF(array->items[i]);
        }
        array->length   = 0;
        // keep the buffer and capacity unchanged
    }
}

/*
 * Destroys an array
 */
void mango_arraylist_dealloc(MangoArrayList *array)
{
    if (array && array->items)
    {
        for (int i = 0;i < array->length;i++)
        {
            if (array->items[i] != NULL)
                OBJ_DECREF(array->items[i]);
        }
        free(array->items);
        free(array);
    }
    mango_object_dealloc((MangoObject *)array);
}

/**
 * Returns if the array is empty or not.
 */
BOOL mango_arraylist_is_empty(MangoArrayList *array)
{
    return array->length == 0;
}

/**
 * Returns the array size.
 */
int mango_arraylist_size(MangoArrayList *array)
{
    return array->length;
}

/**
 * Compares the contents of two arrays and returns if they are equal.
 */
BOOL mango_arraylists_are_equal(const MangoArrayList *array1, const MangoArrayList *array2)
{
    if (array1 == array2)
    {
        return true;
    }

    int length1 = array1 == NULL ? 0 : array1->length;
    int length2 = array2 == NULL ? 0 : array2->length;
    if (length1 != length2)
    {
        return false;
    }
    else if (array1 == NULL || array2 == NULL)
    {
        return false;
    }

    for (int i = 0;i < array1->length;i++)
    {
        if (!OBJ_EQUALS(array1->items[i], array2->items[i]))
            return false;
    }
    return true;
}


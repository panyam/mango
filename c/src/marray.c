
#include "marray.h"
#include "mmemutils.h"

/**
 * Creates a new array with a given capacity.
 */
MangoArray *mango_array_new()
{
    return ZNEW(MangoArray);
}

/*
 * Initialise an array.
 */
void mango_array_reserve(MangoArray *array, int capacity)
{
    assert(array != NULL);

    if (capacity > array->capacity)
    {
        array->items    = realloc(array->items, sizeof(void*) * capacity);
        array->capacity = capacity;
    }
}

/*
 * Return the element at a given index.
 */
void * mango_array_itemat(MangoArray *array, int index)
{
    return array->items[index];
}

/*
 * Sets the item at a given index and returns the old item.
 */
void *mango_array_set_itemat(MangoArray *array, int index, void *newitem)
{
    void *olditem = array->items[index];
    array->items[index] = newitem;
    return olditem;
}

/*
 * Insert an item at a given index in the array
 *
 * -ve index indicates an append operation
 */
void mango_array_insert(MangoArray *array, void *item, int index)
{
    mango_array_reserve(array, array->length + 1);
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
void mango_array_sinsert(MangoArray *array, int index, void **src, int srclen)
{
    mango_array_reserve(array, array->length + srclen);
    if (index >= 0 && index < array->length)
    {
        memmove(array->items + index + srclen, array->items + index, array->length - index);
    }
    memcpy(array + index, src, srclen * sizeof(void *));
    array->length += srclen;
}

/*
 * Remove an item at a given index
 */
void *mango_array_remove(MangoArray *array, int index)
{
    void *removed = array->items[index];
    memmove(array->items + index, array->items + index + 1, array->length - (index + 1));
    array->length--;
    return removed;
}

/*
 * Remove a range of values in an array.
 */
void mango_array_remove_range(MangoArray *array, int from, int to)
{
    if (from > to)
    {
        int a = to;
        to = from;
        from = a;
    }
    memmove(array->items + from, array->items + to + 1, array->length - (to + 1));
    array->length -= (1 + to - from);
}

/*
 * Clear an array without freeing the array itself (but the buffer is
 * freed)
 */
void mango_array_clear(MangoArray *array)
{
    if (array && array->items)
    {
        free(array->items);
        array->items    = NULL;
        array->length   = 0;
        array->capacity = 0;
    }
}

/*
 * Destroys an array
 */
void mango_array_free(MangoArray *array)
{
    if (array)
    {
        free(array->items);
        free(array);
    }
}


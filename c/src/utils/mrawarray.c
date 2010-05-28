
#include "mrawarray.h"
#include "mmemutils.h"

/**
 * Creates a new array with a given capacity.
 */
MangoRawArray *mango_rawarray_new()
{
    return ZNEW(MangoRawArray);
}

/*
 * Initialise an array.
 */
void mango_rawarray_reserve(MangoRawArray *array, int capacity)
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
void * mango_rawarray_itemat(MangoRawArray *array, int index)
{
    return array->items[index];
}

/*
 * Sets the item at a given index and returns the old item.
 */
void *mango_rawarray_set_itemat(MangoRawArray *array, int index, void *newitem)
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
void mango_rawarray_insert(MangoRawArray *array, void *item, int index)
{
    mango_rawarray_reserve(array, array->length + 1);
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
void mango_rawarray_sinsert(MangoRawArray *array, int index, void **src, int srclen)
{
    mango_rawarray_reserve(array, array->length + srclen);
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
void *mango_rawarray_remove(MangoRawArray *array, int index)
{
    void *removed = array->items[index];
    memmove(array->items + index, array->items + index + 1, array->length - (index + 1));
    array->length--;
    return removed;
}

/*
 * Remove a range of values in an array.
 */
void mango_rawarray_remove_range(MangoRawArray *array, int from, int to)
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
 * Clear an array without freeing the array itself.
 */
void mango_rawarray_clear(MangoRawArray *array, void (*deletor)(void *))
{
    if (array && array->items)
    {
        if (deletor != NULL)
        {
            for (int i = 0;i < array->length;i++)
            {
                if (array->items[i] != NULL)
                    deletor(array->items[i]);
            }
        }
        array->length   = 0;
        // keep the buffer and capacity unchanged
    }
}

/*
 * Destroys an array
 */
void mango_rawarray_free(MangoRawArray *array, void (*deletor)(void *))
{
    if (array && array->items)
    {
        if (deletor != NULL)
        {
            for (int i = 0;i < array->length;i++)
            {
                if (array->items[i] != NULL)
                    deletor(array->items[i]);
            }
        }
        free(array->items);
        free(array);
    }
}


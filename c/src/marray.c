
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "marray.h"

/*
 * Initialise an array.
 */
MangoArray * mango_array_reserve(MangoArray *array, int capacity)
{
    if (array == NULL)
    {
        array = malloc(sizeof(MangoArray));

        if (array == NULL)
            return NULL;

        memset(array, 0, sizeof(MangoArray));
    }

    if (capacity > array->capacity)
    {
        array->items    = realloc(array, sizeof(void*) * capacity);
        array->capacity = capacity;
    }

    return array;
}

/*
 * Return the element at a given index.
 */
void * mango_array_itemat(MangoArray *array, int index)
{
    return array->items[index];
}

/*
 * Insert an item at a given index in the array
 *
 * -ve index indicates an append operation
 */
MangoArray * mango_array_insert(MangoArray *array, void *item, int index)
{
    array = mango_array_reserve(array, array->length + 1);
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
    return array;
}

/*
 * Insert a set of value at a given index.
 *
 * -ve index indicates an append operation
 */
MangoArray *  mango_array_sinsert(MangoArray *array, int index, void **src, int srclen)
{
    array = mango_array_reserve(array, array->length + srclen);
    if (index >= 0 && index < array->length)
    {
        memmove(array->items + index + srclen, array->items + index, array->length - index);
    }
    memcpy(array + index, src, srclen * sizeof(void *));
    array->length += srclen;
    return array;
}

/*
 * Remove an item at a given index
 */
MangoArray * mango_array_remove(MangoArray *array, int index)
{
    memmove(array->items + index, array->items + index + 1, array->length - (index + 1));
    array->length--;
    return array;
}

/*
 * Remove a range of values in an array.
 */
MangoArray * mango_array_rremove(MangoArray *array, int from, int to)
{
    if (from > to)
    {
        int a = to;
        to = from;
        from = a;
    }
    memmove(array->items + from, array->items + to + 1, array->length - (to + 1));
    array->length -= (1 + to - from);
    return array;
}

/*
 * Resets an array without freeing the array itself (but the buffer is
 * freed)
 */
void mango_array_reset(MangoArray *array)
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


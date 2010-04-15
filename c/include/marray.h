
#ifndef __MANGO_ARRAY_H__
#define __MANGO_ARRAY_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Array structures.
 */
struct MangoArray
{
    /*
     * Members
     */
    void **     items;
    unsigned    length;
    unsigned    capacity;
};

/**
 * Creates a new array.
 */
extern MangoArray *mango_array_new();

/*
 * Destroys an array
 */
extern void mango_array_free(MangoArray *array);

/*
 * Clear an array without freeing the array itself (but the buffer is
 * freed)
 */
extern void mango_array_clear(MangoArray *array);

/*
 * Initialise an array.
 */
extern void mango_array_reserve(MangoArray *array, int capacity);

/*
 * Return the element at a given index.
 */
extern void *mango_array_itemat(MangoArray *array, int index);

/*
 * Sets the item at a given index and returns the old item.
 */
extern void *mango_array_set_itemat(MangoArray *array, int index, void *newitem);

/*
 * Insert an item at a given index in the array
 *
 * -ve index indicates an append operation
 */
extern void mango_array_insert(MangoArray *array, void *item, int index);

/*
 * Insert a set of value at a given index.
 *
 * -ve index indicates an append operation
 */
extern void mango_array_sinsert(MangoArray *array, int index, void **src, int srclen);

/*
 * Remove an item at a given index
 */
extern void *mango_array_remove(MangoArray *array, int index);

/*
 * Remove a range of values in an array.
 */
extern void mango_array_remove_range(MangoArray *array, int from, int to);

#ifdef __cplusplus
}
#endif

#endif


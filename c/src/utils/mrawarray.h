
#ifndef __MANGO_RAW_ARRAY_H__
#define __MANGO_RAW_ARRAY_H__

#include "core/mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Array structures.
 */
struct MangoRawArray
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
extern MangoRawArray *mango_rawarray_new();

/*
 * Destroys an array
 */
extern void mango_rawarray_free(MangoRawArray *array, void (*deletor)(void *));

/*
 * Clear an array without freeing the array itself (but the buffer is
 * freed)
 */
extern void mango_rawarray_clear(MangoRawArray *array, void (*deletor)(void *));

/*
 * Initialise an array.
 */
extern void mango_rawarray_reserve(MangoRawArray *array, int capacity);

/*
 * Return the element at a given index.
 */
extern void *mango_rawarray_itemat(MangoRawArray *array, int index);

/*
 * Sets the item at a given index and returns the old item.
 */
extern void *mango_rawarray_set_itemat(MangoRawArray *array, int index, void *newitem);

/*
 * Insert an item at a given index in the array
 *
 * -ve index indicates an append operation
 */
extern void mango_rawarray_insert(MangoRawArray *array, void *item, int index);

/*
 * Insert a set of value at a given index.
 *
 * -ve index indicates an append operation
 */
extern void mango_rawarray_sinsert(MangoRawArray *array, int index, void **src, int srclen);

/*
 * Remove an item at a given index
 */
extern void *mango_rawarray_remove(MangoRawArray *array, int index);

/*
 * Remove a range of values in an array.
 */
extern void mango_rawarray_remove_range(MangoRawArray *array, int from, int to);

#ifdef __cplusplus
}
#endif

#endif


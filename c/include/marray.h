
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

/*
 * Initialise an array.
 */
MangoArray *  mango_array_reserve(MangoArray *array, int capacity);

/*
 * Return the element at a given index.
 */
void *      mango_array_itemat(MangoArray *array, int index);

/*
 * Insert an item at a given index in the array
 *
 * -ve index indicates an append operation
 */
MangoArray *  mango_array_insert(MangoArray *array, void *item, int index);

/*
 * Insert a set of value at a given index.
 *
 * -ve index indicates an append operation
 */
MangoArray *  mango_array_sinsert(MangoArray *array, int index, void **src, int srclen);

/*
 * Remove an item at a given index
 */
MangoArray *  mango_array_remove(MangoArray *array, int index);

/*
 * Remove a range of values in an array.
 */
MangoArray *  mango_array_rremove(MangoArray *array, int from, int to);

/*
 * Resets an array without freeing the array itself (but the buffer is
 * freed)
 */
void mango_array_reset(MangoArray *array);

/*
 * Destroys an array
 */
void        mango_array_free(MangoArray *array);

#ifdef __cplusplus
}
#endif

#endif


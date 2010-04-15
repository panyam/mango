
#ifndef __MANGO_VALUE_H__
#define __MANGO_VALUE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MV_NULL,
    MV_BOOL,
    MV_INT,
    MV_DOUBLE,
    MV_STRING,
    MV_ARRAY,
    MV_TABLE,
    MV_ITERATOR,
} MangoValueType;

/**
 * Generic value objects.
 */
struct MangoValue
{
    // must be non-zero
    MangoValueType valueType;
    void *valueData;
};

extern MangoValue NULL_VALUE;

/**
 * Tells if a value is valid.
 */
extern BOOL mango_value_is_valid(const MangoValue *value);

/**
 * Makes a new mango value.
 * \param   vType   Type of the value.
 * \param   vData   Data of the value.
 */
extern MangoValue mango_value_make(MangoValueType type, void *value);

struct MangoValueIterator 
{
    MangoValue      source;
};

/**
 * A value iterator object.
 */
extern MangoValueIterator *mango_valueiterator_new(MangoValue value);

/**
 * Tells if a value iterator has more items in it.
 */
extern BOOL mango_valueiterator_has_next(MangoValueIterator *iter);

/**
 * Gets the next item in the value iterator.
 */
extern void *mango_valueiterator_next(MangoValueIterator *iter);


extern int mango_valueiterator_unpack(MangoValueIterator *iter,
                                      int numvals,
                                      MangoValue *values);

#ifdef __cplusplus
}
#endif

#endif


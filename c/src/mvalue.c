
#include "mvalue.h"
#include "mmemutils.h"

MangoValue NULL_VALUE = { 0, 0 };

/**
 * Tells if a value is valid.
 */
BOOL mango_value_is_valid(const MangoValue *value)
{
    return value->valueType != 0;
}

/**
 * Makes a new mango value.
 * \param   vType   Type of the value.
 * \param   vData   Data of the value.
 */
MangoValue mango_value_make(MangoValueType vType, void *vData)
{
    MangoValue value;
    value.valueType = vType;
    value.valueData = vData;
    return value;
}

/**
 * Creates a new value iterator object.
 */
MangoValueIterator *mango_valueiterator_new(MangoValue value)
{
    MangoValueIterator *mvi = NEW(MangoValueIterator);
    mvi->source = value;
    return mvi;
}

/**
 * Sets the source object of the value iterator.
 */
void mango_valueiterator_set(MangoValueIterator *mvi, MangoValue value)
{
    mvi->source = value;
}

/**
 * Tells if a value iterator has more items in it.
 */
BOOL mango_valueiterator_has_next(MangoValueIterator *iter)
{
    return false;
}

/**
 * Gets the next item in the value iterator.
 */
void *mango_valueiterator_next(MangoValueIterator *iter)
{
    return NULL;
}

/**
 * Unpacks the current value into individual values.
 */
int mango_valueiterator_unpack(MangoValueIterator *iter, int numvals, MangoValue *values)
{
    return 0;
}



#include "mvalue.h"
#include "mmemutils.h"

/**
 * Gets the prototype for all mango values.
 */
MangoPrototype *mango_value_prototype()
{
    return NULL;
}

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
    OBJ_INIT(&value, mango_value_prototype());
    value.valueType     = vType;
    value.valueData     = vData;
    return value;
}

/**
 * Creates a new mango value.
 * \param   vType   Type of the value.
 * \param   vData   Data of the value.
 */
MangoValue *mango_value_new(MangoValueType type, void *value)
{
    MangoValue *out = OBJ_ALLOC(MangoValue, mango_value_prototype);
    out->valueType = type;
    out->valueData = value;
    return out;
}

/**
 * Frees a value created with the mango_value_new method.
 * \param   value   Value to be freed.
 */
void mango_value_free(MangoValue *value)
{
    if (value != NULL)
        free(value);
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


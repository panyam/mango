
#include "mmemutils.h"
#include "mfilter.h"

/**
 * Returns the mango filter prototype.
 */
DECLARE_PROTO_FUNC("Filter", MangoFilterPrototype, mango_filter_prototype,
    ((MangoPrototype *)&__proto__)->deallocFunc = mango_filter_dealloc;
    __proto__.makeInvocationContextFunc = NULL;
    __proto__.makeInstanceContextFunc   = NULL;
);

/**
 * Dealloc's a filter when its refcount reaches 0.
 */
void mango_filter_dealloc(MangoFilter *filter)
{
    mango_object_dealloc((MangoObject *)filter);
}

/**
 * Applies the filter on a value and returns the new value.
 * \param   filter      Filter being applied.
 * \param   input       Input value
 * \param   context     Template Context
 * \param   arguments   Arguments for the application.
 *
 * \return  Value after the filter is applied.
 */
MangoObject *mango_filter_apply(MangoFilter *filter,
                              const MangoObject *input,
                              MangoTemplateContext *context,
                              MangoList *arguments)
{
    if (filter->__prototype__->applyFunc != NULL)
    {
        return filter->__prototype__->applyFunc(filter, input, context, arguments);
    }
    return NULL;
}


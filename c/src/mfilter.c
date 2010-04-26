
#include "mmemutils.h"
#include "mfilter.h"

/**
 * Destroys a filter created with mango_filter_new.
 */
void mango_filter_release(MangoFilter *filter)
{
    mango_object_release((MangoObject *)filter);
}

/**
 * Applies the filter on a value and returns the new value.
 * \param   filter      Filter being applied.
 * \param   input       Input value
 * \param   output      Output value.
 * \param   context     Template Context
 * \param   arguments   Arguments for the application.
 *
 * \return  Output type with the value stored in outValue.
 */
int mango_filter_apply(MangoFilter *filter,
                       const MangoValue *input,
                       MangoValue *output,
                       MangoTemplateContext *context,
                       MangoList *arguments)
{
    if (filter->__prototype__->applyFunc == NULL)
    {
        return -1;
    }
    return filter->__prototype__->applyFunc(filter, input, output, context, arguments);
}


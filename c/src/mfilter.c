
#include "mmemutils.h"
#include "mfilter.h"

void *default_make_context_func(MangoList *arguments)
{
    return NULL;
}

int default_apply_func(void *filter_data, const MangoValue *input, MangoValue *output, MangoTemplateContext *context, MangoList *arguments)
{
    return -1;
}

/**
 * Creates a new filter.
 */
MangoFilter *mango_filter_new(void *data)
{
    MangoFilter *filter                 = NEW(MangoFilter);
    mango_filter_reset(filter, data);
    return filter;
}

/**
 * Resets the filter contents.
 */
void mango_filter_reset(MangoFilter *filter, void *data)
{
    filter->data                        = data;
    filter->deleteFunc                  = free;
    filter->applyFunc                   = default_apply_func;
    filter->makeInvocationContextFunc   = default_make_context_func;
    filter->makeInstanceContextFunc     = default_make_context_func;
}

/**
 * Destroys a filter created with mango_filter_new.
 */
void mango_filter_free(MangoFilter *filter)
{
    if (filter->data != NULL && filter->deleteFunc != NULL)
        filter->deleteFunc(filter->data);
    free(filter);
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
    if (filter->applyFunc == NULL || filter->data == NULL)
    {
        return -1;
    }
    return filter->applyFunc(filter->data, input, output, context, arguments);
}


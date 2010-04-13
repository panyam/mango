
#include "mfilter.h"
#include "maddfilter.h"

int mango_addfilter_apply(void *data, const MangoValue *input, MangoValue *output, MangoTemplateContext *context, MangoList *arguments)
{
    return -1;
}

/**
 * Creates a new "add" filter.
 */
void mango_addfilter_init(const MangoString *name, MangoFilter *filter, ...)
{
    mango_filter_reset(filter, NULL);
    filter->applyFunc = mango_addfilter_apply;
}


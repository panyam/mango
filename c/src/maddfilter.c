
#include "mfilter.h"
#include "maddfilter.h"

/**
 * Creates a new "add" filter.
 */
MangoFilter *mango_addfilter_new(const MangoString *name, ...)
{
    static MangoFilter add_filter;
    static BOOL filterInited = false;

    if (!filterInited)
    {
        mango_filter_reset(&add_filter, NULL);
        filterInited = true;
    }

    return &add_filter;
}


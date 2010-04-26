
#include "mfilter.h"
#include "maddfilter.h"
#include "mmemutils.h"

int mango_addfilter_apply(MangoFilter *filter, const MangoValue *input,
                          MangoValue *output, MangoTemplateContext *context,
                          MangoList *arguments);

/**
 * Returns the prototype for the add filter.
 */
MangoFilterPrototype *mango_addfilter_prototype()
{
    static BOOL initialised = false;
    static MangoFilterPrototype PROTO;
    if (!initialised)
    {
        PROTO.__base__.name             = strdup("MangoAddFilter");
        PROTO.__base__.deleteFunc       = NULL;
        PROTO.__base__.equalsFunc       = NULL;
        PROTO.__base__.compareFunc      = NULL;
        PROTO.applyFunc                 = mango_addfilter_apply;
        PROTO.makeInvocationContextFunc = NULL;
        PROTO.makeInstanceContextFunc   = NULL;
        initialised = true;
    }
    return &PROTO;
}

int mango_addfilter_apply(MangoFilter *filter, const MangoValue *input,
                          MangoValue *output, MangoTemplateContext *context,
                          MangoList *arguments)
{
    return -1;
}

/**
 * Creates a new "add" filter.
 */
MangoFilter *mango_addfilter_new(const MangoString *name, ...)
{
    MangoFilter *filter     = ZNEW(MangoFilter);
    filter->__prototype__   = mango_addfilter_prototype();
    filter->__refCount__    = 1;
    return filter;
}


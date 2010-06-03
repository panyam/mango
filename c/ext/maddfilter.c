
#include "mangopub.h"
#include "maddfilter.h"

MangoObject *mango_addfilter_apply(MangoFilter *filter, const MangoObject *input,
                                   MangoTemplateContext *context,
                                   MangoList *arguments);

/**
 * Returns the prototype for the add filter.
 */
DECLARE_PROTO_FUNC(mango_addfilter_prototype, MangoFilterPrototype, mango_filter_prototype(), 
    __proto__.applyFunc = mango_addfilter_apply;
);

/**
 * The apply method of the add filter.
 */
MangoObject *mango_addfilter_apply(MangoFilter *filter, const MangoObject *input,
                                   MangoTemplateContext *context,
                                   MangoList *arguments)
{
    return NULL;
}

/**
 * Creates a new "add" filter.
 */
MangoFilter *mango_addfilter_default()
{
    static MangoFilter addfilter;
    static BOOL initialised = false;
    if (!initialised)
    {
        OBJ_INIT(&addfilter, mango_addfilter_prototype());
        initialised = true;
    }
    return &addfilter;
}


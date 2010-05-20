
#include "mfilter.h"
#include "maddfilter.h"
#include "mmemutils.h"

int mango_addfilter_apply(MangoFilter *filter, const MangoValue *input,
                          MangoValue *output, MangoTemplateContext *context,
                          MangoList *arguments);

/**
 * Returns the prototype for the add filter.
 */
DECLARE_PROTO_FUNC("AddFilter", MangoFilterPrototype, mango_addfilter_prototype,
    __proto__.applyFunc = mango_addfilter_apply;
);

/**
 * The apply method of the add filter.
 */
int mango_addfilter_apply(MangoFilter *filter, const MangoValue *input,
                          MangoValue *output, MangoTemplateContext *context,
                          MangoList *arguments)
{
    return -1;
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


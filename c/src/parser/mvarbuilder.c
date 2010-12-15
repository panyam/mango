
#include "mangopub.h"

/**
 * Create a new variable instance.
 */
MangoVar *mango_varbuilder_new_var(MangoVarBuilder *varbuilder, MangoContext *ctx, MangoString *value)
{
    if (varbuilder->__prototype__->newVarFunc != NULL)
        return varbuilder->__prototype__->newVarFunc(varbuilder, ctx, value);
    return NULL;
}



#ifndef __MANGO_VARBUILDER_H__
#define __MANGO_VARBUILDER_H__

#include "core/mobject.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Base prototype for all tag parsers.
 */
INHERIT_STRUCT(MangoVarBuilderPrototype, MangoPrototype,
    //! Parses the node
    MangoVar *(*newVarFunc)(MangoVarBuilder *   tagparser,
                            MangoContext *      ctx,
                            MangoString *       value);
);

/**
 * Super class of all tag parsers.
 */
DECLARE_CLASS(MangoVarBuilder, MangoVarBuilderPrototype);

/**
 * Create a new variable instance.
 */
MangoVar *mango_varbuilder_new_var(MangoVarBuilder *varbuilder, MangoContext *ctx, MangoString *value);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_FILTER_NODE_H__
#define __MANGO_FILTER_NODE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoFilterNode
{
    const MangoFilter * filter;
    MangoList *         arguments;
};

/**
 * Creates a new filter node given a filter.
 */
extern MangoFilterNode *mango_filternode_new(const MangoFilter *f);

/**
 * Frees a filter node.
 */
extern void mango_filternode_free(MangoFilterNode *fnode);

/**
 * Tells if two filter nodes are equal.
 */
extern BOOL mango_filternodes_are_equal(const MangoFilterNode *fn1, const MangoFilterNode *fn2);

/**
 * Applies a filter arguments to a filter and returns the value.
 */
extern int mango_filternode_apply(MangoFilterNode *fnode, int inType, void *inValue, void **outValue, MangoTemplateContext *context);

/**
 * Adds an argument to a filter node.
 *
 * \param   fnode   Filter node to add the variable to.
 * \param   mvar    Argument to add.
 */
extern void mango_filternode_add_arg(MangoFilterNode *fnode, MangoVariable *mvar);

#ifdef __cplusplus
}
#endif

#endif


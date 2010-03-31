
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

/**
 * Reads a list of filter expressions with the parser and returns a list.
 *
 * \param   parser  The parser doing the parsing.
 * \param   error   Error value to be set in case of failure.
 *
 * \return  A MangoList with filternode instances.  When an error occurs,
 * the error variable will be set (if it is non NULL) and the output 
 * list can be non-null to indicate filter expressions read upto the point
 * of error.  It is the caller's responsibility to destroy the read
 * instances.
 */
extern MangoList *mango_filternode_extract_filter_list(MangoParser *parser, MangoError **error);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_FILTER_NODE_H__
#define __MANGO_FILTER_NODE_H__

#include "core/mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_CLASS(MangoFilterNode, MangoPrototype,
    MangoFilter *   filter;
    MangoList *     arguments;
);

/**
 * Creates a new filter node given a filter.
 */
extern MangoFilterNode *mango_filternode_new(MangoFilter *f);

/**
 * Initialise an created filter node given a filter.
 */
extern MangoFilterNode *mango_filternode_init(MangoFilter *f, MangoFilterNode *node, MangoPrototype *proto);

/**
 * Frees a filter node.
 */
extern void mango_filternode_dealloc(MangoFilterNode *fnode);

/**
 * Tells if two filter nodes are equal.
 */
extern BOOL mango_filternodes_are_equal(const MangoFilterNode *fn1, const MangoFilterNode *fn2);

/**
 * Applies a filter arguments to a filter and returns the value.
 */
extern MangoObject *mango_filternode_apply(MangoFilterNode *fnode, const MangoObject *input, MangoTemplateContext *context);

/**
 * Adds an argument to a filter node.
 *
 * \param   fnode   Filter node to add the var to.
 * \param   mvar    Argument to add.
 *
 * @test(TestFilterNodeAddArg)
 * MangoFilter *filter = ZNEW(MangoFilter);
 * OBJ_INIT(filter, mango_filter_prototype());
 * MangoFilterNode *filternode = mango_filternode_new(filter);
 * CHECK_EQUAL(1, OBJ_REFCOUNT(filternode));
 * CHECK_EQUAL(2, OBJ_REFCOUNT(filter));
 * CHECK(NULL == filternode->arguments);
 * MangoString *varname = (MangoString *)mango_rcstring_new("a", -1, NULL);
 * MangoVar *var = mango_var_new(varname, false, NULL);
 * mango_filternode_add_arg(filternode, var);
 * CHECK_EQUAL(2, OBJ_REFCOUNT(var));
 * CHECK_EQUAL(2, OBJ_REFCOUNT(varname));
 *
 * CHECK_EQUAL(false, OBJ_DECREF(filternode));
 * CHECK_EQUAL(false, OBJ_DECREF(filter));
 * @endtest
 */
extern void mango_filternode_add_arg(MangoFilterNode *fnode, MangoVar *mvar);

/**
 * Reads a list of filter expressions with the parser and returns a list.
 * Also the final '}}' is discarded.
 *
 * \param   ctx     Parser context containing necessary items.
 * \param   filters List storing all the parsed filters.
 * \param   error   Error value to be set in case of failure.
 *
 * \return true if filters were read successfully, false on error.  On
 * error, the error var might be set if it is provided.  On error, the
 * output list will still contain extracted filters upto the point of error
 * and it is the caller's responsibility to destroy the read filters.
 */
extern BOOL mango_filternode_extract_filter_list(MangoParserContext *ctx,
                                                 MangoList *filters,
                                                 MangoError **error);

/**
 * Extracts the next filter expression in the filter list.  This assumes
 * that the next token being read will be an identifier indicating the name
 * of the filter.
 * 
 * Filter expressions are of the form: 
 *      ident
 *      ident COLON value
 *      ident COLON OPEN_PAREN value_list CLOSE_PAREN
 *
 * \param   ctx     Parser context containing necessary items.
 * \param   error   Optional storage for the error if any.
 *
 * \return A filternode instance on success, otherwise NULL.
 */
extern MangoFilterNode *mango_filternode_extract_with_parser(MangoParserContext *ctx,
                                                             MangoError **error);

/**
 * Parses the arguments of a filter expression.  This assumes that next token
 * that will be read is either a "(" or a var.
 *
 * \param   ctx     Parser context containing necessary items.
 * \param   filternode  The filter node to which the arguments are to be
 *                      added.
 * \param   error       Error to be set in case of failure.
 *
 * \return TRUE if one or more arguments were added to the filter node,
 * false otherwise.
 */
extern BOOL mango_filternode_parse_filter_args(MangoParserContext *ctx,
                                               MangoFilterNode *filternode,
                                               MangoError **error);

#ifdef __cplusplus
}
#endif

#endif


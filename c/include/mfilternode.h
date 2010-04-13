
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
extern int mango_filternode_apply(MangoFilterNode *fnode, const MangoValue *input, MangoValue *output, MangoTemplateContext *context);

/**
 * Adds an argument to a filter node.
 *
 * \param   fnode   Filter node to add the variable to.
 * \param   mvar    Argument to add.
 */
extern void mango_filternode_add_arg(MangoFilterNode *fnode, MangoVariable *mvar);

/**
 * Reads a list of filter expressions with the parser and returns a list.
 * Also the final '}}' is discarded.
 *
 * \param   parser      The parser doing the parsing.
 * \param   filters     List storing all the parsed filters.
 * \param   filterlib   Filter library to extract filters from.
 * \param   error       Error value to be set in case of failure.
 *
 * \return true if filters were read successfully, false on error.  On
 * error, the error variable might be set if it is provided.  On error, the
 * output list will still contain extracted filters upto the point of error
 * and it is the caller's responsibility to destroy the read filters.
 */
extern BOOL mango_filternode_extract_filter_list(MangoParser *parser,
                                                 MangoList *filters,
                                                 MangoFilterLibrary *filterlib,
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
 * \param   parser  Parser doing the parsing.
 * \param   lib     Filter library from which to fetch the filters.
 * \param   error   Optional storage for the error if any.
 *
 * \return A filternode instance on success, otherwise NULL.
 */
extern MangoFilterNode *mango_filternode_extract_with_parser(MangoParser *parser,
                                                             MangoFilterLibrary *lib,
                                                             MangoError **error);

/**
 * Parses the arguments of a filter expression.  This assumes that next token
 * that will be read is either a "(" or a variable.
 *
 * \param   parser      Parser doing the parsing!
 * \param   filternode  The filter node to which the arguments are to be
 *                      added.
 * \param   error       Error to be set in case of failure.
 *
 * \return TRUE if one or more arguments were added to the filter node,
 * false otherwise.
 */
extern BOOL mango_filternode_parse_filter_args(MangoParser *parser,
                                               MangoFilterNode *filternode,
                                               MangoError **error);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_VARIABLE_NODE_H__
#define __MANGO_VARIABLE_NODE_H__

#include "mnode.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoVarNode, MangoNode,
    MangoVariable * variable;
    MangoList *     filterNodes;
);

/**
 * Creates a new mango node list.
 */
extern MangoVarNode *mango_varnode_new(MangoVariable *mvar, MangoList *filters);

/**
 * Initialises a variable node with a variable and a list of filter.
 * \param   varnode     Variable node to be initialised/reset.
 * \param   mvar        Variable to set for the var node.
 * \param   filters     List of filter nodes to be set to the variable.
 */
extern MangoVarNode *mango_varnode_init(MangoVarNode *varnode, MangoVariable *mvar, MangoList *filters);

/**
 * Extracts and builds a variable node with parser.
 *
 * Variable Nodes have the following structure:
 *
 * VariableNode :=      OPEN_VARIABLE_NODE var_exp CLOSE_VARIABLE_NODE 
 *                  |   OPEN_VARIABLE_NODE var_exp filter_list CLOSE_VARIABLE_NODE 
 *                  ;
 *
 * var_exp  :=      ident
 *              |   ident DOT var_exp
 *              ;
 *
 * filter_list  := filter_exp
 *              |   filter_exp FILTER_SEPERATOR filter_list
 *              ;
 *
 * filter_exp   := ident 
 *              |  ident COLON ident
 *              |  ident COLON OPEN_PAREN filter_arg_list CLOSE_PAREN
 *              ;
 *
 * filter_arg_list  :=  ident 
 *                  |   ident COMA filter_arg_list
 *                  ;
 *
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Optional error variable to be filled in case of failure.
 *
 * \return  A new Variable node instance.
 */
extern MangoNode *mango_varnode_extract_with_parser(MangoParserContext *ctx, MangoError **error);

/**
 * Adds a new filter node.
 *
 * \param   mnode   Mango (variable) node to add to.
 * \param   fnode   The filter node to add.
 */
extern void mango_varnode_add_filter(MangoVarNode *mnode, MangoFilterNode *fnode);

/**
 * Called when a varnode is to be dealloced.
 */
extern void mango_varnode_dealloc(MangoVarNode *varnode);

/**
 * Compares two mango varnode objects.
 */
extern BOOL mango_varnode_are_equal(const MangoVarNode *mvn1, const MangoVarNode *mvn2);

#ifdef __cplusplus
}
#endif

#endif


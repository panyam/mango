
#ifndef __MANGO_VARIABLE_NODE_H__
#define __MANGO_VARIABLE_NODE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new mango node list.
 */
extern MangoNode *mango_varnode_new(MangoVariable *mvar, MangoList *filter_nodes);

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
 * \param   parser      Parser to extract with.  The parser at this point has
 *                      already read the "{{" token.
 * \param   filterlib   Filter library to fetch filters from.
 * \param   varlib      Variable library to fetch special variables from.
 * \param   error       Optional error variable to be filled in case of failure.
 *
 * \return  A new Variable node instance.
 */
extern MangoNode *mango_varnode_extract_with_parser(MangoParser *parser,
                                                    MangoFilterLibrary *filterlib,
                                                    MangoLibrary *varlib,
                                                    MangoError **error);

/**
 * Adds a new filter node.
 *
 * \param   mnode   Mango (variable) node to add to.
 * \param   fnode   The filter node to add.
 */
extern void mango_varnode_add_filter(MangoNode *mnode, MangoFilterNode *fnode);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_VARIABLE_NODE_H__
#define __MANGO_VARIABLE_NODE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new mango node list.
 */
extern MangoNode *mango_varnode_new(MangoVariable *mvar);

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
 *
 * \param   parser  Parser to extract with.  The parser at this point has
 *                  already read the "{{" token.
 * \return  A new Variable node instance.
 */
extern MangoNode *mango_varnode_extract_with_parser(MangoParser *parser);

#ifdef __cplusplus
}
#endif

#endif


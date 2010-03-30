
#include "mnode.h"
#include "mvariable.h"

typedef struct MangoVarNodeData
{
    MangoVariable * variable;
    MangoList *     filterNodes;
} MangoVarNodeData;

/**
 * Creates a new variable node data object.
 *
 * \param   mvar        Variable to be stored.
 * \param   filternodes A list of filter nodes to be used.
 *
 * \return  A MangoVarNodeData object.
 */
MangoVarNodeData *mango_varnodedata_new(MangoVariable *mvar, MangoList *filterNodes)
{
    MangoVarNodeData *nodedata = (MangoVarNodeData *)malloc(sizeof(MangoVarNodeData *));
    nodedata->variable      = mvar;
    nodedata->filterNodes   = filterNodes;
    return nodedata;
}

/**
 * Frees a MangoVarNodeData object created with mango_varnodedata_new.
 * \param data  MangoVarNodeData object to be destroyed.
 */
void mango_varnodedata_free(MangoVarNodeData *data)
{
    assert(false);
}

/**
 * Compares and checks if two MangoVarNodeData objects are equal.
 *
 * \param data1     First object to be compared with.
 * \param data2     Second object to be compared to.
 */
BOOL mango_varnodedata_equals(MangoVarNodeData *data)
{
    assert(false);
    return false;
}

/**
 * Creates a new mango node list.
 */
MangoNode *mango_varnode_new(MangoVariable *mvar)
{
    MangoNode *node         = mango_node_new(mango_varnodedata_new(mvar));
    node->nodeClass         = mango_class_for_name("Variable", true);
    node->deleteNodeData    = (DeleteNodeDataCallback)mango_varnodedata_free;
    node->nodeDataEquals    = (NodeDataEqualsCallback)mango_varnodedata_equals;
    return node;
}


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
 * \param   parser  Parser to extract with.  The parser at this point has
 *                  already read the "{{" token.
 * \return  A new Variable node instance.
 */
MangoNode *mango_varnode_extract_with_parser(MangoParser *parser)
{
}


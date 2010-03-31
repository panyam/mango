
#include "mnode.h"
#include "mvariable.h"
#include "mfilternode.h"
#include "mlist.h"
#include "mmemutils.h"

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
    MangoVarNodeData *nodedata  = NEW(MangoVarNodeData);
    nodedata->variable          = mvar;
    nodedata->filterNodes       = filterNodes;
    return nodedata;
}

/**
 * Frees a MangoVarNodeData object created with mango_varnodedata_new.
 * \param data  MangoVarNodeData object to be destroyed.
 */
void mango_varnodedata_free(MangoVarNodeData *data)
{
    if (data->variable != NULL)
        mango_variable_free(data->variable);
    if (data->filterNodes != NULL)
    {
        mango_list_clear(data->filterNodes, mango_filternode_free);
        mango_list_free(data->filterNodes);
    }
    free(data);
}

/**
 * Compares and checks if two MangoVarNodeData objects are equal.
 *
 * \param data1     First object to be compared with.
 * \param data2     Second object to be compared to.
 */
BOOL mango_varnodedata_equals(MangoVarNodeData *data1, MangoVarNodeData *data2)
{
    return mango_variables_are_equal(data1->variable, data2->variable) &&
            mango_lists_are_equal(data1->filterNodes, data2->filterNodes, NULL);
}

/**
 * Creates a new mango node list.
 */
MangoNode *mango_varnode_new(MangoVariable *mvar)
{
    MangoNode *node         = mango_node_new(mango_varnodedata_new(mvar, NULL));
    node->nodeClass         = mango_class_for_name("Variable", true);
    node->deleteNodeData    = (DeleteNodeDataCallback)mango_varnodedata_free;
    node->nodeDataEquals    = (EqualsFunc)mango_varnodedata_equals;
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
    MangoNode *node = mango_varnode_new(NULL);
    return node;

#if 0
    variable = ParseUtils.parseVariable(parser);
    // read the next token - it should be a close or a filter starter
    Token token = parser.peekToken();
    if (token.tokenType == TokenType.TOKEN_FILTER_SEPERATOR)
    {
        filterNodes = ParseUtils.parseFilterList(parser);
        token = parser.peekToken();
    }
    
    if (token == null || token.tokenType != TokenType.TOKEN_CLOSE_VARIABLE)
    {
        parser.throwError("Expected '}}', but found '" + (token == null ? "EOF" : token) + "'");
    }
    else
    {
        // otherwise read and discard the '}}'
        parser.getToken();
    }
#endif
}

/**
 * Adds a new filter node.
 *
 * \param   mnode   Mango (variable) node to add to.
 * \param   fnode   The filter node to add.
 */
void mango_varnode_add_filter(MangoNode *mnode, MangoFilterNode *fnode)
{
    assert(mnode->nodeClass == mango_class_for_name("Variable", true));
    MangoVarNodeData *data = (MangoVarNodeData *)mnode->nodeData;
    if (data->filterNodes == NULL)
    {
        data->filterNodes = mango_list_new();
    }
    mango_list_push_back(data->filterNodes, fnode);
}



#include "mnode.h"
#include "merror.h"
#include "mparser.h"
#include "mparsercontext.h"
#include "mvariable.h"
#include "mfilternode.h"
#include "mlist.h"
#include "mmemutils.h"
#include "mclasses.h"

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
        mango_list_clear(data->filterNodes, (DeleteFunc)mango_filternode_free);
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
            mango_lists_are_equal(data1->filterNodes, data2->filterNodes, (EqualsFunc)mango_filternodes_are_equal);
}

/**
 * Creates a new mango node list.
 */
MangoNode *mango_varnode_new(MangoVariable *mvar, MangoList *filter_nodes)
{
    MangoNode *node         = mango_node_new(mango_varnodedata_new(mvar, filter_nodes));
    node->nodeClass         = mango_class_for_name("Variable", true);
    node->deleteNodeFunc    = (DeleteFunc)mango_varnodedata_free;
    node->nodeEqualsFunc    = (EqualsFunc)mango_varnodedata_equals;
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
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Optional error variable to be filled in case of failure.
 *
 * \return  A new Variable node instance.
 */
MangoNode *mango_varnode_extract_with_parser(MangoParserContext *ctx, MangoError **error)
{
    MangoVariable *variable = mango_variable_extract_with_parser(ctx, error);
    if (variable == NULL)
        return NULL;

    // read the next token - it should be a close or a filter starter
    MangoParser *parser = ctx->parser;
    const MangoToken *token = mango_parser_peek_token(parser, error);
    if (token == NULL)
        return NULL;

    MangoList *filter_nodes = mango_list_new();
    if (token->tokenType == TOKEN_FILTER_SEPERATOR)
    {
        if (mango_filternode_extract_filter_list(ctx, filter_nodes, error))
        {
            token = mango_parser_peek_token(parser, error);
        }
        else
        {
            assert("How do we handle this?" && false);
        }
    }

    if (token == NULL || token->tokenType != TOKEN_CLOSE_VARIABLE)
    {
        mango_error_set(error, -1, "Expected '}}', but found '%s'.",
                            token == NULL ? "EOF" : MangoTokenStrings[token->tokenType]);
    }
    else
    {
        // otherwise read and discard the '}}'
        mango_parser_get_token(parser, error);
    }

    MangoNode *node = NULL;

    // was there an error?
    if (error != NULL && *error != NULL)
    {
        mango_variable_free(variable);
        if (filter_nodes != NULL)
        {
            mango_list_clear(filter_nodes, (DeleteFunc)mango_filternode_free);
            free(filter_nodes);
        }
    }
    else
    {
        if (filter_nodes->size == 0)
        {
            mango_list_free(filter_nodes);
            filter_nodes = NULL;
        }
        node = mango_varnode_new(variable, filter_nodes);
    }
    return node;
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



#include "mvarnode.h"
#include "merror.h"
#include "mparser.h"
#include "mparsercontext.h"
#include "mvar.h"
#include "mfilternode.h"
#include "mlist.h"
#include "mmemutils.h"
#include "mclasses.h"

/**
 * The prototype for mango var nodes.
 */
MangoNodePrototype *mango_varnode_prototype()
{
    DECLARE_PROTO_VARIABLE("VarNode", MangoNodePrototype, varnodePrototype,
        varnodePrototype.nodeCountFunc      = NULL;
        varnodePrototype.getChildNodeFunc   = NULL;
        ((MangoPrototype *)&varnodePrototype)->deallocFunc  = (PrototypeDeallocFunc)mango_varnode_dealloc;
        ((MangoPrototype *)&varnodePrototype)->equalsFunc   = (PrototypeEqualsFunc)mango_varnode_are_equal;
    );
}

/**
 * Creates a new mango node list.
 * \param   mvar        Variable to be stored.
 * \param   filternodes A list of filter nodes to be used.
 *
 * \return  A MangoVarNode object.
 */
MangoVarNode *mango_varnode_new(MangoVariable *mvar, MangoList *filters)
{
    MangoVarNode *mvnode = NEW(MangoVarNode);
    return mango_varnode_init(mvnode, mvar, filters);
}

/**
 * Initialises a variable node with a variable and a list of filter.
 * \param   varnode     Variable node to be initialised/reset.
 * \param   mvar        Variable to set for the var node.
 * \param   filters     List of filter nodes to be set to the variable.
 */
MangoVarNode *mango_varnode_init(MangoVarNode *varnode, MangoVariable *mvar, MangoList *filters)
{
    mango_node_init((MangoNode *)varnode, mango_varnode_prototype());
    varnode->variable       = mvar;
    varnode->filterNodes    = filters;
    return varnode;
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
        OBJ_DECREF(variable);
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
        node = (MangoNode *)mango_varnode_new(variable, filter_nodes);
    }
    return node;
}

/**
 * Adds a new filter node.
 *
 * \param   mnode   Mango (variable) node to add to.
 * \param   fnode   The filter node to add.
 */
void mango_varnode_add_filter(MangoVarNode *mnode, MangoFilterNode *fnode)
{
    if (mnode->filterNodes == NULL)
    {
        mnode->filterNodes = mango_list_new();
    }
    mango_list_push_back(mnode->filterNodes, fnode);
}

/**
 * Called when a varnode is to be dealloced.
 */
void mango_varnode_dealloc(MangoVarNode *varnode)
{
    if (varnode->variable != NULL)
        OBJ_DECREF(varnode->variable);
    if (varnode->filterNodes != NULL)
    {
        mango_list_clear(varnode->filterNodes, (DeleteFunc)mango_filternode_free);
        mango_list_free(varnode->filterNodes);
    }

    // simply call node's dealloc
    mango_node_dealloc((MangoNode *)varnode);
}


/**
 * Compares and checks if two MangoVarNode objects are equal.
 *
 * \param data1     First object to be compared with.
 * \param data2     Second object to be compared to.
 */
BOOL mango_varnode_are_equal(const MangoVarNode *mvn1, const MangoVarNode *mvn2)
{
    return mango_variables_are_equal(mvn1->variable, mvn2->variable) &&
            mango_lists_are_equal(mvn1->filterNodes, mvn2->filterNodes, (EqualsFunc)mango_filternodes_are_equal);
}


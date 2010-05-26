
#include "mvarnode.h"
#include "merror.h"
#include "mparser.h"
#include "mparsercontext.h"
#include "mvar.h"
#include "mfilternode.h"
#include "mlinkedlist.h"
#include "mmemutils.h"
#include "mclasses.h"

/**
 * The prototype for mango var nodes.
 */
DECLARE_PROTO_FUNC("VarNode", MangoNodePrototype, mango_varnode_prototype,
    ((MangoPrototype *)&__proto__)->deallocFunc  = (ObjectDeallocFunc)mango_varnode_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc   = (ObjectEqualsFunc)mango_varnode_are_equal;
);

/**
 * Creates a new mango node list.
 * \param   mvar        Var to be stored.
 * \param   filternodes A list of filter nodes to be used.
 *
 * \return  A MangoVarNode object.
 */
MangoVarNode *mango_varnode_new(MangoVar *mvar, MangoList *filters)
{
    MangoVarNode *mvnode = NEW(MangoVarNode);
    return mango_varnode_init(mvnode, mvar, filters);
}

/**
 * Initialises a var node with a var and a list of filter.
 * \param   varnode     Var node to be initialised/reset.
 * \param   mvar        Var to set for the var node.
 * \param   filters     List of filter nodes to be set to the var.
 */
MangoVarNode *mango_varnode_init(MangoVarNode *varnode, MangoVar *mvar, MangoList *filters)
{
    mango_node_init((MangoNode *)varnode, mango_varnode_prototype());
    varnode->var       = mvar;
    varnode->filterNodes    = filters;
    return varnode;
}

/**
 * Extracts and builds a var node with parser.
 *
 * Var Nodes have the following structure:
 *
 * VarNode :=      OPEN_VARIABLE_NODE var_exp CLOSE_VARIABLE_NODE 
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
 * \param   error   Optional error var to be filled in case of failure.
 *
 * \return  A new Var node instance.
 */
MangoNode *mango_varnode_extract_with_parser(MangoParserContext *ctx, MangoError **error)
{
    MangoVar *var = mango_var_extract_with_parser(ctx, error);
    if (var == NULL)
        return NULL;

    // read the next token - it should be a close or a filter starter
    MangoParser *parser = ctx->parser;
    const MangoToken *token = mango_parser_peek_token(parser, error);
    if (token == NULL)
        return NULL;

    MangoList *filter_nodes = (MangoList *)mango_linkedlist_new();
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
        OBJ_DECREF(var);
        if (filter_nodes != NULL)
        {
            OBJ_DECREF(filter_nodes);
        }
    }
    else
    {
        if (COLLECTION_IS_EMPTY(filter_nodes) == 0)
        {
            OBJ_DECREF(filter_nodes);
            filter_nodes = NULL;
        }
        node = (MangoNode *)mango_varnode_new(var, filter_nodes);
    }
    return node;
}

/**
 * Adds a new filter node.
 *
 * \param   mnode   Mango (var) node to add to.
 * \param   fnode   The filter node to add.
 */
void mango_varnode_add_filter(MangoVarNode *mnode, MangoFilterNode *fnode)
{
    if (mnode->filterNodes == NULL)
    {
        mnode->filterNodes = mango_rawlist_new();
    }
    mango_rawlist_push_back(mnode->filterNodes, fnode);
}

/**
 * Called when a varnode is to be dealloced.
 */
void mango_varnode_dealloc(MangoVarNode *varnode)
{
    if (varnode->var != NULL)
        OBJ_DECREF(varnode->var);
    if (varnode->filterNodes != NULL)
    {
        mango_rawlist_clear(varnode->filterNodes, (DeleteFunc)mango_filternode_free);
        mango_rawlist_free(varnode->filterNodes);
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
    return mango_vars_are_equal(mvn1->var, mvn2->var) &&
            mango_rawlists_are_equal(mvn1->filterNodes, mvn2->filterNodes, (EqualsFunc)mango_filternodes_are_equal);
}


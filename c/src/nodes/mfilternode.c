
#include "mangopub.h"

DECLARE_PROTO_FUNC("MangoFilterNode", MangoPrototype, mango_filternode_prototype,
    __proto__.deallocFunc   = (ObjectDeallocFunc)mango_filternode_dealloc;
    __proto__.equalsFunc    = (ObjectEqualsFunc)mango_filternodes_are_equal;
);

/**
 * Creates a new filter node given a filter.
 */
MangoFilterNode *mango_filternode_new(MangoFilter *f)
{
    return mango_filternode_init(f, ZNEW(MangoFilterNode), mango_filternode_prototype());
}

MangoFilterNode *mango_filternode_init(MangoFilter *filter, MangoFilterNode *node, MangoPrototype *proto)
{
    if (proto == NULL)
        proto = mango_filternode_prototype();
    OBJ_INIT(node, proto);
    node->filter = filter;
    node->arguments = NULL;
    return node;
}

/**
 * Frees a filter node.
 */
void mango_filternode_dealloc(MangoFilterNode *fnode)
{
    // do not delete filter as they are shared
    if (fnode->arguments != NULL)
        OBJ_DECREF(fnode->arguments);
    mango_object_dealloc((MangoObject *)fnode);
}

/**
 * Tells if two filter nodes are equal.
 */
BOOL mango_filternodes_are_equal(const MangoFilterNode *fn1, const MangoFilterNode *fn2)
{
    if (fn1 == fn2)
    {
        return true;
    }
    else if (fn1 == NULL || fn2 == NULL)
    {
        return false;
    }
    else if (fn1->filter != fn2->filter)    // filter instances are shared
    {
        return false;
    }
    // compare the arguments
    return OBJ_EQUALS(fn1->arguments, fn2->arguments);
}

/**
 * Applies a filter arguments to a filter and returns the value.
 */
MangoObject *mango_filternode_apply(MangoFilterNode *fnode, const MangoObject *input, MangoTemplateContext *context)
{
    return mango_filter_apply(fnode->filter, input, context, fnode->arguments);
}

/**
 * Adds an argument to a filter node.
 *
 * \param   fnode   Filter node to add the var to.
 * \param   mvar    Argument to add.
 */
void mango_filternode_add_arg(MangoFilterNode *fnode, MangoVar *mvar)
{
    if (fnode->arguments == NULL)
        fnode->arguments = (MangoList *)mango_linkedlist_new();
    LIST_PUSH_BACK(fnode->arguments, mvar);
}

/**
 * Reads a list of filter expressions with the parser and returns a list.
 * Also the final '}}' is discarded.
 *
 * \param   ctx     Parser context containing necessary items.
 * \param   filters     List storing all the parsed filters.
 * \param   error       Error value to be set in case of failure.
 *
 * \return true if filters were read successfully, false on error.  On
 * error, the error var might be set if it is provided.  On error, the
 * output list will still contain extracted filters upto the point of error
 * and it is the caller's responsibility to destroy the read filters.
 */
BOOL mango_filternode_extract_filter_list(MangoParserContext *ctx,
                                          MangoList *filters,
                                          MangoError **error)
{
    MangoParser *parser = ctx->parser;
    const MangoToken *token = mango_parser_peek_token(parser, error);
    if (token == NULL)
        return false;

    while (token->tokenType == TOKEN_FILTER_SEPERATOR)
    {
        mango_parser_get_token(parser, error);  // discard the "|"
        MangoFilterNode *filternode = mango_filternode_extract_with_parser(ctx, error);
        if (filternode == NULL)
            return false;
        LIST_PUSH_BACK(filters, filternode);
        token = mango_parser_peek_token(parser, error);
        if (token == NULL)
            return false;
    }
    return true;
}

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
MangoFilterNode *mango_filternode_extract_with_parser(MangoParserContext *ctx, MangoError **error)
{
    MangoParser *parser = ctx->parser;
    MangoStringFactory *msf = ctx->strfactory;
    MangoTable *filterlib = ctx->filterlib;
    const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER,
                                                        false, error);

    MangoString *filtername = mango_stringfactory_from_buffer(msf, token->tokenValue);
    MangoFilter *filter = mango_filter_library_get(filtername, filterlib);
    OBJ_DECREF(filtername);
    if (filter == NULL)
    {
        mango_error_set(error, -1, "Filter not found: %s", token->tokenValue->buffer);
        return NULL;
    }

    MangoFilterNode *filternode = mango_filternode_new(filter);

    token = mango_parser_peek_token(parser, error);

    if (token != NULL && token->tokenType == TOKEN_COLON)
    {
        // consume the token
        token = mango_parser_get_token(parser, error);
        mango_filternode_parse_filter_args(ctx, filternode, error);
    }
    return filternode;
}

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
BOOL mango_filternode_parse_filter_args(MangoParserContext *ctx,
                                        MangoFilterNode *filternode,
                                        MangoError **error)
{
    // now read the tokens
    MangoParser *parser = ctx->parser;
    MangoStringFactory *msf = ctx->strfactory;
    const MangoToken *token = mango_parser_expect_token_in_list(
                                parser, IDENT_STRING_OR_OPEN_PAREN, false, error);
    if (token == NULL)
        return false;

    if (token->tokenType == TOKEN_OPEN_PAREN)
    {
        token = mango_parser_expect_token_in_list(parser, IDENT_OR_STRING, false, error);
        while (true)
        {
            MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
            MangoVar *var = mango_var_new(
                                        varValue, token->tokenType == TOKEN_QUOTED_STRING, NULL);
            mango_filternode_add_arg(filternode, var);
            token = mango_parser_expect_token_in_list(parser, COMA_OR_CLOSE_PAREN, false, error);
            if (token == NULL)
            {
                return false;
            }
            else if (token->tokenType == TOKEN_CLOSE_PAREN)
            {
                break ;
            }
            else if (token->tokenType == TOKEN_COMA)
            {
                token = mango_parser_expect_token_in_list(parser, IDENT_OR_STRING, false, error);
                if (token == NULL)
                    return false;
            }
        }
    }
    else if (token->tokenType == TOKEN_IDENTIFIER || 
            token->tokenType == TOKEN_QUOTED_STRING)
    {
        MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
        BOOL isquoted = token->tokenType == TOKEN_QUOTED_STRING;
        MangoVar *var = mango_var_new(varValue, isquoted, NULL);
        mango_filternode_add_arg(filternode, var);
    }
    else
    {
        return false;
    }
    return true;
}


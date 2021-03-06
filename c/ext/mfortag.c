
#include "mangopub.h"
#include "mfortag.h"

static const char *EMPTY_OR_ENDFOR[3]   = { "empty", "endfor", NULL };
static const char *ENDFOR[2]            = { "endfor", NULL };

MangoForTagContext *mango_fortag_create_context(MangoForTagNode *       ftNode,
                                                MangoTemplateContext *  tmplCtx,
                                                MangoNodeContext *      topCtx);
MangoNode *mango_fortag_render_bit_more(MangoForTagNode *       fortag,
                                        MangoOutStream *        outstream,
                                        MangoTemplateContext *  context,
                                        MangoNodeContext *      currContext,
                                        MangoError **           error);
MangoNode *mango_fortag_child_exited(MangoForTagNode *      fortag,
                                     MangoNode *            childNode,
                                     MangoTemplateContext * context,
                                     MangoNodeContext *     currContext,
                                     MangoError **          error);
MangoNode *mango_fortag_node_entered(MangoForTagNode *      fortag,
                                     MangoTemplateContext * context,
                                     MangoForTagContext *   ftnContext,
                                     MangoNode *            fromNode,
                                     MangoError **          error);
void mango_fortagctx_dealloc(MangoForTagContext *fortagctx);

/**
 * Sets the source var for the for-tag render context.
 * \param   ftc     For tag context to be udpated.
 * \param   source  Source var to set.
 */
extern void mango_fortagctx_set_source(MangoForTagContext *ftc, MangoObject *source);

////    For Loop related variables
MangoVar *mango_forloopvar_set_next(MangoForLoopVar *var, MangoString *value, BOOL isquoted);
MangoObject *mango_forloopvar_resolve(MangoForLoopVar *var, MangoTemplateContext *context, MangoNodeContext *currContext);

/**
 * Get the prototype for the fortag.
 */
DECLARE_PROTO_FUNC(mango_fortag_prototype, MangoNodePrototype, mango_node_prototype(),
    ((MangoPrototype *)&__proto__)->deallocFunc     = (ObjectDeallocFunc)mango_fortag_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc      = (ObjectEqualsFunc)mango_fortags_are_equal;
    __proto__.createContextFunc                     = (NodeCreateContextFunc)mango_fortag_create_context;
    __proto__.renderBitMoreFunc                     = (NodeRenderBitMoreFunc)mango_fortag_render_bit_more;
    __proto__.childExitedFunc                       = (NodeChildExitedFunc)mango_fortag_child_exited;
);

/**
 * Prototype for the for tag parser.
 */
DECLARE_PROTO_FUNC(mango_fortagparser_prototype, MangoTagParserPrototype, mango_default_prototype(),
    __proto__.parserFunc = (TagParserFunc)mango_fortag_extract_with_parser;
);

/**
 * Prototype for tag for the for tag context.
 */
DECLARE_PROTO_FUNC(mango_fortagctx_prototype, MangoPrototype, NULL, 
    __proto__.deallocFunc = (ObjectDeallocFunc)mango_fortagctx_dealloc;
);

/**
 * Prototype for the forloop variable.
 */
DECLARE_PROTO_FUNC(mango_forloopvar_prototype, MangoVarPrototype, mango_var_prototype(), 
    __proto__.setNextVarFunc    = (VarSetNextFunc)mango_forloopvar_set_next;
    __proto__.resolveFunc       = (VarResolveFunc)mango_forloopvar_resolve;
);

/**
 * Creates a new fortag node.
 * \param   source      Source var to be used.
 * \param   childNode   Nodes to be used on each iteration.
 * \param   emptyNode   Nodes to be used if body of the loop was never hit.
 *
 * \return  A new MangoNode instance.
 */
MangoForTagNode *mango_fortag_new(MangoVar * source,
                                  MangoNode * childNode,
                                  MangoNode * emptyNode)
{
    MangoForTagNode *node   = NEW(MangoForTagNode);
    return mango_fortag_init(node, source, childNode, emptyNode, NULL);
}

/**
 * Initialises a fortag object.
 * \param   mftnode     Fortag node to be initialised.
 * \param   source      Source var to be used.
 * \param   childNode   Nodes to be used on each iteration.
 * \param   emptyNode   Nodes to be used if body of the loop was never hit.
 * \param   proto       Fortag prototype or its children to be used as
 *                      base.
 *
 * \return  The node passed into be intialised.
 */
MangoForTagNode *mango_fortag_init(MangoForTagNode *mftnode,
                                   MangoVar * source,
                                   MangoNode * childNode,
                                   MangoNode * emptyNode,
                                   MangoNodePrototype *proto)
{
    if (proto == NULL)
        proto = mango_fortag_prototype();
    mango_tagnode_init((MangoTagNode *)mftnode, proto);
    mftnode->items          = NULL;
    mftnode->sourceVar      = source;
    mftnode->childNodes     = childNode;
    mftnode->emptyNodes     = emptyNode;
    return mftnode;
}

/**
 * Deallocs the for tag data when ref count reaches 0.
 * \param ftn   The for-tag node to be dealloced.
 */
void mango_fortag_dealloc(MangoForTagNode *ftn)
{
    OBJ_DECREF(ftn->childNodes);
    OBJ_DECREF(ftn->emptyNodes);
    OBJ_DECREF(ftn->sourceVar);

    if (ftn->items != NULL)
    {
        COLLECTION_CLEAR(ftn->items);
        OBJ_DECREF(ftn->items);
    }
}

/**
 * Compares the data of for-tag nodes to see if they are equal.
 * \param   ftd1    First for-tag data in comparison.
 * \param   ftd2    Second for-tag data in comparison.
 * \return true if the two objects are recursively equal, false otherwise.
 */
BOOL mango_fortags_are_equal(const MangoForTagNode *ftd1, const MangoForTagNode *ftd2)
{
    if (ftd1 == ftd2)
    {
        return true;
    }
    else if (ftd1 == NULL || ftd2 == NULL)
    {
        return false;
    }
    else
    {
        if (mango_vars_are_equal(ftd1->sourceVar, ftd2->sourceVar))
        {
            return OBJ_EQUALS(ftd1->items, ftd2->items) &&
                    OBJ_EQUALS(ftd1->childNodes, ftd2->childNodes) &&
                    OBJ_EQUALS(ftd1->emptyNodes, ftd2->emptyNodes);
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////
//          Parser related methods
////////////////////////////////////////////////////////////////////////////////////

/**
 * Returns the default fortag parser.
 */
MangoTagParser *mango_fortagparser_default()
{
    static MangoTagParser tagparser;
    static BOOL initialised = false;
    if (!initialised)
    {
        OBJ_INIT(&tagparser, mango_fortagparser_prototype());
        initialised = true;
    }
    return &tagparser;
}


/**
 * Extracts a for-tag from the token stream usign the parser.
 *
 * \param   tagparser   The tag parser.
 * \param   ctx         Parser context containing necessary items for parsing.
 * \param   error       Error var to set in case of failure.
 *
 * \return Parsed for-tag node data.
 */
MangoForTagNode *mango_fortag_extract_with_parser(MangoTagParser *tagparser, MangoParser *parser, MangoContext *ctx, MangoError **error)
{
    MangoForTagNode *ftn    = mango_fortag_new(NULL, NULL, NULL);
    mango_fortag_parse_item_list(ftn, parser, ctx, error);

    // parse the source var and discared the '%}' token
    ftn->sourceVar = mango_var_extract_with_parser(parser, ctx, error);
    mango_parser_expect_token(parser, TOKEN_CLOSE_TAG, false, error);

    // parse child nodes till the endfor tag.
    ftn->childNodes = mango_parser_parse_till(parser, ctx, EMPTY_OR_ENDFOR, error);

    if (error == NULL || *error == NULL)
    {
        // see if this is the end of it or if there is an "empty" bit
        const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);

        // see what the node name was if it was "empty" then read again
        if (token != NULL)
        {
            BOOL isEmptyTag = strcmp("empty", token->tokenValue->buffer) == 0;
            mango_parser_discard_till_token(parser, TOKEN_CLOSE_TAG, error);
            if (isEmptyTag)
            {
                // read till end-tag var
                ftn->emptyNodes = mango_parser_parse_till(parser, ctx, ENDFOR, error);
                token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
                mango_parser_discard_till_token(parser, TOKEN_CLOSE_TAG, error);
            }
            return ftn;
        }
    }
    OBJ_DECREF(ftn);
    return NULL;
}

/**
 * Parse the list of items before the "in".
 * \param   ftd     For-tag data whose items list is to be populated.
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Error to be set incase of failure.
 *
 * \returns true if successful, false otherwise.
 */
BOOL mango_fortag_parse_item_list(MangoForTagNode * ftd,
                                  MangoParser *     parser,
                                  MangoContext *    ctx,
                                  MangoError **     error)
{
    // now read the tokens
    MangoStringFactory *msf = ctx->string_factory;
    const MangoToken *token = mango_parser_expect_token_in_list(parser, IDENT_OR_OPEN_PAREN, false, error);
    if (token->tokenType == TOKEN_OPEN_PAREN)
    {
        token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
        while (true)
        {
            MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
            MangoVar *nextVar = mango_var_new(varValue, token->tokenType == TOKEN_QUOTED_STRING, NULL);
            mango_fortag_add_item(ftd, nextVar);
            token = mango_parser_expect_token_in_list(parser, COMA_OR_CLOSE_PAREN, false, error);
            if (token->tokenType == TOKEN_CLOSE_PAREN)
                break ;
            else if (token->tokenType == TOKEN_COMA)
                token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
        }
    }
    else if (token->tokenType == TOKEN_IDENTIFIER) 
    {
        MangoString *varValue = mango_stringfactory_from_buffer(msf, token->tokenValue);
        MangoVar *nextVar = mango_var_new(varValue, token->tokenType == TOKEN_QUOTED_STRING, NULL);
        mango_fortag_add_item(ftd, nextVar);
    }
    else
    {
        assert("Internal Error.  This case should have been caught by expectTokensInList" && false);
        return false;
    }
    
    // now read and discard the "in" token - we treat this just as an identifier
    token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
    if (strcasecmp(token->tokenValue->buffer, "in") != 0)
    {
        mango_error_set(error, -1, "Expected 'in', but found: %s", token->tokenValue);
        return false;
    }
    return true;
}

/**
 * Adds a new var to the list of "items" in the for-tag node.
 * \param   ftd     For tag to which an item is to be added.
 * \param   var     Var to be added.
 */
void mango_fortag_add_item(MangoForTagNode *ftd, MangoVar *var)
{
    if (ftd->items == NULL)
        ftd->items = (MangoList *)mango_linkedlist_new();
    LIST_PUSH_BACK(ftd->items, var);
}

/**
 * Create the for tag node rendering context when required.
 */
MangoForTagContext *mango_fortag_create_context(MangoForTagNode *       ftNode,
                                                    MangoTemplateContext *  tmplCtx,
                                                    MangoNodeContext *      topCtx)
{
    MangoForTagContext *ftnContext = NULL;
    if (ftNode->sourceVar != NULL && ftNode->items != NULL)
    {
        ftnContext = mango_fortagctx_new((MangoNode *)ftNode, topCtx);
        mango_fortagctx_set_source(ftnContext, mango_var_resolve(ftNode->sourceVar, tmplCtx, topCtx));
        
        // push NULL values on the context stack for the vars referred by the items
        MangoIterator *iter = OBJ_ITERATOR(ftNode->items);
        while (mango_iterator_has_next(iter))
        {
            MangoVar *nextvar = (MangoVar *)mango_iterator_next(iter);
            mango_tmplctx_push(tmplCtx, nextvar->value, NULL);
        }
        OBJ_DECREF(iter);
    }
    return ftnContext;
}

/**
 * Renders a bit more content from this node.
 */
MangoNode *mango_fortag_render_bit_more(MangoForTagNode *       fortag,
                                        MangoOutStream *        outstream,
                                        MangoTemplateContext *  context,
                                        MangoNodeContext *      currContext,
                                        MangoError **           error)
{
    if (OBJ_IMPLEMENTS(currContext, mango_fortagctx_prototype()))
    {
        MangoForTagContext *ftnContext = (MangoForTagContext *)currContext;
    
        // see if the context can unpack the number of values 
        // as we have in the items array.
        return mango_fortag_node_entered(fortag, context, ftnContext, NULL, error);
    }
    return NULL;
}

/**
 * Called when a child node (that was returned in renderBitMore) was exited having completed.
 * By doing this we are giving the parent node a chance to tell the renderer what the next 
 * node will be.
 * \param   fortag  Fortag being currently rendered.
 * \param   childNode   Child node being exited during the rendering process.
 * \param   context     Value store
 * \param   currContext Top of the context stack.
 * \param   error       Error to be set on failure.
 * \return NULL if this node is ALSO to be exited, otherwise a new child node to be pushed 
 * onto the renderer stack.
 */
MangoNode *mango_fortag_child_exited(MangoForTagNode *      fortag,
                                     MangoNode *            childNode,
                                     MangoTemplateContext * context,
                                     MangoNodeContext *     currContext,
                                     MangoError **          error) 
{
    if (OBJ_IMPLEMENTS(currContext, mango_fortagctx_prototype()))
        return mango_fortag_node_entered(fortag, context, (MangoForTagContext *)currContext, childNode, error);
    return NULL;
}

/**
 * "Enters" the node either from a parent node or a child node.
 * 
 * \param   fortag      Tag being entered.
 * \param   context     Value store
 * \param   ftnContex   Render context for the for tag.
 * \param   fromNode    Where we are entering (NULL is an exit from a child).
 * \param   error       Error to be set incase of failure.
 * \return  The next node to enter for rendering, NULL, if we need to exit
 * this node as well (ie the node has been completely rendered).
 */
MangoNode *mango_fortag_node_entered(MangoForTagNode *      fortag,
                                     MangoTemplateContext * context,
                                     MangoForTagContext *   ftnContext,
                                     MangoNode *            fromNode,
                                     MangoError **          error)
{
    if (ftnContext->isEmpty)
    {
        if (fromNode == NULL)
            return fortag->emptyNodes;
    }
    else
    {
        // update the values of all values in the items
        int numVars = mango_fortagctx_unpack_values(ftnContext, COLLECTION_SIZE(fortag->items));
        if (numVars > 0)
        {
            // push all the values onto the context stack
            for (int i = 0;i < numVars;i++)
            {
                MangoObject *itemValue  = (MangoObject *)OBJ_GETINTATTR(ftnContext->itemValues, i);
                MangoVar *var           = (MangoVar *)OBJ_GETINTATTR(fortag->items, i);
                mango_tmplctx_set(context, var->value, itemValue);
            }
            return fortag->childNodes;
        }

        // we are exiting the node so pop the values out of the context
        MangoIterator *iter = OBJ_ITERATOR(fortag->items);
        for (;mango_iterator_has_next(iter);)
        {
            MangoVar *var = (MangoVar *)mango_iterator_next(iter);
            mango_tmplctx_pop(context, var->value);
        }
        OBJ_DECREF(iter);
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//              ForTag Render Context related methods
///////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Deallocs the for tag node context when ref count reaches 0.
 */
void mango_fortagctx_dealloc(MangoForTagContext *fortagctx)
{
    OBJ_DECREF(fortagctx->valIterator);   // delete the old iterator
    mango_object_dealloc(OBJ(fortagctx));
}

/**
 * Creates a new node context object.
 * \param   node    Node data for the for tag node.
 * \param   parent  The parent node context.
 *
 * \return  A new instance of the node context data.
 */
MangoForTagContext *mango_fortagctx_new(MangoNode *node, MangoNodeContext *parent)
{
    MangoForTagContext *ftc = ZNEW(MangoForTagContext);
    mango_nodecontext_init((MangoNodeContext *)ftc,
                           (MangoPrototype *)mango_fortagctx_prototype(),
                           node, parent);
    ftc->isFirst        = false;
    ftc->isLast         = false;
    ftc->currIndex      = 0;
    ftc->isEmpty        = true;
    ftc->itemValues     = NULL;
    ftc->valIterator    = NULL;
    ftc->itemValues     = NULL;
    mango_fortagctx_set_source(ftc, NULL);
    return ftc;
}

/**
 * Sets the source var for the for-tag render context.
 * \param   ftc     For tag context to be udpated.
 * \param   source  Source var to set.
 */
void mango_fortagctx_set_source(MangoForTagContext *ftc, MangoObject *source)
{
    ftc->isEmpty        = true;
    ftc->isFirst        = true;
    ftc->isLast         = false;
    ftc->currIndex      = 0;

    OBJ_DECREF(ftc->valIterator);   // delete the old iterator
    ftc->valIterator    = OBJ_ITERATOR(source);
    ftc->isEmpty        = !mango_iterator_has_next(ftc->valIterator);
}
    
///////////////////////////////////////////////////////////////////////////////////
//                      ForLoop Variable specific methods
///////////////////////////////////////////////////////////////////////////////////

/**
 * Creates a new forloop variable.
 */
MangoForLoopVar *mango_forloopvar_new()
{
    MangoForLoopVar *flv = ZNEW(MangoForLoopVar);
    mango_var_init((MangoVar *)flv, mango_forloopvar_prototype(), NULL, false, NULL);
    flv->parentCount = 0;
    return flv;
}

/**
 * Sets the value of the next variable.  If the value is "parentloop" then
 * simply stores the parent count so that we can look up the nth context
 * from now.
 */
MangoVar *mango_forloopvar_set_next(MangoForLoopVar *var, MangoString *value, BOOL isquoted)
{
    if (mango_string_compare_to_buffer(value, "parentloop", -1) == 0)
    {
        var->parentCount++;
        return NULL;
    }

    // call super class method
    return mango_var_set_next((MangoVar *)var, value, isquoted);
}

/**
 * Resolves the value of the forloop variable by traversing parent
 * contexts.
 */
MangoObject *mango_forloopvar_resolve(MangoForLoopVar *var, MangoTemplateContext *context, MangoNodeContext *currContext)
{
    // find the first ForLoop anywhere along the node context stack!!
    MangoNodeContext *tempContext = currContext;
    int parentsLeft = var->parentCount;
    while (parentsLeft >= 0)
    {
        while (tempContext != NULL && OBJ_IMPLEMENTS(tempContext, mango_fortagctx_prototype()))
            tempContext = tempContext->parent;

        if (tempContext != NULL)
        {
            parentsLeft--;
            if (parentsLeft >= 0)
                tempContext = tempContext->parent;
        }
    }

    MangoVar *nextVar = ((MangoVar *)var)->next;
    if (tempContext != NULL && nextVar != NULL)
    {
        MangoForTagContext *ftnContext = (MangoForTagContext *)tempContext;
        if (mango_string_compare_to_buffer(nextVar->value, "counter", -1) == 0)
        {
            return OBJ(mango_number_from_int(ftnContext->currIndex + 1));
        }
        else if (mango_string_compare_to_buffer(nextVar->value, "counter0", -1) == 0)
        {
            return OBJ(mango_number_from_int(ftnContext->currIndex));
        }
        else if (mango_string_compare_to_buffer(nextVar->value, "first", -1) == 0)
        {
            return OBJ(mango_number_from_int(ftnContext->isFirst));
        }
        else if (mango_string_compare_to_buffer(nextVar->value, "last", -1) == 0)
        {
            return OBJ(mango_number_from_int(ftnContext->isLast));
        }
        return OBJ(mango_number_from_int(0));
    }
    return NULL;
}

#if 0
    /**
     * Called when an instance of this tagnode is registered.
     * @param tagLib
     * @param instance
     */
    public static void onClassRegistered()
    {
        // now register the special var class as well...
        // so the next time a forloop gets called it will do its magic
        // on the parent items.
        VarLibrary.getSharedInstance().registerObjectClass("forloop", ForLoopVar.class);
    }

#endif

/**
 * Unpacks numvals values from the next value in the iterator and
 * returns the number of values unpacked.
 * \param   ftc     Fortag context to be rendered.
 * \param   numvals Number of values to be unpacked.
 * \return number of values "really" unpacked.
 */
int mango_fortagctx_unpack_values(MangoForTagContext *ftc, int numvals)
{
    if (ftc->valIterator == NULL || !mango_iterator_has_next(ftc->valIterator))
    {
        // reached the end of the line so return 0;
        return 0;
    }

    if (ftc->itemValues == NULL)
    {
        ftc->isFirst = true;
        ftc->currIndex = 0;
        ftc->itemValues = (MangoList *)mango_arraylist_new();
    }
    else
    {
        ftc->isFirst = false;
        ftc->currIndex++;
    }

    int count = COLLECTION_SIZE(ftc->itemValues);
    for (int i = 0;i < count;i++)
        LIST_SET_AT(ftc->itemValues, i, NULL);

    for (int i = count; i < numvals;i++)
        LIST_PUSH_BACK(ftc->itemValues, NULL);
    
    int outCount = mango_valueiterator_unpack(ftc->valIterator, numvals, ftc->itemValues);

    if (!mango_iterator_has_next(ftc->valIterator))
        ftc->isLast = true;

    // clear the item values and reset them to NULL
    return outCount;
}


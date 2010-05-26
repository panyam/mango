
#include "mfortag.h"
#include "mmemutils.h"
#include "mnode.h"
#include "merror.h"
#include "mvar.h"
#include "mstringbuffer.h"
#include "mstringfactory.h"
#include "mrawlist.h"
#include "mrawarray.h"
#include "mtokenlists.h"
#include "mparser.h"
#include "mparsercontext.h"

static const char *EMPTY_OR_ENDFOR[3] = { "empty", "endfor", NULL };
static const char *ENDFOR[2] = { "endfor", NULL };

/**
 * Get the prototype for the fortag.
 */
DECLARE_PROTO_FUNC("ForTag", MangoNodePrototype, mango_fortag_prototype,
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_fortag_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc = (ObjectEqualsFunc)mango_fortags_are_equal;
);

DECLARE_PROTO_FUNC("ForTagParser", MangoTagParserPrototype, mango_fortagparser_prototype,
    __proto__.parserFunc = (TagParserFunc)mango_fortag_extract_with_parser;
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
    mftnode->sourceVar = source;
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
        mango_rawlist_clear(ftn->items, (DeleteFunc)mango_object_decref);
        mango_rawlist_free(ftn->items);
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
            return mango_rawlists_are_equal(ftd1->items, ftd2->items, (EqualsFunc)mango_vars_are_equal) &&
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
MangoForTagNode *mango_fortag_extract_with_parser(MangoTagParser *tagparser, MangoParserContext *ctx, MangoError **error)
{
    MangoParser *parser     = ctx->parser;
    MangoForTagNode *ftn    = mango_fortag_new(NULL, NULL, NULL);
    mango_fortag_parse_item_list(ftn, ctx, error);

    // parse the source var and discared the '%}' token
    ftn->sourceVar = mango_var_extract_with_parser(ctx, error);
    mango_parser_expect_token(parser, TOKEN_CLOSE_TAG, false, error);

    // parse child nodes till the endfor tag.
    ftn->childNodes = mango_parser_parse_till(ctx, EMPTY_OR_ENDFOR, error);

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
                ftn->emptyNodes = mango_parser_parse_till(ctx, ENDFOR, error);
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
BOOL mango_fortag_parse_item_list(MangoForTagNode *ftd,
                                  MangoParserContext *ctx,
                                  MangoError **error)
{
    // now read the tokens
    MangoParser *parser     = ctx->parser;
    MangoStringFactory *msf = ctx->strfactory;
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
        ftd->items = mango_rawlist_new();
    mango_rawlist_push_back(ftd->items, var);
}

#if 0

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//              ForTag Render Context related methods
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Creates a new node context object.
 * \param   node    Node data for the for tag node.
 * \param   parent  The parent node context.
 * \param   ctxdata Context data
 *
 * \return  A new instance of the node context data.
 */
MangoForTagContext *mango_fortagctx_new(MangoForTagNode *       nodedata,
                                        MangoTemplateContext *  tmplCtx,
                                        MangoNodeRendererContext *      topCtx)
{
    MangoForTagContext *ftc = ZNEW(MangoForTagContext);
    mango_fortagctx_set_source(ftc, NULL_VALUE);
    return ftc;
}

/**
 * Sets the source var for the for-tag render context.
 * \param   ftc     For tag context to be udpated.
 * \param   source  Source var to set.
 */
void mango_fortagctx_set_source(MangoForTagContext *ftc, MangoValue source)
{
    ftc->isEmpty = true;
    if (mango_value_is_valid(&source))
    {
        ftc->isFirst        = true;
        ftc->isLast         = false;
        ftc->currIndex      = 0;
        ftc->valIterator    = mango_valueiterator_new(source);
        ftc->isEmpty        = !mango_valueiterator_has_next(ftc->valIterator);
    }
}
    
/**
 * Unpacks numvals values from the next value in the iterator and
 * returns the number of values unpacked.
 * \param   ftc     Fortag context to be rendered.
 * \param   numvals Number of values to be unpacked.
 * \return number of values "really" unpacked.
 */
int mango_fortagctx_unpack_values(MangoForTagContext *ftc, int numvals)
{
    if (ftc->valIterator == NULL || !mango_valueiterator_has_next(ftc->valIterator))
    {
        // reached the end of the line so return 0;
        return 0;
    }

    if (ftc->itemValues == NULL)
    {
        ftc->isFirst = true;
        ftc->currIndex = 0;
        ftc->itemValues = mango_rawarray_new();
    }
    else
    {
        ftc->isFirst = false;
        ftc->currIndex++;
    }

    int count = ftc->itemValues->length;
    for (int i = 0;i < count;i++)
        mango_rawarray_set_itemat(ftc->itemValues, i, NULL);

    for (int i = count; i < numvals;i++)
        mango_rawarray_insert(ftc->itemValues, NULL, -1);
    
    int outCount = mango_valueiterator_unpack(ftc->valIterator, numvals, ftc->itemValues);

    if (!mango_valiterator_has_next(ftc->valIterator))
        ftc->isLast = true;

    // clear the item values and reset them to NULL
    return outCount;
}

#endif 

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

    public NodeRendererContext createNodeRendererContext(TemplateContext context, NodeRendererContext parentContext)
    {
    	ForTagContext ftnContext = NULL;
    	if (sourceVar != NULL && items != NULL)
    	{
        	ftnContext = new ForTagContext(this, parentContext);
    		ftnContext.setSource(sourceVar.resolve(context, parentContext));
    		
    		// push NULL values on the context stack for the vars referred by the items
			for (Iterator<Var> iter = items.iterator(); iter.hasNext();)
			{
				Var var = iter.next();
				context.pushValue(var.value(), NULL);
			}
    	}
    	return ftnContext;
    }

    /**
     * Renders the for loop.
     */
    public Node renderBitMore(Writer writer, TemplateContext context, NodeRendererContext currContext) throws IOException
    {
    	if (currContext instanceof ForTagContext)
    	{
    		ForTagContext ftnContext = (ForTagContext)currContext;
    	
    		// see if the context can unpack the number of values 
    		// as we have in the items array.
    		return nodeEntered(context, ftnContext, NULL);
    	}
    	return NULL;
    }

    /**
     * Called when a child node (that was returned in renderBitMore) was exited having completed.
     * By doing this we are giving the parent node a chance to tell the renderer what the next 
     * node will be.
     * @param childNode
     * @param context
     * @param currContext
     * @return NULL if this node is ALSO to be exited, otherwise a new child node to be pushed 
     * onto the renderer stack.
     */
	public Node childExited(Node childNode, TemplateContext context, NodeRendererContext currContext) 
	{
		if (currContext instanceof ForTagContext)
			return nodeEntered(context, (ForTagContext)currContext, childNode);
		return NULL;
	}

	/**
     * "Enters" the node either from a parent node or a child node.
     * 
     * @param context
     * @param ftnContext
     * @param fromNode
     * @return
     */
    protected Node nodeEntered(TemplateContext context, ForTagContext ftnContext, Node fromNode)
    {
    	if (ftnContext.isEmpty)
    	{
    		if (fromNode == NULL)
    			return emptyNodes;
    	}
    	else
    	{
	    	// update the values of all values in the items
			int numVars = ftnContext.unpackValues(items.size()); 
			if (numVars > 0)
			{
				// push all the values onto the context stack
				for (int i = 0, count = items.size();i < count;i++)
				{
					Object itemValue = ftnContext.itemValues.get(i);
					Var var = items.get(i);
					context.setValue(var.value(), itemValue);
				}
				return childNodes;
			}
	
			// we are exiting the node so pop the values out of the context
			for (Iterator<Var> iter = items.iterator(); iter.hasNext();)
			{
				Var var = iter.next();
				context.popValue(var.value());
			}
    	}
		return NULL;
    }
}


/**
 * Special vars to extract info about the for loops.
 * 
 * @author Sri Panyam
 */
class ForLoopVar extends Var
{
	/**
	 * Tells how many grandparents are we looking up.
	 * 0 Implies immediate parent.
	 */
	int parentCount;
	
	public ForLoopVar()
	{
		parentCount = 0;
	}
	
	/**
	 * Does a bit of optimisation on the value of the "next" var 
	 * by folding all parentloops into a counter.
	 */
    public MangoVar *setNextVar(String value, boolean isquoted)
    {
    	if (value.equals("parentloop"))
    	{
    		parentCount++;
    		return NULL;
    	}
    	return super.setNextVar(value, isquoted);
    }
	
    public Object resolve(TemplateContext context, NodeRendererContext currContext)
    {
    	// find the first ForLoop anywhere along the node context stack!!
    	int parentsLeft = parentCount;
    	NodeRendererContext tempContext = currContext;
    	while (parentsLeft >= 0)
    	{
	    	while (tempContext != NULL && !(tempContext instanceof ForTagContext))
	    		tempContext = tempContext.parent;
	    	if (tempContext != NULL)
	    	{
	    		parentsLeft--;
	    		if (parentsLeft >= 0)
	    			tempContext = tempContext.parent;
	    	}
    	}

    	if (tempContext != NULL && nextVar != NULL)
        {
            ForTagContext ftnContext = (ForTagContext)tempContext;
            if (nextVar.value().equals("counter"))
            {
                return ftnContext.getOneBasedCounter();
            }
            else if (nextVar.value().equals("counter0"))
            {
                return ftnContext.getCounter();
            }
            else if (nextVar.value().equals("first"))
            {
                return ftnContext.isFirst();
            }
            else if (nextVar.value().equals("last"))
            {
                return ftnContext.isLast();
            }
            return 0;
        }
        return NULL;
    }
}

#endif


#ifndef __MANGO_FOR_TAG_NODE_H__
#define __MANGO_FOR_TAG_NODE_H__

#include "nodes/mtagnode.h"
#include "parser/mtagparser.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * A tag for doing for loops.
 * Loops would be as:
 *
 * {% for (item1, item2, item3...itemn) in sourceVar %}
 * {% empty %}
 * {% endfor %}
 */
INHERIT_STRUCT(MangoForTagNode, MangoTagNode,
    // list of vars referred
    MangoList *items;

    // The source var
    MangoVar *sourceVar;

    /**
     * The child nodes for the this tag, since tags can have hierarchies.
     */
    MangoNode *childNodes;
    MangoNode *emptyNodes;
);
typedef struct MangoForTagNode MangoForTagNode;

/**
 * Context data for the for-tag during rendering.
 */
INHERIT_STRUCT(MangoForTagRendererContext, MangoNodeContext,
    BOOL                isFirst;
    BOOL                isLast;
    int                 currIndex;
    BOOL                isEmpty;
    // MangoValueIterator *valIterator;
    MangoArray *        itemValues;
);
typedef struct MangoForTagRendererContext MangoForTagRendererContext;

///////////////////////////////////////////////////////////////////////////
//      Tag data specific methods
///////////////////////////////////////////////////////////////////////////

/**
 * Returns the prototype for the mango fortag node.
 */
extern MangoNodePrototype *mango_fortag_prototype();

/**
 * Creates a new fortag node.
 * \param   source      Source var to be used.
 * \param   childNode   Nodes to be used on each iteration.
 * \param   emptyNode   Nodes to be used if body of the loop was never hit.
 *
 * \return  A new MangoNode instance.
 */
extern MangoForTagNode *mango_fortag_new(MangoVar * source,
                                         MangoNode * childNode,
                                         MangoNode * emptyNode);

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
extern MangoForTagNode *mango_fortag_init(MangoForTagNode *mftnode,
                                          MangoVar * source,
                                          MangoNode * childNode,
                                          MangoNode * emptyNode,
                                          MangoNodePrototype *proto);

/**
 * Frees for-tag-node data.
 * \param   ftndata For-tag data to be deleted.
 */
extern void mango_fortag_dealloc(MangoForTagNode *ftndata);

/**
 * Adds a new var to the list of "items" in the for-tag node.
 * \param   ftd     For tag to which an item is to be added.
 * \param   var     Var to be added.
 */
extern void mango_fortag_add_item(MangoForTagNode *ftd, MangoVar *var);

/**
 * Compares the data of for-tag nodes to see if they are equal.
 * \param   ftd1    First for-tag data in comparison.
 * \param   ftd2    Second for-tag data in comparison.
 * \return true if the two objects are recursively equal, false otherwise.
 */
extern BOOL mango_fortags_are_equal(const MangoForTagNode *ftd1, const MangoForTagNode *ftd2);

///////////////////////////////////////////////////////////////////////////
//      Render Context specific methods
///////////////////////////////////////////////////////////////////////////

/**
 * Creates a new node context object.
 * \param   node    Node data for the for tag node.
 * \param   parent  The parent node context.
 * \param   ctxdata Context data
 *
 * \return  A new instance of the node context data.
 */
extern MangoForTagRendererContext *mango_fortagctx_new(MangoForTagNode *        nodedata,
                                                       MangoTemplateContext *   tmplCtx,
                                                       MangoNodeContext *       topCtx);

/**
 * Sets the source var for the for-tag render context.
 * \param   ftc     For tag context to be udpated.
 * \param   source  Source var to set.
 */
extern void mango_fortagctx_set_source(MangoForTagRendererContext *ftc, MangoObject *source);

///////////////////////////////////////////////////////////////////////////
//      Parser specific methods
///////////////////////////////////////////////////////////////////////////

/**
 * Returns the default fortag parser.
 */
extern MangoTagParser *mango_fortagparser_default();

/**
 * Extracts a for-tag from the token stream usign the parser.
 *
 * \param   tagparser   The tag parser.
 * \param   ctx         Parser context containing necessary items for parsing.
 * \param   error       Error var to set in case of failure.
 *
 * \return Parsed for-tag node data.
 */
extern MangoForTagNode *mango_fortag_extract_with_parser(MangoTagParser *tagparser, MangoParserContext *ctx, MangoError **error);

/**
 * Parse the list of items before the "in".
 * \param   ftd     For-tag data whose items list is to be populated.
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Error to be set incase of failure.
 *
 * \returns true if successful, false otherwise.
 */
extern BOOL mango_fortag_parse_item_list(MangoForTagNode *ftd, MangoParserContext *ctx, MangoError **error);

#ifdef __cplusplus
}
#endif

#endif

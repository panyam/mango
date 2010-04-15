
#ifndef __MANGO_FOR_TAG_NODE_H__
#define __MANGO_FOR_TAG_NODE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A tag for doing for loops.
 * Loops would be as:
 *
 * {% for (item1, item2, item3...itemn) in sourceVariable %}
 * {% empty %}
 * {% endfor %}
 */
typedef struct MangoForTagData
{
    // list of variables referred
    MangoList *items;

    // The source variable
    MangoVariable *sourceVariable;

    /**
     * The child nodes for the this tag, since tags can have hierarchies.
     */
    MangoNode *childNodes;
    MangoNode *emptyNodes;
} MangoForTagData;

/**
 * Context data for the for-tag during rendering.
 */
typedef struct MangoForTagContext
{
    BOOL                isFirst;
    BOOL                isLast;
    int                 currIndex;
    BOOL                isEmpty;
    // VariableIterator    iterator;
    MangoList *         itemValues;
} MangoForTagContext;

///////////////////////////////////////////////////////////////////////////
//      Tag data specific methods
///////////////////////////////////////////////////////////////////////////

/**
 * Frees for-tag-node data.
 * \param   ftndata For-tag data to be deleted.
 */
extern void mango_fortag_free(MangoForTagData *ftndata);

/**
 * Adds a new variable to the list of "items" in the for-tag node.
 * \param   ftd     For tag to which an item is to be added.
 * \param   var     Variable to be added.
 */
extern void mango_fortag_add_item(MangoForTagData *ftd, MangoVariable *var);

/**
 * Compares the data of for-tag nodes to see if they are equal.
 * \param   ftd1    First for-tag data in comparison.
 * \param   ftd2    Second for-tag data in comparison.
 * \return true if the two objects are recursively equal, false otherwise.
 */
extern BOOL mango_fortags_are_equal(const MangoForTagData *ftd1, const MangoForTagData *ftd2);

/**
 * Parse the list of items before the "in".
 * \param   ftd     For-tag data whose items list is to be populated.
 * \param   parser  Parser reading the tokens.
 * \param   error   Error to be set incase of failure.
 *
 * \returns true if successful, false otherwise.
 */
extern BOOL mango_fortag_parse_item_list(MangoForTagData *ftd, MangoParser *parser, MangoError **error);

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
extern MangoForTagContext *mango_fortagcontext_new(MangoForTagData *       nodedata,
                                                   MangoTemplateContext *  tmplCtx,
                                                   MangoNodeContext *      topCtx);

#ifdef __cplusplus
}
#endif

#endif

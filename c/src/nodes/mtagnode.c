
#include "mangopub.h"

/**
 * Initialises a tag node.
 */
MangoTagNode *mango_tagnode_init(MangoTagNode *tagnode, MangoNodePrototype *proto)
{
    mango_node_init((MangoNode *)tagnode, proto);
    return tagnode;
}

/**
 * Extracts a tag node using a given parser.
 *
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Error output in case of failure.
 *
 * \return  NULL if failure otherwise a MangoNode.
 */
MangoTagNode *mango_tagnode_extract_with_parser(MangoParser *parser, MangoContext *ctx, MangoError **error)
{
    const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
    if (token == NULL)
        return NULL;

    MangoString *tagname = mango_stringfactory_from_buffer(ctx->string_factory, token->tokenValue);
    MangoTagParser *tagparser = (MangoTagParser *)OBJ_GETSTRATTR(ctx->tag_library, tagname);
    if (tagparser == NULL)
    {
        mango_error_set(error, -1, "Invalid tag type: %s", token->tokenValue);
        OBJ_DECREF(tagname);
        return NULL;
    }

    return tagparser->__prototype__->parserFunc(tagparser, parser, ctx, error);
}


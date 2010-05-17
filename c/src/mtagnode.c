
#include "mnode.h"
#include "merror.h"
#include "mparser.h"
#include "mparsercontext.h"
#include "mtemplateloader.h"
#include "mtagnode.h"
#include "mtagparser.h"
#include "mtagparserlibrary.h"
#include "mstringbuffer.h"
#include "mstringfactory.h"

/**
 * Extracts a tag node using a given parser.
 *
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Error output in case of failure.
 *
 * \return  NULL if failure otherwise a MangoNode.
 */
MangoNode *mango_tagnode_extract_with_parser(MangoParserContext *ctx, MangoError **error)
{
    MangoParser *parser = ctx->parser;
    const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
    if (token == NULL)
        return NULL;

    MangoString *tagname = mango_stringfactory_from_buffer(ctx->strfactory, token->tokenValue);
    MangoTagParser *tagparser = (MangoTagParser *)mango_tagparser_library_get(tagname, ctx->taglib);
    if (tagparser == NULL)
    {
        mango_error_set(error, -1, "Invalid tag type: %s", token->tokenValue);
        OBJ_DECREF(tagname);
        return NULL;
    }

    return tagparser->parserFunc(tagparser, ctx, error);
}

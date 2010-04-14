
#include "mnode.h"
#include "merror.h"
#include "mparser.h"
#include "mtemplateloader.h"
#include "mtagnode.h"
#include "mtagparser.h"
#include "mtagparserlibrary.h"
#include "mstringbuffer.h"

/**
 * Extracts a tag node using a given parser.
 *
 * \param   parser  Parser doing the parsing.
 * \param   loader  Template loader that contains other loaded templates.
 * \param   error   Error output in case of failure.
 *
 * \return  NULL if failure otherwise a MangoNode.
 */
MangoNode *mango_tagnode_extract_with_parser(MangoParser *parser,
                                             MangoTemplateLoader *loader,
                                             MangoError **error,
                                             MangoLibrary *tagParserLib)
{
    const MangoToken *token = mango_parser_expect_token(parser, TOKEN_IDENTIFIER, false, error);
    if (token == NULL)
        return NULL;

    MangoString *tagname = mango_stringbuffer_tostring(token->tokenValue);
    MangoTagParser *tagparser = (MangoTagParser *)mango_tagparser_library_get(tagname, tagParserLib);
    if (tagparser == NULL)
    {
        mango_error_set(error, -1, "Invalid tag type: %s", token->tokenValue);
        mango_string_free(tagname);
        return NULL;
    }

    return tagparser->parserFunc(tagparser, parser, loader, error);
}

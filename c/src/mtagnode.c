
#include "mnode.h"
#include "merror.h"
#include "mparser.h"
#include "mtemplateloader.h"
#include "mtagnode.h"

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
                                             MangoError **error)
{
    return NULL;
}

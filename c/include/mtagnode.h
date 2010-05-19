
#ifndef __MANGO_TAGNODE_H__
#define __MANGO_TAGNODE_H__

#include "mnode.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Superclass for all tag nodes.
 */
DECLARE_CLASS(MangoTagNode, MangoNode);

/**
 * Extracts a tag node using a given parser.
 *
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Error output in case of failure.
 *
 * \return  NULL if failure otherwise a MangoNode.
 */
extern MangoTagNode *mango_tagnode_extract_with_parser(MangoParserContext *ctx, MangoError **error);

#ifdef __cplusplus
}
#endif

#endif


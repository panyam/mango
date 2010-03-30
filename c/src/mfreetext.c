
#include "mnode.h"
#include "mstring.h"
#include "mfreetext.h"

/**
 * Creates a new mango node list.
 */
MangoNode *mango_freetext_new(MangoString *value)
{
    MangoNode *node = mango_node_new(value);
    node->deleteNodeData    = (DeleteNodeDataCallback)mango_string_free;
    return node;
}


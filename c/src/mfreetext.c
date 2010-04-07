
#include "mnode.h"
#include "mstring.h"
#include "mfreetext.h"

/**
 * Creates a new mango node list.
 */
MangoNode *mango_freetext_new(MangoString *value)
{
    MangoNode *node         = mango_node_new(value);
    node->nodeClass         = mango_class_for_name("FreeText", true);
    node->deleteNodeData    = (DeleteNodeDataCallback)mango_string_free;
    node->nodeDataEquals    = mango_strings_are_equal;
    return node;
}


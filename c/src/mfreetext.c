
#include "mnode.h"
#include "mstring.h"
#include "mfreetext.h"

BOOL mango_strings_equal(const void *a, const void *b)
{
    const MangoString *str1 = (const MangoString *)a;
    const MangoString *str2 = (const MangoString *)b;
    return mango_string_compare(str1, str2->buffer, str2->length) == 0;
}

/**
 * Creates a new mango node list.
 */
MangoNode *mango_freetext_new(MangoString *value)
{
    MangoNode *node         = mango_node_new(value);
    node->nodeClass         = mango_class_for_name("FreeText", true);
    node->deleteNodeData    = (DeleteNodeDataCallback)mango_string_free;
    node->nodeDataEquals    = mango_strings_equal;
    return node;
}


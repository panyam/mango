
#include "mnode.h"
#include "mstring.h"
#include "mfreetext.h"
#include "mclasses.h"

/**
 * Creates a new mango node list.
 */
MangoNode *mango_freetext_new(MangoString *value)
{
    MangoNode *node         = mango_node_new(value);
    node->nodeClass         = mango_class_for_name("FreeText", true);
    node->deleteNodeFunc    = (DeleteFunc)mango_string_free;
    node->nodeEqualsFunc    = (EqualsFunc)mango_strings_are_equal;
    return node;
}


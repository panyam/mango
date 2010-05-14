
#include "mnode.h"
#include "mstring.h"
#include "mfreetext.h"
#include "mclasses.h"

/**
 * Creates a new mango node list.
 */
MangoFreeTextNode *mango_freetext_init(MangoFreeTextNode *mftNode, MangoString *value);
{
    mango_node_init(mftNode, NULL);
    mftNode->value = OBJ_INCREF(value);
    return mftNode;
}



#include "mstring.h"
#include "mfreetext.h"
#include "mclasses.h"

/**
 * The prototype for mango node lists.
 */
MangoNodePrototype *mango_freetext_prototype()
{
    DECLARE_PROTO_VARIABLE("FreeText", MangoNodePrototype, freetextPrototype,
        freetextPrototype.nodeCountFunc     = NULL;
        freetextPrototype.getChildNodeFunc  = NULL;
        ((MangoPrototype *)&freetextPrototype)->deallocFunc = mango_freetext_dealloc;
    );
}

/**
 * Creates a freetext node.
 */
MangoFreeTextNode *mango_freetext_new(MangoString *value)
{
    MangoFreeTextNode *mftNode = NEW(MangoFreeTextNode);
    return mango_freetext_init(mftNode, value);
}

/**
 * Creates a new mango node list.
 */
MangoFreeTextNode *mango_freetext_init(MangoFreeTextNode *mftNode, MangoString *value)
{
    mango_node_init((MangoNode *)mftNode, NULL);
    mftNode->value = OBJ_INCREF(value);
    return mftNode;
}

/**
 * Frees a freetext node.
 */
void mango_freetext_dealloc(MangoFreeTextNode *mftnode)
{
    mango_object_release(mftnode->value);

    // call super class dealloc
    mango_node_dealloc((MangoNode *)mftnode);
}


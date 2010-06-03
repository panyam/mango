
#include "mangopub.h"

/**
 * The prototype for mango node lists.
 */
DECLARE_PROTO_FUNC(mango_freetext_prototype, MangoNodePrototype, MangoFreeTextNodePrototype, 
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_freetext_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc  = (ObjectEqualsFunc)mango_freetext_are_equal;
    ((MangoPrototype *)&__proto__)->compareFunc = (ObjectCompareFunc)mango_freetext_compare;
);

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
    mango_node_init((MangoNode *)mftNode, mango_freetext_prototype());
    mftNode->value = OBJ_INCREF(value);
    return mftNode;
}

/**
 * Frees a freetext node.
 */
void mango_freetext_dealloc(MangoFreeTextNode *mftnode)
{
    OBJ_DECREF(mftnode->value);

    // call super class dealloc
    mango_node_dealloc((MangoNode *)mftnode);
}

/**
 * Tells if two free text nodes are equal.
 */
BOOL mango_freetext_are_equal(const MangoFreeTextNode *mftn1, const MangoFreeTextNode *mftn2)
{
    return mango_objects_are_equal((const MangoObject *)mftn1->value, (const MangoObject *)mftn2->value);
}

/**
 * Compares two free text nodes.
 */
int mango_freetext_compare(const MangoFreeTextNode *mftn1, const MangoFreeTextNode *mftn2)
{
    return mango_object_compare((const MangoObject *)mftn1->value, (const MangoObject *)mftn2->value);
}


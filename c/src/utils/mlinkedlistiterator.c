
#include "mangopub.h"

void mango_linkedlistiterator_dealloc(MangoLinkedListIterator *iter);
BOOL mango_linkedlistiterator_has_next(MangoLinkedListIterator *iter);
MangoObject *mango_linkedlistiterator_next(MangoLinkedListIterator *iter);

/**
 * Array list iterator prototype.
 */
DECLARE_PROTO_FUNC(mango_linkedlistiterator_prototype, MangoIteratorPrototype, mango_iterator_prototype(),
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_linkedlistiterator_dealloc;
    __proto__.hasNextFunc = (IteratorHasNextFunc)mango_linkedlistiterator_has_next;
    __proto__.nextFunc = (IteratorNextFunc)mango_linkedlistiterator_next;
);

/**
 * Get an linked list iterator for an linkedlist.
 */
MangoLinkedListIterator *mango_linkedlistiterator_new(MangoLinkedList *llist)
{
    MangoLinkedListIterator *iter = OBJ_ALLOC(MangoLinkedListIterator, mango_linkedlistiterator_prototype());
    iter->linkedlist = OBJ_INCREF(llist);
    iter->currnode = llist != NULL ? llist->head : NULL;
    return iter;
}

/**
 * Dealloc the iterator.
 */
void mango_linkedlistiterator_dealloc(MangoLinkedListIterator *iter)
{
    OBJ_DECREF(iter->linkedlist);
    mango_object_dealloc(OBJ(iter));
}

/**
 * Are there any more items left in the iterator?
 */
BOOL mango_linkedlistiterator_has_next(MangoLinkedListIterator *iter)
{
    return iter->currnode != NULL;
}

/**
 * Get the next item pointed by the iterator.
 */
MangoObject *mango_linkedlistiterator_next(MangoLinkedListIterator *iter)
{
    if (iter->currnode == NULL)
        return NULL;

    MangoObject *out = iter->currnode->data;
    iter->currnode = iter->currnode->next;
    return out;
}


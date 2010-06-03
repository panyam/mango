
#include "mangopub.h"

void mango_arraylistiterator_dealloc(MangoArrayListIterator *iter);
BOOL mango_arraylistiterator_has_next(MangoArrayListIterator *iter);
MangoObject *mango_arraylistiterator_next(MangoArrayListIterator *iter);

/**
 * Array list iterator prototype.
 */
DECLARE_PROTO_FUNC(mango_arraylistiterator_prototype, MangoIteratorPrototype, mango_iterator_prototype(),
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_arraylistiterator_dealloc;
    __proto__.hasNextFunc = (IteratorHasNextFunc)mango_arraylistiterator_has_next;
    __proto__.nextFunc = (IteratorNextFunc)mango_arraylistiterator_next;
);

/**
 * Get an array list iterator for an arraylist.
 */
MangoArrayListIterator *mango_arraylistiterator_new(MangoArrayList *array)
{
    MangoArrayListIterator *iter = OBJ_ALLOC(MangoArrayListIterator, mango_arraylistiterator_prototype());
    iter->arraylist = OBJ_INCREF(array);
    iter->currIndex = 0;
    return iter;
}

/**
 * Dealloc the iterator.
 */
void mango_arraylistiterator_dealloc(MangoArrayListIterator *iter)
{
    OBJ_DECREF(iter->arraylist);
    mango_object_dealloc(OBJ(iter));
}

/**
 * Are there any more items left in the iterator?
 */
BOOL mango_arraylistiterator_has_next(MangoArrayListIterator *iter)
{
    return iter->currIndex < iter->arraylist->length;
}

/**
 * Get the next item pointed by the iterator.
 */
MangoObject *mango_arraylistiterator_next(MangoArrayListIterator *iter)
{
    if (iter->currIndex >= iter->arraylist->length)
        return NULL;
    return iter->arraylist->items[iter->currIndex++];
}


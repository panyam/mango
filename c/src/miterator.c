
#include "miterator.h"

/**
 * Deallocs an iterator
 * \param   miter   Iterator to be dealloced.
 */
void mango_iterator_dealloc(MangoIterator *miter)
{
    mango_object_dealloc((MangoObject *)(miter));
}

/**
 * Tells if there are more items in the iterator.
 * \param   miter   Iterator to peek from.
 * \return  true if more items are to follow, false otherwise.
 */
BOOL mango_iterator_hase_next(MangoIterator *miter)
{
    if (miter != NULL && miter->__prototype__->hasNextFunc != NULL)
        miter->__prototype__->hasNextFunc(miter);
    return false;
}

/**
 * Gets the next item pointed by the iterator.
 * \param   miter   Iterator to get the next item from.
 */
MangoObject *mango_iterator_next(MangoIterator *miter)
{
    if (miter != NULL && miter->__prototype__->nextFunc != NULL)
        miter->__prototype__->nextFunc(miter);
    return NULL;
}


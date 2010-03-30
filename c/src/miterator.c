
#include "miterator.h"

/**
 * Frees an iterator
 * \param   miter   Iterator to be freed.
 */
void mango_iterator_free(MangoIterator *miter)
{
    if (miter->data != NULL && miter->deleteFunc != NULL)
    {
        miter->deleteFunc(miter->data);
    }
    free(miter);
}

/**
 * Gets the next item pointed by the iterator.
 * \param   miter   Iterator to get the next item from.
 */
void *mango_iterator_next(MangoIterator *miter)
{
    if (miter->data == NULL || miter->hasNext == NULL || miter->next == NULL)
        return NULL;
    return miter->next(miter->data);
}


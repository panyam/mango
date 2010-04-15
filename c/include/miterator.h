
#ifndef __MANGO_ITERATOR_H__
#define __MANGO_ITERATOR_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoIterator
{
    void *  data;
    void    (*deleteFunc)(void *data);
    BOOL    (*hasNext)(void *data);
    void *  (*next)(void *data);
};

/**
 * Frees an iterator
 * \param   miter   Iterator to be freed.
 */
extern void mango_iterator_free(MangoIterator *miter);

/**
 * Tells if there are more items in the iterator.
 * \param   miter   Iterator to peek from.
 * \return  true if more items are to follow, false otherwise.
 */
extern BOOL mango_iterator_hase_next(MangoIterator *miter);

/**
 * Gets the next item pointed by the iterator.
 * \param   miter   Iterator to get the next item from.
 */
extern void *mango_iterator_next(MangoIterator *miter);

#ifdef __cplusplus
}
#endif

#endif


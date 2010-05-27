
#ifndef __MANGO_ITERATOR_H__
#define __MANGO_ITERATOR_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prototypes of iterators.
 */
INHERIT_STRUCT(MangoIteratorPrototype, MangoPrototype,
    BOOL            (*hasNextFunc)(MangoIterator *iterator);
    MangoObject *   (*nextFunc)(MangoIterator *iterator);
);

DECLARE_CLASS(MangoIterator, MangoIteratorPrototype);

/**
 * Initialises a new iterator object.
 */
extern MangoObject *mango_iterator_init(MangoIterator *iter, MangoIteratorPrototype *proto);

/**
 * Deallocs an iterator.
 * \param   miter   Iterator to be dealloced.
 */
extern void mango_iterator_dealloc(MangoIterator *miter);

/**
 * Tells if there are more items in the iterator.
 * \param   miter   Iterator to peek from.
 * \return  true if more items are to follow, false otherwise.
 */
extern BOOL mango_iterator_has_next(MangoIterator *miter);

/**
 * Gets the next item pointed by the iterator.
 * \param   miter   Iterator to get the next item from.
 */
extern MangoObject *mango_iterator_next(MangoIterator *miter);

#ifdef __cplusplus
}
#endif

#endif


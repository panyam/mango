
#ifndef __MANGO_ARRAYLIST_ITERATOR_H__
#define __MANGO_ARRAYLIST_ITERATOR_H__

#include "core/miterator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prototypes of iterators.
 */
DECLARE_CLASS(MangoArrayListIterator, MangoIteratorPrototype, 
    MangoArrayList *arraylist;
    int             currIndex;
);

/**
 * Array list iterator prototype.
 */
MangoIteratorPrototype *mango_arraylistiterator_prototype();

/**
 * Get an array list iterator for an arraylist.
 */
MangoArrayListIterator *mango_arraylistiterator_new(MangoArrayList *list);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_LINKEDLIST_ITERATOR_H__
#define __MANGO_LINKEDLIST_ITERATOR_H__

#include "core/miterator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prototypes of iterators.
 */
DECLARE_CLASS(MangoLinkedListIterator, MangoIteratorPrototype, 
    MangoLinkedList *linkedlist;
    MangoLinkedListNode *currnode;
);

/**
 * Array list iterator prototype.
 */
MangoIteratorPrototype *mango_linkedlistiterator_prototype();

/**
 * Get an array list iterator for an linkedlist.
 */
MangoLinkedListIterator *mango_linkedlistiterator_new(MangoLinkedList *list);

#ifdef __cplusplus
}
#endif

#endif


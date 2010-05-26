
#ifndef __MANGO_LINKEDLIST_H__
#define __MANGO_LINKEDLIST_H__

#include "mlist.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoLinkedListNode
{
    MangoObject *           data;
    MangoLinkedListNode *   next;
    MangoLinkedListNode *   prev;
};

/**
 * A mango linked list object.
 */
DECLARE_CLASS(MangoLinkedList, MangoListPrototype,
    MangoLinkedListNode *   head;
    MangoLinkedListNode *   tail;
    size_t                  size;
);

/**
 * Creates a new mango list.
 *
 * \returns A new MangoLinkedList instance.
 */
extern MangoLinkedList *mango_linkedlist_new();

/**
 * Initialises a linked list.
 */
extern MangoLinkedList *mango_linkedlist_init(MangoLinkedList *list, MangoListPrototype *proto);

#ifdef __cplusplus
}
#endif

#endif


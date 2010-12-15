#include "mangopub.h"

void mango_linkedlist_dealloc(MangoLinkedList *mlist);
BOOL mango_linkedlist_is_empty(MangoLinkedList *mlist);
size_t mango_linkedlist_size(const MangoLinkedList *mlist);
extern void mango_linkedlist_clear(MangoLinkedList *mlist);
MangoObject *mango_linkedlist_item_at(MangoLinkedList *mlist, int index);
MangoLinkedListNode *mango_linkedlist_insert_at(MangoLinkedList *mlist, MangoObject *obj, int index);
void mango_linkedlist_remove_at(MangoLinkedList *mlist, int index);
BOOL mango_linkedlists_are_equal(const MangoLinkedList *list1, const MangoLinkedList *list2);
void mango_linkedlist_set_at(MangoLinkedList *mlist, int index, MangoObject *obj);

/**
 * The default array prototype.
 */
DECLARE_PROTO_FUNC(mango_linkedlist_prototype, MangoListPrototype, mango_list_prototype(), 
    ((MangoPrototype *)&__proto__)->deallocFunc             = (ObjectDeallocFunc)mango_linkedlist_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc              = (ObjectEqualsFunc)mango_linkedlists_are_equal;
    ((MangoPrototype *)&__proto__)->getIntAttrFunc          = (ObjectGetIntAttrFunc)mango_linkedlist_item_at;
    ((MangoCollectionPrototype *)&__proto__)->clearFunc     = (CollectionClearFunc)mango_linkedlist_clear;
    ((MangoCollectionPrototype *)&__proto__)->isEmptyFunc   = (CollectionIsEmptyFunc)mango_linkedlist_is_empty;
    ((MangoCollectionPrototype *)&__proto__)->sizeFunc      = (CollectionSizeFunc)mango_linkedlist_size;
    __proto__.insertAtFunc                                  = (ListInsertAtFunc)mango_linkedlist_insert_at;
    __proto__.removeAtFunc                                  = (ListRemoveAtFunc)mango_linkedlist_remove_at;
    __proto__.setAtFunc                                     = (ListSetAtFunc)mango_linkedlist_set_at;
);

/**
 * Creates a linked list.
 *
 * \returns A new MangoLinkedList instance.
 */
MangoLinkedList *mango_linkedlist_new()
{
    return mango_linkedlist_init(NEW(MangoLinkedList), mango_linkedlist_prototype());
}

/**
 * Initialises a linked list.
 */
MangoLinkedList *mango_linkedlist_init(MangoLinkedList *list, MangoListPrototype *proto)
{
    if (proto == NULL)
        proto = mango_linkedlist_prototype();
    mango_list_init((MangoList *)list, proto);
    list->head  = NULL;
    list->tail  = NULL;
    list->size  = 0;
    return list;
}

/**
 * Deallocs a mango list.
 * \param   mlist    The mango list to be dealloced
 */
void mango_linkedlist_dealloc(MangoLinkedList *mlist)
{
    mango_linkedlist_clear(mlist);
    mango_object_dealloc((MangoObject *)mlist);
}

/**
 * Clears the list and optionally deletes entries within the list with a
 * given deletor method.
 *
 * \param   mlist   List to be freed and cleared.
 * \param   deletor Method that will delete each entry.
 */
void mango_linkedlist_clear(MangoLinkedList *mlist)
{
    for (MangoLinkedListNode *temp = mlist->head;temp != NULL;)
    {
        MangoLinkedListNode *next = temp->next;
        OBJ_DECREF(temp->data);
        free(temp);
        temp = next;
    }
    mlist->head = mlist->tail = NULL;
    mlist->size = 0;
}

/**
 * Gets the number of items in the list.
 *
 * \returns A the list size.
 */
size_t mango_linkedlist_size(const MangoLinkedList *mlist)
{
    return mlist->size;
}

/**
 * Finds the linked list node at a given index.
 */
MangoLinkedListNode *mango_linkedlist_node_at(MangoLinkedList *mlist, int index)
{
    MangoLinkedListNode *temp = mlist->head;
    if (index == 0)
    {
        temp = mlist->head;
    }
    else if (index < 0)
    {
        temp = NULL;
    }
    else if (index < mlist->size)
    {
        if (index < mlist->size / 2)
        {
            temp = mlist->head;
            for (int i = 0;i < index && temp != NULL;i++, temp = temp->next);
        }
        else
        {
            temp = mlist->tail;
            for (int i = mlist->size - 1;i > index && temp != NULL;i++, temp = temp->prev);
        }
    }
    return temp;
}

/**
 * Gets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \return The data at the given index.
 */
MangoObject *mango_linkedlist_item_at(MangoLinkedList *mlist, int index)
{
    MangoLinkedListNode *node = mango_linkedlist_node_at(mlist, index);
    return node == NULL ? NULL : node->data;
}

/**
 * Sets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \param   obj     Object to be set as.
 */
void mango_linkedlist_set_at(MangoLinkedList *mlist, int index, MangoObject *obj)
{
    MangoLinkedListNode *node = mango_linkedlist_node_at(mlist, index);
    if (node != NULL && node->data != obj)
    {
        OBJ_DECREF(node->data);
        node->data = OBJ_INCREF(obj);
    }
}

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
MangoLinkedListNode *mango_linkedlist_insert_at(MangoLinkedList *mlist, MangoObject *data, int index)
{
    MangoLinkedListNode *newnode = ZNEW(MangoLinkedListNode);
    newnode->data = OBJ_INCREF(data);

    mlist->size++;
    if (mlist->head == NULL)
    {
        mlist->head = mlist->tail = newnode;
    }
    else
    {
        MangoLinkedListNode *beforeNode = mango_linkedlist_node_at(mlist, index);
        if (beforeNode == NULL)
        {
            mlist->tail->next = newnode;
            newnode->prev = mlist->tail;
            mlist->tail = newnode;
        }
        else
        {
            MangoLinkedListNode *prev = beforeNode->prev;
            MangoLinkedListNode *next = beforeNode;

            newnode->prev = prev;
            newnode->next = next;

            if (prev != NULL) prev->next = newnode;
            else mlist->head = newnode;

            if (next != NULL) next->prev = newnode;
            else mlist->tail = newnode;
        }
    }
    return newnode;
}

/**
 * Removes a node from the list.
 */
void mango_linkedlist_remove_at(MangoLinkedList *mlist, int index)
{
    MangoLinkedListNode *node = mango_linkedlist_node_at(mlist, index);
    if (mlist->size > 0)
    {
        MangoLinkedListNode *prev = node->prev;
        MangoLinkedListNode *next = node->next;
        mlist->size--;
        if (prev != NULL) prev->next = next;
        else mlist->head = next;

        if (next != NULL) next->prev = prev;
        else mlist->tail = prev;

        // erase the node
        OBJ_DECREF(node->data);
        free(node);
    }
}

/**
 * Tells if a list is empty or not.
 */
BOOL mango_linkedlist_is_empty(MangoLinkedList *mlist)
{
    return mlist->head == NULL;
}

/**
 * Tells if two lists are equal using a comparator function.
 */
BOOL mango_linkedlists_are_equal(const MangoLinkedList *list1, const MangoLinkedList *list2)
{
    if (list1 == list2)
    {
        return true;
    }

    int size1 = list1 == NULL ? 0 : list1->size;
    int size2 = list2 == NULL ? 0 : list2->size;
    if (size1 != size2)
    {
        return false;
    }
    else if (list1 == NULL || list2 == NULL)
    {
        return false;
    }

    for (MangoLinkedListNode *n1 = list1->head, *n2=list2->head;n1 != NULL;n1=n1->next,n2=n2->next)
    {
        if (!OBJ_EQUALS(n1->data, n2->data))
        {
            return false;
        }
    }
    return true;
}


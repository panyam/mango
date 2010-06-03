#include "mangopub.h"

DECLARE_PROTO_FUNC(mango_rawlist_prototype, MangoPrototype, NULL);

/**
 * Creates a linked list node.
 *
 * \returns A new MangoRawListNode instance.
 */
MangoRawListNode *mango_rawlist_node_new(void *data)
{
    MangoRawListNode *newnode = (MangoRawListNode *)calloc(1, sizeof(MangoRawListNode));
    newnode->data = data;
    return newnode;
}

/**
 * Creates a linked list.
 *
 * \returns A new MangoRawList instance.
 */
MangoRawList *mango_rawlist_new()
{
    return mango_rawlist_init(ZNEW(MangoRawList), mango_rawlist_prototype());
}

/**
 * Initialises a raw list.
 */
MangoRawList *mango_rawlist_init(MangoRawList *list, MangoPrototype *proto)
{
    if (proto == NULL)
        proto = mango_rawlist_prototype();
    OBJ_INIT(list, proto);
    list->head  = NULL;
    list->tail  = NULL;
    list->size  = 0;
    return list;
}

/**
 * Frees a mango list.
 * \param   mlist    The mango list to be freed
 * \param   deletor Method that will delete each entry.
 */
void mango_rawlist_free(MangoRawList *mlist, void (*deletor)(void *))
{
    if (mlist != NULL)
    {
        mango_rawlist_clear(mlist, deletor);
        free(mlist);
    }
}

/**
 * Clears the list and optionally deletes entries within the list with a
 * given deletor method.
 *
 * \param   mlist   List to be freed and cleared.
 * \param   deletor Method that will delete each entry.
 */
void mango_rawlist_clear(MangoRawList *mlist, void (*deletor)(void *))
{
    for (MangoRawListNode *temp = mlist->head;temp != NULL;)
    {
        MangoRawListNode *next = temp->next;
        if (deletor != NULL && temp->data != NULL)
            deletor(temp->data);
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
size_t mango_rawlist_size(const MangoRawList *mlist)
{
    return mlist->size;
}

/**
 * Gets the node at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the node is to be retrieved.
 * \return The node at the given index.
 */
const MangoRawListNode *mango_rawlist_node_at(const MangoRawList *mlist, int index)
{
    if (index < 0 || index >= mlist->size)
        return NULL;

    const MangoRawListNode *temp = mlist->head;
    for (int i = 0;i < index && temp != NULL;i++, temp = temp->next);
    return temp;
}

/**
 * Gets the item at a given index.
 * \param   mlist   List being searched.
 * \param   index   Index at which the item is to be retrieved.
 * \return The data at the given index.
 */
void *mango_rawlist_item_at(const MangoRawList *mlist, int index)
{
    const MangoRawListNode *node = mango_rawlist_node_at(mlist, index);
    return node == NULL ? NULL : node->data;
}

/**
 * Returns (without removing) the item at the front of the list.
 *
 * \returns The value of the node at the front of the list.
 */
void *mango_rawlist_front(MangoRawList *mlist)
{
    return mlist->head != NULL ? mlist->head->data : NULL;
}

/**
 * Returns (without removing) the item at the back of the list.
 *
 * \returns The value of the node at the back of the list.
 */
void *mango_rawlist_back(MangoRawList *mlist)
{
    return mlist->tail != NULL ? mlist->tail->data : NULL;
}

/**
 * Adds a new object at the end of the list.
 *
 * \returns The node at which the object was added.
 */
MangoRawListNode *mango_rawlist_push_back(MangoRawList *mlist, void *data)
{
    return mango_rawlist_insert(mlist, data, NULL);
}

/**
 * Set the value at a given index.
 *
 * \returns The old value that was replaced.
 */
void *mango_rawlist_set_at(MangoRawList *mlist, int index, void *data)
{
    MangoRawListNode *node = mlist->head;
    for (int i = 0;i < index && node != NULL;i++, node=node->next) ;
    void *oldvalue = NULL;
    if (node != NULL)
    {
        oldvalue = node->data;
        node->data = data;
    }
    return oldvalue;
}

/**
 * Adds a new object at the front of the list.
 *
 * \returns The node at which the object was added.
 */
MangoRawListNode *mango_rawlist_push_front(MangoRawList *mlist, void *data)
{
    return mango_rawlist_insert(mlist, data, mlist->head);
}

/**
 * Adds a new object before a given node.
 *
 * \returns The node at which the object was added.
 */
MangoRawListNode *mango_rawlist_insert(MangoRawList *mlist, void *data, MangoRawListNode *beforeNode)
{
    MangoRawListNode *newnode = mango_rawlist_node_new(data);
    mlist->size++;
    if (mlist->head == NULL)
    {
        mlist->head = mlist->tail = newnode;
    }
    else
    {
        if (beforeNode == NULL)
        {
            mlist->tail->next = newnode;
            newnode->prev = mlist->tail;
            mlist->tail = newnode;
        }
        else
        {
            MangoRawListNode *prev = beforeNode->prev;
            MangoRawListNode *next = beforeNode;

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
void *mango_rawlist_remove(MangoRawList *mlist, MangoRawListNode *node)
{
    void *data = node->data;
    if (mlist->size > 0)
    {
        MangoRawListNode *prev = node->prev;
        MangoRawListNode *next = node->next;
        mlist->size--;
        if (prev != NULL) prev->next = next;
        else mlist->head = next;

        if (next != NULL) next->prev = prev;
        else mlist->tail = prev;

        // erase the node
        free(node);
    }
    return data;
}

/**
 * Removes a node from the front of the list.
 */
void *mango_rawlist_remove_front(MangoRawList *mlist)
{
    return mango_rawlist_remove(mlist, mlist->head);
}

/**
 * Removes a node from the back of the list.
 */
void *mango_rawlist_remove_back(MangoRawList *mlist)
{
    return mango_rawlist_remove(mlist, mlist->tail);
}

/**
 * Tells if a list is empty or not.
 */
BOOL mango_rawlist_is_empty(MangoRawList *mlist)
{
    return mlist->head == NULL;
}

/**
 * Tells if two lists are equal using a comparator function.
 */
BOOL mango_rawlists_are_equal(const MangoRawList *list1, const MangoRawList *list2, BOOL (*equalFn)(const void *item1, const void *item2))
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
    if (equalFn != NULL)
    {
        for (MangoRawListNode *n1 = list1->head, *n2=list2->head;n1 != NULL;n1=n1->next,n2=n2->next)
        {
            if (!equalFn(n1->data, n2->data))
            {
                return false;
            }
        }
    }
    return true;
}


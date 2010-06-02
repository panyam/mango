
#include "mangopub.h"

typedef struct MangoTableEntry
{
    MangoString *   name;
    MangoObject *   value;
} MangoTableEntry;

int tableentry_name_cmp(const MangoString *name1, const MangoTableEntry *mle2)
{
    return OBJ_COMPARE(name1, mle2->name);
}

int tableentry_cmp(const MangoTableEntry *mle1, const MangoTableEntry *mle2)
{
    return OBJ_COMPARE(mle1->name, mle2->name);
}

BOOL mango_treetable_contains(MangoTreeTable *table, MangoString *key);
MangoObject *mango_treetable_get(MangoTreeTable *table, MangoString *key);

DECLARE_PROTO_FUNC("MangoTreeTable", MangoTablePrototype, mango_treetable_prototype,
    ((MangoPrototype *)&__proto__)->deallocFunc         = (ObjectDeallocFunc)mango_treetable_dealloc;
    ((MangoPrototype *)&__proto__)->getStrAttrFunc      = (ObjectGetStrAttrFunc)mango_treetable_get;
    ((MangoPrototype *)&__proto__)->hasStrAttrFunc      = (ObjectHasStrAttrFunc)mango_treetable_contains;
    ((MangoCollectionPrototype *)&__proto__)->sizeFunc  = (CollectionSizeFunc)mango_treetable_size;
    __proto__.putFunc          = (TablePutFunc)mango_treetable_put;
    __proto__.eraseFunc        = (TableEraseFunc)mango_treetable_erase;
);

/**
 * Get the size of the table.
 *
 * \param   table   Table whose size is to be returned.
 *
 * \return Number of items in the table.
 */
int mango_treetable_size(MangoTreeTable *table)
{
    return table->entries != NULL ? mango_bintree_size(table->entries) : 0;
}

/**
 * Gets the table entry (with key and value pair) corresponding to a
 * particular key in the table.
 * \param   table   Table to search in.
 * \param   key     Key to search for.
 * \return  The TableEntry for the key in the table.
 */
MangoTableEntry *mango_treetable_entry(MangoTreeTable *table, MangoString *key)
{
    if (table->entries != NULL)
    {
        MangoBinTreeNode *node = mango_bintree_find(table->entries, key, (CompareFunc)tableentry_name_cmp);
        if (node != NULL)
            return ((MangoTableEntry *)node->data);
    }
    return NULL;
}

/**
 * Tells if a value for a particular key is in the table.
 *
 * \param   table   Table from which the value is to be searched.
 * \param   key     Key for which the value is to be searched.
 *
 * \return true if the key exists, false otherwise.
 */
BOOL mango_treetable_contains(MangoTreeTable *table, MangoString *key)
{
    return mango_treetable_entry(table, key) != NULL;
}

/**
 * Gets the value for a particular key is in the table.
 *
 * \param   table   Table from which the value is to be fetched.
 * \param   key     Key for which the value is to be fetched.
 *
 * \return The value of the key.  THe value is not increfed.
 */
MangoObject *mango_treetable_get(MangoTreeTable *table, MangoString *key)
{
    MangoTableEntry *entry = mango_treetable_entry(table, key);
    return entry == NULL ? NULL : entry->value;
}

/**
 * Erases the value for a particular key is in the table.
 *
 * \param   table   Table from which the value is to be erased.
 * \param   key     Key for which the value is to be erased.
 * 
 * \return  The current value of the key (it is not decrefed).
 */
void mango_treetable_erase(MangoTreeTable *table, MangoString *key)
{
    MangoBinTreeNode *parent = NULL;
    MangoBinTreeNode *node = mango_bintree_find_with_parent(table->entries, key, (CompareFunc)tableentry_name_cmp, &parent);
    if (node != NULL)
    {
        MangoTableEntry *entry = (MangoTableEntry *)node->data;
        OBJ_DECREF(entry->name);
        OBJ_DECREF(entry->value);
        mango_bintree_delete(table->entries, node, parent, NULL);
    }
}

/**
 * Puts the value for a particular key is in the table.  If the key already
 * exists, it is replaced and the old value is returned.
 *
 * \param   table   Table into which the value is to be set.
 * \param   key     Key for which the value is to be set.
 * \param   value   Value to be set to.
 */
void mango_treetable_put(MangoTreeTable *table, MangoString *key, MangoObject *value)
{
    if (table->entries == NULL)
        table->entries = mango_bintree_new();

    MangoObject *oldvalue = NULL;
    MangoBinTreeNode *node = mango_bintree_find(table->entries, key, (CompareFunc)tableentry_name_cmp);
    if (node == NULL)
    {
        MangoTableEntry *newentry = NEW(MangoTableEntry);
        newentry->name  = OBJ_INCREF(key);
        newentry->value = OBJ_INCREF(value);
        mango_bintree_insert(table->entries, newentry, (CompareFunc)tableentry_cmp);
    }
    else
    {
        oldvalue = ((MangoTableEntry *)node->data)->value;
        if (oldvalue != value)
        {
            OBJ_DECREF(oldvalue);   // erase old value
            ((MangoTableEntry *)node->data)->value = OBJ_INCREF(value);
        }
    }
}

/**
 * Creates a new table that is implemented as a binary tree.
 */
MangoTreeTable *mango_treetable_new()
{
    return mango_treetable_init(ZNEW(MangoTreeTable), mango_treetable_prototype());
}

/**
 * Frees the tree based table
 */
void mango_treetable_dealloc(MangoTreeTable *table)
{
    if (table->entries != NULL)
    {
        mango_bintree_free(table->entries, (DeleteFunc)mango_object_decref);
    }
    mango_table_dealloc((MangoTable *)table);
}

/**
 * Initialises a mango table based on a binary tree.
 */
MangoTreeTable *mango_treetable_init(MangoTreeTable *ttable, MangoTablePrototype *proto)
{
    if (proto == NULL)
        proto = mango_treetable_prototype();
    OBJ_INIT(ttable, proto);
    ttable->entries = NULL;
    return ttable;
}


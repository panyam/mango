
#include "mbtreetable.h"
#include "mbintree.h"
#include "mmemutils.h"

int mango_treetable_size(MangoTreeTable *table)
{
    return table->entries != NULL ? mango_bintree_size(table->entries) : 0;
}

BOOL mango_treetable_contains(MangoTreeTable *btree, MangoString *key)
{
    return false;
}

MangoObject *mango_treetable_get(MangoTreeTable *btree, MangoString *key)
{
    return NULL;
}

MangoObject *mango_treetable_erase(MangoTreeTable *btree, MangoString *key)
{
    return NULL;
}

MangoObject *mango_treetable_put(MangoTreeTable *btree, MangoString *key, MangoObject *value)
{
    return NULL;
}

/**
 * Creates a new table that is implemented as a binary tree.
 */
MangoTable *mango_btree_table_new()
{
    MangoTreeTable *table       = ZNEW(MangoTreeTable);
    return mango_treetable_init(table, mango_treetable_prototype);
}

/**
 * Frees the tree based table
 */
void mango_treetable_dealloc(MangoTreeTable *table)
{
    if (table->entries != NULL)
    {
        mango_bintree_free(table);
    }
    mango_table_dealloc((MangoTable *)table)
}

/**
 * Initialises a mango table based on a binary tree.
 */
MangoTreeTable *mango_treetable_init(MangoTreeTable *ttable, MangoTablePrototype *proto)
{
    ttable->entries          = ZNEW(MangoBinTree);
    ttable->sizeFunc         = mango_treetable_size;
    ttable->freeTableFunc    = mango_treetable_dealloc;
    ttable->getFunc          = mango_treetable_get;
    ttable->containsFunc     = mango_treetable_contains;
    ttable->putFunc          = mango_treetable_put;
    ttable->eraseFunc        = mango_treetable_erase;
    return table;
}


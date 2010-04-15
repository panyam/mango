
#include "mbtreetable.h"
#include "mbintree.h"
#include "mmemutils.h"

BOOL mango_btreetable_contains(MangoBinTree *btree, void *key)
{
    return false;
}

void *mango_btreetable_get(MangoBinTree *btree, void *key)
{
    return NULL;
}

void *mango_btreetable_erase(MangoBinTree *btree, void *key)
{
    return NULL;
}

void *mango_btreetable_put(MangoBinTree *btree, void *key, void *entry)
{
    return NULL;
}

/**
 * Creates a new table that is implemented as a binary tree.
 */
MangoTable *mango_btree_table_new()
{
    MangoTable *table       = ZNEW(MangoTable);
    table->entries          = ZNEW(MangoBinTree);
    table->sizeFunc         = mango_bintree_size;
    table->freeTableFunc    = mango_bintree_free;
    table->getFunc          = mango_btreetable_get;
    table->containsFunc     = mango_btreetable_contains;
    table->putFunc          = mango_btreetable_put;
    table->eraseFunc        = mango_btreetable_erase;
    return table;
}


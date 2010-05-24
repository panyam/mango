
#ifndef __MANGO_BINTREE_TABLE_H__
#define __MANGO_BINTREE_TABLE_H__

#include "mtable.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoTreeTable, MangoTable,
    MangoBinTree *  entries;
);

/**
 * Creates a new table that is implemented as a binary tree.
 */
MangoTreeTable *mango_btree_table_new();

/**
 * Initialises a tree table.
 */
MangoTreeTable *mango_treetable_init(MangoTreeTable *ttable, MangoTablePrototype *proto);

#ifdef __cplusplus
}
#endif

#endif


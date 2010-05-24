
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
 * Get the size of the table.
 *
 * \param   table   Table whose size is to be returned.
 *
 * \return Number of items in the table.
 */
extern int mango_treetable_size(MangoTreeTable *table);

/**
 * Tells if a value for a particular key is in the table.
 *
 * \param   table   Table from which the value is to be searched.
 * \param   key     Key for which the value is to be searched.
 *
 * \return true if the key exists, false otherwise.
 */
extern BOOL mango_treetable_contains(MangoTreeTable *table, MangoString *key);

/**
 * Gets the value for a particular key is in the table.
 *
 * \param   table   Table from which the value is to be fetched.
 * \param   key     Key for which the value is to be fetched.
 *
 * \return The value of the key.  THe value is not increfed.
 */
extern MangoObject *mango_treetable_get(MangoTreeTable *table, MangoString *key);

/**
 * Erases the value for a particular key is in the table.
 *
 * \param   table   Table from which the value is to be erased.
 * \param   key     Key for which the value is to be erased.
 * 
 * \return  The current value of the key (it is not decrefed).
 */
extern MangoObject *mango_treetable_erase(MangoTreeTable *table, MangoString *key);

/**
 * Puts the value for a particular key is in the table.  If the key already
 * exists, it is replaced and the old value is returned.
 *
 * \param   table   Table into which the value is to be set.
 * \param   key     Key for which the value is to be set.
 * \param   value   Value to be set to.
 * 
 * \return  NULL if the key does not already exist, otherwise the old
 * value.  Also the value is increfed.
 */
extern MangoObject *mango_treetable_put(MangoTreeTable *table, MangoString *key, MangoObject *value);

/**
 * Creates a new table that is implemented as a binary tree.
 */
extern MangoTreeTable *mango_treetable_new();

/**
 * Frees the tree based table
 */
extern void mango_treetable_dealloc(MangoTreeTable *table);

/**
 * Initialises a mango table based on a binary tree.
 */
extern MangoTreeTable *mango_treetable_init(MangoTreeTable *ttable, MangoTablePrototype *proto);

#ifdef __cplusplus
}
#endif

#endif


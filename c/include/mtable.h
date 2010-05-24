
#ifndef __MANGO_TABLE_H__
#define __MANGO_TABLE_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*TableSizeFunc)(MangoTable *table);
typedef MangoObject *(*TableGetFunc)(MangoTable *table, MangoString *key);
typedef BOOL (*TableContainsFunc)(MangoTable *table, MangoString *key);
typedef MangoObject *(*TablePutFunc)(MangoTable *table, MangoString *key, MangoObject *value);
typedef MangoObject *(*TableEraseFunc)(MangoTable *table, MangoString *key);

/**
 * General associate container for a set of MangoObjects.
 */
INHERIT_STRUCT(MangoTablePrototype, MangoPrototype,
    /**
     * Returns the number of entries.
     */
    int (*sizeFunc)(MangoTable *table);

    /**
     * Gets a value by key.
     */
    MangoObject *(*getFunc)(MangoTable *table, MangoString *key);

    /**
     * Tells if a value exists.
     */
    BOOL (*containsFunc)(MangoTable *table, MangoString *key);

    /**
     * Puts a value by key, replacing and returning the old value if any.
     */
    MangoObject *(*putFunc)(MangoTable *table, MangoString *key, MangoObject *value);

    /**
     * Erases an element from the table.
     */
    MangoObject *(*eraseFunc)(MangoTable *table, MangoString *key);
);

/**
 * Super class of all associative containers.
 */
DECLARE_CLASS(MangoTable, MangoTablePrototype);

/**
 * Frees the table.
 * \param   table   Table to be freed.
 */
extern void mango_table_dealloc(MangoTable *table);

/**
 * Returns the table size.
 * \param   table   Table whose size is to be returned.
 * \return size of the table.
 */
extern int mango_table_size(MangoTable *table);

/**
 * Gets a value by key.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be searched.
 */
extern MangoObject *mango_table_get(MangoTable *table, MangoString *key);

/**
 * Tells if a value exists.
 * \param   table   Table to search in.
 * \param   key     key by which the element is to be searched.
 * \return  True if value exists for key, false otherwise.
 */
extern BOOL mango_table_contains(MangoTable *table, MangoString *key);

/**
 * Puts a value by key, replacing and returning the old value if any.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be inserted.
 * \param   value   New value.
 * \return old value if it exists, otherwise NULL.
 */
extern MangoObject *mango_table_put(MangoTable *table, MangoString *key, MangoObject *value);

/**
 * Erases an element from the table.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be erased.
 * \return The erased value if it exists.
 */
extern MangoObject *mango_table_erase(MangoTable *table, MangoString *key);

#ifdef __cplusplus
}
#endif

#endif


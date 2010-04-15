
#ifndef __MANGO_TABLE_H__
#define __MANGO_TABLE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * General associate container for a set of homogeneous items.
 */
struct MangoTable
{
    void *entries;

    /**
     * Returns the number of entries.
     */
    int (*sizeFunc)(void *entries);

    /**
     * Frees the entire table.
     */
    void (*freeTableFunc)(void *entries);

    /**
     * Function to free each entry in the table on clearing.
     */
    void (*freeEntryFunc)(void *entries);

    /**
     * Gets a value by key.
     */
    void *(*getFunc)(void *entries, void *key);

    /**
     * Tells if a value exists.
     */
    BOOL (*containsFunc)(void *entries, void *key);

    /**
     * Puts a value by key, replacing and returning the old value if any.
     */
    void *(*putFunc)(void *entries, void *key, void *value);

    /**
     * Erases an element from the table.
     */
    void *(*eraseFunc)(void *entries, void *key);
};

/**
 * Frees the table.
 * \param   table   Table to be freed.
 */
extern void mango_table_free(MangoTable *table);

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
extern void *mango_table_get(MangoTable *table, void *key);

/**
 * Tells if a value exists.
 * \param   table   Table to search in.
 * \param   key     key by which the element is to be searched.
 * \return  True if value exists for key, false otherwise.
 */
extern BOOL mango_table_contains(MangoTable *table, void *key);

/**
 * Puts a value by key, replacing and returning the old value if any.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be inserted.
 * \param   value   New value.
 * \return old value if it exists, otherwise NULL.
 */
extern void *mango_table_put(MangoTable *table, void *key, void *value);

/**
 * Erases an element from the table.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be erased.
 * \return The erased value if it exists.
 */
extern void *mango_table_erase(MangoTable *table, void *key);

#ifdef __cplusplus
}
#endif

#endif


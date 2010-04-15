
#include "mtable.h"

/**
 * Frees the table.
 * \param   table   Table to be freed.
 */
void mango_table_free(MangoTable *table)
{
    if (table->entries != NULL && table->freeTableFunc != NULL)
    {
        table->freeTableFunc(table->entries);
        table->entries = NULL;
    }
}

/**
 * Returns the table size.
 * \param   table   Table whose size is to be returned.
 * \return size of the table.
 */
int mango_table_size(MangoTable *table)
{
    if (table->entries != NULL && table->sizeFunc != NULL)
    {
        return table->sizeFunc(table->entries);
    }
    return 0;
}

/**
 * Gets a value by key.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be searched.
 */
void *mango_table_get(MangoTable *table, void *key)
{
    if (table->entries != NULL && table->getFunc != NULL)
    {
        return table->getFunc(table->entries, key);
    }
    return NULL;
}

/**
 * Tells if a value exists.
 * \param   table   Table to search in.
 * \param   key     key by which the element is to be searched.
 * \return  True if value exists for key, false otherwise.
 */
BOOL mango_table_contains(MangoTable *table, void *key)
{
    if (table->entries != NULL && table->containsFunc != NULL)
    {
        return table->containsFunc(table->entries, key);
    }
    return false;
}

/**
 * Puts a value by key, replacing and returning the old value if any.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be inserted.
 * \param   value   New value.
 * \return old value if it exists, otherwise NULL.
 */
void *mango_table_put(MangoTable *table, void *key, void *value)
{
    if (table->entries != NULL && table->putFunc != NULL)
    {
        return table->putFunc(table->entries, key, value);
    }
    return NULL;
}

/**
 * Erases an element from the table.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be erased.
 * \return The erased value if it exists.
 */
void *mango_table_erase(MangoTable *table, void *key)
{
    if (table->entries != NULL && table->eraseFunc != NULL)
    {
        return table->eraseFunc(table->entries, key);
    }
    return NULL;
}

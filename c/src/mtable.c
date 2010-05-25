
#include "mtable.h"

/**
 * Gets a value by key.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be searched.
 */
MangoObject *mango_table_get(MangoTable *table, const MangoString *key)
{
    if (table->__prototype__->getFunc != NULL)
    {
        return table->__prototype__->getFunc(table, key);
    }
    return NULL;
}

/**
 * Frees the table.
 * \param   table  Collection to be freed.
 */
void mango_table_dealloc(MangoTable *table)
{
    mango_collection_dealloc((MangoCollection *)table);
}

/**
 * Tells if a value exists.
 * \param   table   Table to search in.
 * \param   key     key by which the element is to be searched.
 * \return  True if value exists for key, false otherwise.
 */
BOOL mango_table_contains(MangoTable *table, const MangoString *key)
{
    if (table->__prototype__->containsFunc != NULL)
    {
        table->__prototype__->containsFunc(table, key);
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
MangoObject *mango_table_put(MangoTable *table, MangoString *key, MangoObject *value)
{
    if (table->__prototype__->putFunc != NULL)
    {
        table->__prototype__->putFunc(table, key, value);
    }
    return NULL;
}

/**
 * Erases an element from the table.
 * \param   table   Table to be searched.
 * \param   key     Key by which the element is to be erased.
 * \return The erased value if it exists.
 */
MangoObject *mango_table_erase(MangoTable *table, const MangoString *key)
{
    if (table->__prototype__->eraseFunc != NULL)
    {
        table->__prototype__->eraseFunc(table, key);
    }
    return NULL;
}

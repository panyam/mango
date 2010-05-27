
#include "mtable.h"

/**
 * Frees the table.
 * \param   table  Collection to be freed.
 */
void mango_table_dealloc(MangoTable *table)
{
    mango_collection_dealloc((MangoCollection *)table);
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
 */
void mango_table_erase(MangoTable *table, const MangoString *key)
{
    if (table->__prototype__->eraseFunc != NULL)
    {
        table->__prototype__->eraseFunc(table, key);
    }
}

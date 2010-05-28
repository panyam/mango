
#include "mtable.h"

/**
 * Puts multiple values into a table.  Values are entered as key and value
 * pairs and terminated by the first NULL key argument.
 */
MangoTable *mango_table_put_values(MangoTable *table, ...)
{
    va_list ap;
    va_start(ap, table);
    MangoString *key = va_arg(ap, MangoString *);
    while (key != NULL)
    {
        MangoObject *value = va_arg(ap, MangoObject *);
        mango_table_put(table, key, value);
        key = va_arg(ap, MangoString *);
    }
    va_end(ap);
    return table;
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

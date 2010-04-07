
#ifndef __MANGO_STRING_TABLE_H__
#define __MANGO_STRING_TABLE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoStringTable
{
    void *data;
};

/**
 * Creates a new string table.
 * \return  A new mango string table instance.
 */
extern MangoStringTable *mango_string_table_new();

/**
 * Frees a string table created with the above new method.
 * \param   mstable The mango string table to be destroyed.
 */
extern void mango_string_table_free(MangoStringTable *mstable);

/**
 * Finds the index of a particular string.
 * \param   stable  Table in which to find the string.
 * \param   str     String to find
 * \param   length  Length of the string to find, if -ve, str is null
 *                  terminated.
 * \param   create  If the string is not found, it will be created, if this
 *                  parameter is set.
 * 
 * \return  The index of the string if it exists or if it was created,
 * otherwise -1.
 */
extern int mango_string_table_find(MangoStringTable *   stable,
                                   const char *         str,
                                   int                  length,
                                   BOOL                 create);

#ifdef __cplusplus
}
#endif

#endif


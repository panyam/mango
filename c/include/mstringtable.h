
#ifndef __MANGO_STRING_TABLE_H__
#define __MANGO_STRING_TABLE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MangoStringData
{
    int     strId;
    char *  strValue;
    int     strLength;
    int     refCount;
} MangoStringData;

struct MangoStringTable
{
    void *data;
};

/**
 * Gets the default string table.
 * \return  The default global string table.
 */
extern MangoStringTable *mango_string_table_default();

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
 * \param   rcdelta How much to change the refcount by.
 * 
 * \return  The index of the string if it exists or if it was created,
 * otherwise -1.
 */
extern int mango_string_table_find(MangoStringTable *   stable,
                                   const char *         str,
                                   int                  length,
                                   BOOL                 create,
                                   int                  rcdelta);

/**
 * Gets the string data for a particular string ID.
 * \param   mstable The mango string table to be searched.
 * \param   strid   ID of the string to be searched.
 */
extern const MangoStringData *mango_string_table_free(MangoStringTable *mstable,
                                                      int strid);

/**
 * Increments the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
extern void mango_string_table_incref(MangoStringTable *mstable, int strid);

/**
 * Decrements the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
extern void mango_string_table_decref(MangoStringTable *mstable, int strid);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_RCSTRING_TABLE_H__
#define __MANGO_RCSTRING_TABLE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MangoRCStringData
{
    int     strId;
    int     strLength;
    int     refCount;
    char *  strValue;
} MangoRCStringData;

struct MangoRCStringTable
{
    MangoRawArray * entriesByIndex;
    MangoBinTree *  entriesByName;
};

/**
 * Gets the default string table.
 * \return  The default global string table.
 */
extern MangoRCStringTable *mango_rcstring_table_default();

/**
 * Creates a new string table.
 * \return  A new mango string table instance.
 */
extern MangoRCStringTable *mango_rcstring_table_new();

/**
 * Frees a string table created with the above new method.
 * \param   mstable The mango string table to be destroyed.
 */
extern void mango_rcstring_table_free(MangoRCStringTable *mstable);

/**
 * Clears all entries from the string table but the table itself is not
 * destroyed.
 * \param   mstable The mango string table to be cleared.
 */
extern void mango_rcstring_table_clear(MangoRCStringTable *mstable);

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
extern int mango_rcstring_table_find(MangoRCStringTable *   stable,
                                   const char *         str,
                                   int                  length,
                                   BOOL                 create,
                                   int                  rcdelta);

/**
 * Gets the string data for a particular string ID.
 * \param   mstable The mango string table to be searched.
 * \param   strid   ID of the string to be searched.
 */
extern const MangoRCStringData *mango_rcstring_table_get(const MangoRCStringTable *mstable,
                                                     int strid);

/**
 * Increments the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
extern void mango_rcstring_table_incref(MangoRCStringTable *mstable, int strid);

/**
 * Decrements the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
extern void mango_rcstring_table_decref(MangoRCStringTable *mstable, int strid);

#ifdef __cplusplus
}
#endif

#endif



#include <string.h>
#include "mstringtable.h"
#include "mmemutils.h"
#include "mbintree.h"
#include "marray.h"

typedef struct StringTableEntry
{
    int     strId;
    char *  strValue;
    int     strLength;
} StringTableEntry;

/**
 * Compare two string table nodes by their string value.
 */
int stablenode_compare(const void *a, const void *b)
{
    const StringTableEntry *stna = (const StringTableEntry *)a;
    const StringTableEntry *stnb = (const StringTableEntry *)b;
    return strcmp(stna->strValue, stnb->strValue);
}

/**
 * Return the StringTable entries of a String Table by index.
 */
MangoArray *mango_string_table_by_index(MangoStringTable *mstable)
{
    return (MangoArray *)(((void **)mstable->data)[0]);
}

/**
 * Return the StringTable entries of a String Table by name.
 */
MangoBinTree *mango_string_table_by_name(MangoStringTable *mstable)
{
    return (MangoArray *)(((void **)mstable->data)[1]);
}

/**
 * Creates a new string table.
 * \return  A new mango string table instance.
 */
MangoStringTable *mango_string_table_new()
{
    MangoStringTable *mstable = ZNEW(MangoStringTable);
    mstable->data = ZNEW_ARRAY(void *, 2);
    ((void **)mstable->data)[0] = mango_array_new();
    ((void **)mstable->data)[1] = mango_bintree_new();
    return mstable;
}

/**
 * Frees a string table created with the above new method.
 * \param   mstable The mango string table to be destroyed.
 */
void mango_string_table_free(MangoStringTable *mstable)
{
    if (mstable->data != NULL)
    {
        NOT_IMPLEMENTED();
        // mango_bintree_free((MangoBinTree *)mstable->data);
    }
    free(mstable);
}

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
int mango_string_table_find(MangoStringTable *  stable,
                            const char *        str,
                            int                 length,
                            BOOL                create)
{
    if (stable->data == NULL)
    {
        if (!create)
            return false;
        stable->data = mango_bintree_new();
    }

    MangoBinTree *  bintree = mango_string_table_by_name(stable);
    MangoArray *    array   = mango_string_table_by_index(stable);
    StringTableEntry stentry;
    stentry.strValue = (char *)str;
    stentry.strLength = length;
    MangoBinTreeNode *node = mango_bintree_find(bintree, &stentry, stablenode_compare);
    int strId = -1;
    if (node == NULL && create)
    {
        strId = mango_bintree_size(bintree) + 1;
        StringTableEntry *newentry = ZNEW(StringTableEntry);
        newentry->strId      = strId;
        newentry->strLength  = length;
        newentry->strValue   = NEW_ARRAY(char, length);
        memcpy(newentry->strValue, str, length);
        node = mango_bintree_insert(bintree, newentry, stablenode_compare);
        mango_array_insert(array, newentry, -1);
    }
    return strId;
}



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
    int     refCount;
} StringTableEntry;

typedef struct StringTableImpl
{
    MangoArray *    entriesByIndex;
    MangoBinTree *  entriesByName;
} StringTableImpl;

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
    return ((StringTableImpl *)mstable->data)->entriesByIndex;
}

/**
 * Return the StringTable entries of a String Table by name.
 */
MangoBinTree *mango_string_table_by_name(MangoStringTable *mstable)
{
    return ((StringTableImpl *)mstable->data)->entriesByName;
}

/**
 * Increments the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
void mango_string_table_incref(MangoStringTable *mstable, int strid)
{
    MangoArray *entriesByIndex = mango_string_table_by_index(mstable);
    StringTableEntry *entry = mango_array_itemat(entriesByIndex, strid);
    entry->refCount++;
}

/**
 * Decrements the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
void mango_string_table_decref(MangoStringTable *mstable, int strid)
{
    MangoArray *entriesByIndex = mango_string_table_by_index(mstable);
    StringTableEntry *entry = mango_array_itemat(entriesByIndex, strid);
    entry->refCount--;
    if (entry->refCount <= 0)
    {
        // TODO: delete it?
    }
}

/**
 * Creates a new string table.
 * \return  A new mango string table instance.
 */
MangoStringTable *mango_string_table_new()
{
    MangoStringTable *mstable = NEW(MangoStringTable);
    mstable->data = NEW(StringTableImpl);
    ((StringTableImpl *)mstable->data)->entriesByIndex = mango_array_new();
    ((StringTableImpl *)mstable->data)->entriesByName = mango_bintree_new();
    return mstable;
}

/**
 * Gets the default string table.
 * \return  The default global string table.
 */
MangoStringTable *mango_string_table_default()
{
    MangoStringTable *DEFAULT_STRING_TABLE = NULL;
    if (DEFAULT_STRING_TABLE  == NULL)
    {
        DEFAULT_STRING_TABLE = mango_string_table_new();
    }
    return DEFAULT_STRING_TABLE;
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
 * \param   rcdelta How much to change the refcount by.
 * 
 * \return  The index of the string if it exists or if it was created,
 * otherwise -1.
 */
int mango_string_table_find(MangoStringTable *  stable,
                            const char *        str,
                            int                 length,
                            BOOL                create,
                            int                 rcdelta)
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
        newentry->refCount   = 0;
        memcpy(newentry->strValue, str, length);
        node = mango_bintree_insert(bintree, newentry, stablenode_compare);
        mango_array_insert(array, newentry, -1);
    }

    if (node != NULL)
    {
        StringTableEntry *stEntry = (StringTableEntry *)node->data;
        stEntry += rcdelta;
        if (stEntry->refCount <= 0)
        {
            stEntry->refCount = 0;
            // TODO: what do we do here? delete it to save space?
        }
    }
    return strId;
}



#include <string.h>
#include "mrcstringtable.h"
#include "mmemutils.h"
#include "mbintree.h"
#include "marray.h"

typedef struct StringTableImpl
{
    MangoArray *    entriesByIndex;
    MangoBinTree *  entriesByName;
} StringTableImpl;

void rcstringdata_free(MangoRCStringData *rcsdata)
{
    free(rcsdata->strValue);
    free(rcsdata);
}

/**
 * Compare two string table nodes by their string value.
 */
int stablenode_compare(const void *a, const void *b)
{
    const MangoRCStringData *stna = (const MangoRCStringData *)a;
    const MangoRCStringData *stnb = (const MangoRCStringData *)b;

    int cmp = memcmp(stna->strValue, stnb->strValue, stna->strLength <= stnb->strLength ? stna->strLength : stnb->strLength);
    if (cmp == 0)
        cmp = stna->strLength - stnb->strLength;
    return cmp;
}

/**
 * Return the StringTable entries of a String Table by index.
 */
MangoArray *mango_rcstring_table_by_index(MangoRCStringTable *mstable)
{
    return ((StringTableImpl *)mstable->data)->entriesByIndex;
}

/**
 * Return the StringTable entries of a String Table by name.
 */
MangoBinTree *mango_rcstring_table_by_name(MangoRCStringTable *mstable)
{
    return ((StringTableImpl *)mstable->data)->entriesByName;
}

/**
 * Increments the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
void mango_rcstring_table_incref(MangoRCStringTable *mstable, int strid)
{
    MangoArray *entriesByIndex = mango_rcstring_table_by_index(mstable);
    MangoRCStringData *entry = mango_array_itemat(entriesByIndex, strid);
    entry->refCount++;
}

/**
 * Decrements the reference count of a string.
 * \param   mstable Table in which to find the string.
 * \param   strid   ID of the string.
 */
void mango_rcstring_table_decref(MangoRCStringTable *mstable, int strid)
{
    MangoArray *entriesByIndex = mango_rcstring_table_by_index(mstable);
    MangoRCStringData *entry = mango_array_itemat(entriesByIndex, strid);
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
MangoRCStringTable *mango_rcstring_table_new()
{
    MangoRCStringTable *mstable = NEW(MangoRCStringTable);
    mstable->data = NEW(StringTableImpl);
    MangoArray *array = mango_array_new();
    mango_array_insert(array, NULL, -1);  // reserve index 0 for NULL entries
    ((StringTableImpl *)mstable->data)->entriesByIndex = array;
    ((StringTableImpl *)mstable->data)->entriesByName = mango_bintree_new();
    return mstable;
}

/**
 * Gets the default string table.
 * \return  The default global string table.
 */
MangoRCStringTable *mango_rcstring_table_default()
{
    static MangoRCStringTable *DEFAULT_STRING_TABLE = NULL;
    if (DEFAULT_STRING_TABLE  == NULL)
    {
        DEFAULT_STRING_TABLE = mango_rcstring_table_new();
    }
    return DEFAULT_STRING_TABLE;
}

/**
 * Frees a string table created with the above new method.
 * \param   mstable The mango string table to be destroyed.
 */
void mango_rcstring_table_free(MangoRCStringTable *mstable)
{
    mango_rcstring_table_clear(mstable);
    if (mstable->data != NULL)
    {
        free(mstable->data);
        mstable->data = NULL;
    }
    free(mstable);
}

/**
 * Clears all entries from the string table but the table itself is not
 * destroyed.
 * \param   mstable The mango string table to be cleared.
 */
void mango_rcstring_table_clear(MangoRCStringTable *mstable)
{
    if (mstable->data != NULL)
    {
        MangoBinTree *  bintree = mango_rcstring_table_by_name(mstable);
        MangoArray *    array   = mango_rcstring_table_by_index(mstable);
        mango_bintree_clear(bintree, rcstringdata_free);
        mango_array_clear(array, NULL);
        mango_array_insert(array, NULL, -1);  // reserve index 0 for NULL entries
    }
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
int mango_rcstring_table_find(MangoRCStringTable *  stable,
                            const char *        str,
                            int                 length,
                            BOOL                create,
                            int                 rcdelta)
{
    if (stable->data == NULL)
    {
        if (!create)
            return -1;
        stable->data = mango_bintree_new();
    }

    if (length < 0)
        length = strlen(str);

    MangoBinTree *  bintree = mango_rcstring_table_by_name(stable);
    MangoArray *    array   = mango_rcstring_table_by_index(stable);
    MangoRCStringData stentry;
    stentry.strValue = (char *)str;
    stentry.strLength = length;
    MangoBinTreeNode *node = mango_bintree_find(bintree, &stentry, stablenode_compare);
    int strId = -1;
    BOOL created = false;
    MangoRCStringData *msdata = NULL;
    if (node == NULL && create)
    {
        created             = true;
        strId               = mango_bintree_size(bintree) + 1;
        msdata              = ZNEW(MangoRCStringData);
        msdata->strId       = strId;
        msdata->strLength   = length;
        msdata->strValue    = NEW_ARRAY(char, length + 1);
        msdata->refCount    = rcdelta > 0 ? rcdelta : 1;
        memcpy(msdata->strValue, str, length);
        msdata->strValue[length] = 0;
        node = mango_bintree_insert(bintree, msdata, stablenode_compare);
        mango_array_insert(array, msdata, -1);
    }
    else if (node != NULL)
    {
        msdata  = (MangoRCStringData *)node->data;
        strId   = msdata->strId;
    }

    if (msdata != NULL && !created)
    {
        // only updated ref count if a node was found and 
        // it was not newly created
        msdata->refCount        += rcdelta;
        if (msdata->refCount <= 0)
        {
            msdata->refCount = 0;
            // TODO: what do we do here? delete it to save space?
        }
    }
    return strId;
}


/**
 * Gets the string data for a particular string ID.
 * \param   mstable The mango string table to be searched.
 * \param   strid   ID of the string to be searched.
 */
const MangoRCStringData *mango_rcstring_table_get(const MangoRCStringTable *mstable, int strid)
{
    return (const MangoRCStringData *)mango_array_itemat(((StringTableImpl *)mstable->data)->entriesByIndex, strid);
}


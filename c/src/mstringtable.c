
#include <string.h>
#include "mstringtable.h"
#include "mmemutils.h"
#include "mbintree.h"

typedef struct StringTableNode
{
    int     strId;
    char *  strValue;
    int     strLength;
} StringTableNode;

/**
 * Compare two string table nodes by their string value.
 */
int stablenode_compare(const void *a, const void *b)
{
    const StringTableNode *stna = (const StringTableNode *)a;
    const StringTableNode *stnb = (const StringTableNode *)b;
    return strcmp(stna->strValue, stnb->strValue);
}


/**
 * Creates a new string table.
 * \return  A new mango string table instance.
 */
MangoStringTable *mango_string_table_new()
{
    return ZNEW(MangoStringTable);
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

    MangoBinTree *  bintree = (MangoBinTree *)stable->data;
    StringTableNode stnode;
    stnode.strValue = (char *)str;
    stnode.strLength = length;
    MangoBinTreeNode *node = mango_bintree_find(bintree, &stnode, stablenode_compare);
    int strId = -1;
    if (node == NULL && create)
    {
        strId = mango_bintree_size(bintree) + 1;
        StringTableNode *newnode = ZNEW(StringTableNode);
        newnode->strId      = strId;
        newnode->strLength  = length;
        newnode->strValue   = NEW_ARRAY(char, length);
        memcpy(newnode->strValue, str, length);
        node = mango_bintree_insert(bintree, newnode, stablenode_compare);
    }
    return strId;
}


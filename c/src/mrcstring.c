
#include <stdarg.h>
#include "merror.h"
#include "mrcstring.h"
#include "mstringtable.h"
#include "mmemutils.h"

MangoPrototype *mango_rcstring_prototype()
{
    static MangoPrototype *RCSTRING_PROTOTYPE = NULL;
    if (RCSTRING_PROTOTYPE == NULL)
    {
        RCSTRING_PROTOTYPE = NEW(MangoStringPrototype);
        RCSTRING_PROTOTYPE->bufferFunc  = mango_rcstring_buffer;
        RCSTRING_PROTOTYPE->sizeFunc    = mango_rcstring_size;
        RCSTRING_PROTOTYPE->copyFunc    = mango_rcstring_copy;
        RCSTRING_PROTOTYPE->releaseFunc = mango_rcstring_release;
        RCSTRING_PROTOTYPE->equalsFunc  = mango_rcstrings_are_equal;
        RCSTRING_PROTOTYPE->compareFunc = mango_rcstring_compare;
    }
    return RCSTRING_PROTOTYPE;
}

/**
 * Creates a new immutale string.
 * \param   value   Value of the string.
 * \param   lenght  Length of the string.  If -ve then string is null
 *                  terminated.
 * \param   mstable The String table/pool from which the string is to be
 *                  sourced.  If NULL, then the default table is used.
 *
 * \return  A new instance of the immutable string.
 */
MangoString mango_rcstring_new(const char *value, int length, MangoRCStringTable *mstable)
{
    if (mstable == NULL)
        mstable = mango_rcstring_table_default();
    if (length < 0)
        length = strlen(value);
    MangoRCString *mstr = NEW(MangoRCString);
    mstr->internId  = mango_rcstring_table_find(mstable, value, length, true, 1);
    mstr->mstable   = mstable;
    return mango_string_new(mstr, mango_rcstring_prototype());
}

/**
 * Makes a copy of another string.
 *
 * \param   buffer  Buffer of the values to copy.
 * \param   length  Length of the buffer.  If length < 0, then buffer is
 *                  null terminated.
 * \return A new string instance.
 */
MangoRCString *mango_rcstring_copy(const MangoRCString *another)
{
    MangoRCString *mstr   = NEW(MangoRCString);
    mango_rcstring_table_incref(another->mstable, another->internId);
    mstr->internId      = another->internId;
    mstr->mstable       = another->mstable;
    return mstr;
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_rcstring_free(MangoRCString *mstr)
{
    mango_rcstring_table_decref(mstr->mstable, mstr->internId);
    free(mstr);
}

/**
 * Compares the string contents with another buffer.
 *
 * \param   mstr1   First String being compared with.
 * \param   mstr2   Second String being compared to.
 *
 * \return -1 if mstr < value, 0 if equal else +1
 */
int mango_rcstring_compare(const MangoRCString *mstr1, const MangoRCString *mstr2)
{
    if (mstr1->mstable == mstr2->mstable)
    {
        return mstr1->internId - mstr2->internId;
    }
    return mstr1->mstable - mstr2->mstable;
}

/**
 * Tells if two strings are equal.
 */
BOOL mango_rcstrings_are_equal(const MangoRCString *mstr1, const MangoRCString *mstr2)
{
    return mstr1->internId == mstr2->internId &&
            mstr1->mstable == mstr2->mstable;
}

/**
 * Gets the buffer value of the string.
 */
const char *mango_rcstring_value(const MangoRCString *mstr)
{
    const MangoRCStringData *msData = mango_rcstring_table_get(mstr->mstable, mstr->internId);
    return msData->strValue;
}

/**
 * Gets the length of the string.
 */
size_t mango_rcstring_length(const MangoRCString *mstr)
{
    const MangoRCStringData *msData = mango_rcstring_table_get(mstr->mstable, mstr->internId);
    return msData->strLength;
}


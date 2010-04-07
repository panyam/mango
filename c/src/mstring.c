
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "merror.h"
#include "mstring.h"
#include "mstringtable.h"
#include "mmemutils.h"

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
MangoString *mango_string_new(const char *value, int length,
                              MangoStringTable *mstable)
{
    if (mstable == NULL)
        mstable = mango_string_table_default();
    if (length < 0)
        length = strlen(value);
    MangoString *mstr = NEW(MangoString);
    mstr->internId  = mango_string_table_find(mstable, value, length, true, 1);
    mstr->mstable   = mstable;
    return mstr;
}

/**
 * Makes a copy of another string.
 *
 * \param   buffer  Buffer of the values to copy.
 * \param   length  Length of the buffer.  If length < 0, then buffer is
 *                  null terminated.
 * \return A new string instance.
 */
MangoString *mango_string_copy(const MangoString *another)
{
    MangoString *mstr   = NEW(MangoString);
    mango_string_table_incref(another->mstable, another->internId);
    mstr->internId      = another->internId;
    mstr->mstable       = another->mstable;
    return mstr;
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_string_free(MangoString *mstr)
{
    mango_string_table_decref(mstr->mstable, mstr->internId);
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
int mango_string_compare(const MangoString *mstr1, const MangoString *mstr2)
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
BOOL mango_strings_are_equal(const MangoString *mstr1, const MangoString *mstr2)
{
    return mstr1->internId == mstr2->internId &&
            mstr1->mstable == mstr2->mstable;
}



#include "mangopub.h"

DECLARE_PROTO_FUNC(mango_rcstring_prototype, MangoStringPrototype, mango_string_prototype(),
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_rcstring_dealloc;
    ((MangoPrototype *)&__proto__)->equalsFunc  = (ObjectEqualsFunc)mango_rcstrings_are_equal;
    ((MangoPrototype *)&__proto__)->compareFunc = (ObjectCompareFunc)mango_rcstring_compare;
    __proto__.bufferFunc                        = (StringBufferFunc)mango_rcstring_buffer;
    __proto__.sizeFunc                          = (StringLengthFunc)mango_rcstring_length;
    __proto__.compareToBufferFunc               = (StringCompareToBufferFunc)mango_rcstring_compare_to_buffer;
);

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
MangoRCString *mango_rcstring_new(const char *value, int length, MangoRCStringTable *mstable)
{
    if (mstable == NULL)
        mstable = mango_rcstring_table_default();
    if (length < 0)
        length = strlen(value);
    MangoRCString *mstr = OBJ_ALLOC(MangoRCString, mango_rcstring_prototype());
    mstr->mstable       = mstable;
    mstr->internId      = mango_rcstring_table_find(mstable, value, length, true, 1);
    mstr->strPtr        = mango_rcstring_buffer(mstr);
    return mstr;
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_rcstring_dealloc(MangoRCString *mstr)
{
    mango_rcstring_table_decref(mstr->mstable, mstr->internId);
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
const char *mango_rcstring_buffer(const MangoRCString *mstr)
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

/**
 * Compares a string with the contents of a buffer.
 *
 * \param   str     String being compared.
 * \param   buff    Value being compared to.
 * \param   length  Length of the buffer.  If -ve, then buff is null terminated.
 *
 * \return  -ve if str < buff, 0 if they are equal, +ve otherwise
 */
int mango_rcstring_compare_to_buffer(const MangoRCString *str, const char *buffer, int length)
{
    const MangoRCStringData *msData = mango_rcstring_table_get(str->mstable, str->internId);

    if (length < 0) length = strlen(buffer);

    int minl = msData->strLength < length ? msData->strLength : length;
    int result = memcmp(str, buffer, minl);
    return result != 0 ? result : msData->strLength - length;
}


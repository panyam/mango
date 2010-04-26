
#include "merror.h"
#include "mstringbuffer.h"
#include "mstringfactory.h"
#include "mrcstring.h"
#include "mrcstringtable.h"
#include "mmemutils.h"

MangoStringPrototype *mango_rcstring_prototype()
{
    static BOOL initialised = false;
    static MangoStringPrototype RCSTRING_PROTOTYPE;
    if (!initialised)
    {
        RCSTRING_PROTOTYPE.bufferFunc  = (StringBufferFunc)mango_rcstring_buffer;
        RCSTRING_PROTOTYPE.sizeFunc    = (StringLengthFunc)mango_rcstring_length;
        RCSTRING_PROTOTYPE.copyFunc    = (StringCopyFunc)mango_rcstring_copy;
        ((MangoPrototype *)&RCSTRING_PROTOTYPE)->deleteFunc = (PrototypeCleanUpFunc)mango_rcstring_release;
        ((MangoPrototype *)&RCSTRING_PROTOTYPE)->equalsFunc  = (PrototypeEqualsFunc)mango_rcstrings_are_equal;
        ((MangoPrototype *)&RCSTRING_PROTOTYPE)->compareFunc = (PrototypeCompareFunc)mango_rcstring_compare;
        initialised = true;
    }
    return &RCSTRING_PROTOTYPE;
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
MangoString *mango_rcstring_new(const char *value,
                                int length,
                                MangoRCStringTable *mstable)
{
    if (mstable == NULL)
        mstable = mango_rcstring_table_default();
    if (length < 0)
        length = strlen(value);
    MangoRCString *mstr = ZNEW(MangoRCString);
    mstr->__prototype__ = mango_rcstring_prototype();
    mstr->__refCount__  = 1;
    mstr->mstable       = mstable;
    mstr->internId      = mango_rcstring_table_find(mstable, value, length, true, 1);
    return (MangoString *)mstr;
}

/**
 * Makes a copy of another string.
 *
 * \param   buffer  Buffer of the values to copy.
 * \param   length  Length of the buffer.  If length < 0, then buffer is
 *                  null terminated.
 * \return A new string instance.
 */
void mango_rcstring_copy(const MangoRCString *source, MangoString *another)
{
    MangoRCString *mstr     = ZNEW(MangoRCString);
    mango_rcstring_table_incref(source->mstable, source->internId);
    mstr->internId          = source->internId;
    mstr->mstable           = source->mstable;
    another->__prototype__  = mango_rcstring_prototype();
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_rcstring_release(MangoRCString *mstr)
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



#include <stdarg.h>
#include "merror.h"
#include "mrcstring.h"
#include "mrcstringtable.h"
#include "mmemutils.h"

MangoStringPrototype *mango_rcstring_prototype()
{
    static MangoStringPrototype *RCSTRING_PROTOTYPE = NULL;
    if (RCSTRING_PROTOTYPE == NULL)
    {
        RCSTRING_PROTOTYPE = NEW(MangoStringPrototype);
        RCSTRING_PROTOTYPE->bufferFunc  = mango_rcstring_buffer;
        RCSTRING_PROTOTYPE->sizeFunc    = mango_rcstring_length;
        RCSTRING_PROTOTYPE->copyFunc    = mango_rcstring_copy;
        RCSTRING_PROTOTYPE->releaseFunc = mango_rcstring_release;
        RCSTRING_PROTOTYPE->equalsFunc  = mango_rcstrings_are_equal;
        RCSTRING_PROTOTYPE->compareFunc = mango_rcstring_compare;
    }
    return RCSTRING_PROTOTYPE;
}

/**
 * Creates a new string.
 */
MangoString *mango_rcstringfactory_new_string(MangoRCStringTable *mstable, const char *buffer, int length)
{
    MangoString *out = NEW(MangoString);
    *out = mango_rcstring_new(buffer, length, mstable);
    return out;
}

/**
 * Creates a new string from a string buffer.
 */
MangoString *mango_rcstringfactory_from_buffer(MangoRCStringTable *mstable, const MangoStringBuffer *buffer)
{
    return mango_rcstring_new(msbuffer->buffer, msbuffer->length, mstable);
}

/**
 * Creates a new immutale string factory.
 * \return  A new instance of the immutable string.
 */
MangoStringFactory *mango_rcstringfactory_new()
{
    MangoStringFactory *msfactory = NEW(MangoStringFactory);
    msfactory->data             = mango_rcstring_table_new;
    msfactory->cleanupFunc      = mango_rcstring_table_free;
    msfactory->newStringFunc    = mango_rcstringfactory_new_string;
    msfactory->fromBufferFunc   = mango_rcstringfactory_from_buffer;
    return msfactory;
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
    return mango_string_new(mango_rcstring_prototype(), mstr);
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
    MangoRCString *mstr   = NEW(MangoRCString);
    mango_rcstring_table_incref(source->mstable, source->internId);
    mstr->internId      = source->internId;
    mstr->mstable       = source->mstable;
    another->data       = mstr;
    another->prototype  = mango_rcstring_prototype();
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_rcstring_release(MangoRCString *mstr)
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


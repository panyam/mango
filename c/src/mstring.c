
#include "merror.h"
#include "mstring.h"
#include "mmemutils.h"

/**
 * Creates a new string with its data and prototype.
 * \param   proto   Prototype for the string.
 * \param   data    Implementation specific data for the string.
 */
MangoString mango_string_new(MangoStringPrototype *proto, void *data)
{
    MangoString out;
    out.prototype = proto;
    out.data = data;
    return out;
}

/**
 * Copies another mango string.
 * \param   mstr    String to be copied.
 * \return  A new instance of the immutable string.
 */
void mango_string_copy(const MangoString *mstr, MangoString *another)
{
    return mstr->prototype->copyFunc(mstr->data, another);
}

/**
 * Releases a string.
 *
 * \param   mstr String to be released.
 */
void mango_string_release(MangoString *mstr)
{
    return mstr->prototype->releaseFunc(mstr->data);
}

/**
 * Gets the buffer value of the string.
 */
const char *mango_string_buffer(const MangoString *mstr)
{
    return mstr->prototype->bufferFunc(mstr->data);
}

/**
 * Gets the length of the string.
 */
size_t mango_string_length(const MangoString *mstr)
{
    return mstr->prototype->sizeFunc(mstr->data);
}

/**
 * Compares the string contents with another buffer.
 *
 * \param   mstr    String being compared.
 * \param   value   String being compared to.
 * \param   length  Length of the string being compared to.
 *
 * \return -1 if mstr < value, 0 if equal else +1
 */
int mango_string_compare(const MangoString *mstr1, const MangoString *mstr2)
{
    return mstr1->prototype->compareFunc(mstr1->data, mstr2->data);
}

/**
 * Tells if two strings are equal.
 *
 * \param   mstr1   String being compared.
 * \param   mstr2   String being compared to.
 *
 * \return true if strings are equal, false otherwise.
 */
BOOL mango_strings_are_equal(const MangoString *mstr1, const MangoString *mstr2)
{
    return mstr1->prototype->equalsFunc(mstr1->data, mstr2->data);
}


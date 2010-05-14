
#include "merror.h"
#include "mstring.h"
#include "mmemutils.h"

/**
 * Copies another mango string.
 * \param   mstr    String to be copied.
 * \return  A new instance of the immutable string.
 */
void mango_string_copy_to(const MangoString *mstr, MangoString *another)
{
    mstr->__prototype__->copyFunc(mstr, another);
}

/**
 * Returns a copy of a string.
 * \param   mstr    String to be copied.
 * \return  The new copy of the string.
 */
MangoString *mango_string_copy(MangoString *mstr)
{
    MangoString *newstr = OBJ_ALLOC(MangoString, MangoStringPrototype);
    mstr->__prototype__->copyFunc(mstr, newstr);
    return newstr;
}

/**
 * Gets the buffer value of the string.
 */
const char *mango_string_buffer(const MangoString *mstr)
{
    return mstr->__prototype__->bufferFunc(mstr);
}

/**
 * Gets the length of the string.
 */
size_t mango_string_length(const MangoString *mstr)
{
    return mstr->__prototype__->sizeFunc(mstr);
}

/**
 * Compares two strings to see if they are equal.
 *
 * \param   str1    First str in the comparison.
 * \param   str2    Second str in the comparison.
 *
 * \return  true if Strings are equal false otherwise.
 */
BOOL mango_strings_are_equal(const MangoString *str1, const MangoString *str2)
{
    return mango_objects_are_equal((const MangoObject *)str1, (const MangoObject *)str2);
}

/**
 * Compares two objects to check their relative order.
 *
 * \param   str1    First str in the comparison.
 * \param   str2    Second str in the comparison.
 *
 * \return  -ve if str1 < str2, 0 if they are equal, +ve otherwise
 */
int mango_string_compare(const MangoString *str1, const MangoString *str2)
{
    return mango_object_compare((const MangoObject *)str1, (const MangoObject *)str2);
}


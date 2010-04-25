
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
    MangoString *newstr = NEW(MangoString);
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


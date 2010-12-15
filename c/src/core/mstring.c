
#include "mangopub.h"

/**
 * Default string prototype.
 */
DECLARE_PROTO_FUNC(mango_string_prototype, MangoStringPrototype, NULL);

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
 * Compares a string with the contents of a buffer.
 *
 * \param   str     String being compared.
 * \param   buff    Value being compared to.
 * \param   length  Length of the buffer.  If -ve, then buff is null terminated.
 *
 * \return  -ve if str < buff, 0 if they are equal, +ve otherwise
 */
int mango_string_compare_to_buffer(const MangoString *str, const char *buffer, int length)
{
    return str->__prototype__->compareToBufferFunc(str, buffer, length);
}


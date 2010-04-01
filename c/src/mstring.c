
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "merror.h"
#include "mstring.h"
#include "mmemutils.h"

/**
 * Create a new string with a given capacity.
 *
 * \param   capacity    Capacity of the string.
 */
MangoString *mango_string_new(unsigned capacity)
{
    MangoString *mstr   = ZNEW(MangoString);
    mstr->buffer        = NEW_ARRAY(char, capacity);
    mstr->capacity      = capacity;
    mstr->length        = 0;
    return mstr;
}

/**
 * Create a new string from a buffer.
 *
 * \param   buffer  Buffer of the values to copy.
 * \param   length  Length of the buffer.  If length < 0, then buffer is
 *                  null terminated.
 * \return A new string instance.
 */
MangoString *mango_string_from_buffer(const char *buffer, int length)
{
    if (length < 0)
        length = strlen(buffer);
    MangoString *mstr = mango_string_new(length + 1);
    memcpy(mstr->buffer, buffer, length);
    mstr->buffer[mstr->length] = 0;
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
    return mango_string_from_buffer(another->buffer, another->length);
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_string_free(MangoString *mstr)
{
    if (mstr->buffer != NULL)
        free(mstr->buffer);
    free(mstr);
}

/**
 * Clears the buffer.
 *
 * \param   mstr    String to be updated.
 */
void mango_string_clear(MangoString *mstr)
{
    mstr->length = 0;
}

/**
 * Sets the buffer value.
 *
 * \param   mstr    String to be updated.
 * \param   value   Value to be set to (not necessarily null terminated).
 * \param   length  Length of the input string.
 */
void mango_string_set(MangoString *mstr, const char *value, size_t length)
{
    mstr->length = 0;
    mango_string_append(mstr, value, length);
}

/**
 * Appends a value to the string buffer.
 *
 * \param   mstr    String to be updated.
 * \param   value   Value to be set to (not necessarily null terminated).
 * \param   length  Length of the input string.
 */
void mango_string_append(MangoString *mstr, const char *value, size_t length)
{
    mango_string_ensure_capacity(mstr, length + mstr->length + 1);
    memcpy(mstr->buffer + mstr->length, value, length);
    mstr->length += length;
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends a character.
 *
 * \param   mstr    String to be updated.
 * \param   chr     Character to be appended.
 */
void mango_string_append_char(MangoString *mstr, char ch)
{
    mango_string_ensure_capacity(mstr, mstr->length + 2);
    mstr->buffer[mstr->length++] = ch;
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends a short value.
 *
 * \param   mstr    String to be updated.
 * \param   value   Character to be appended.
 */
void mango_string_append_short(MangoString *mstr, short value)
{
    int nbytes = sizeof(value);
    mango_string_ensure_capacity(mstr, mstr->length + nbytes + 1);
    for (int i = 0;i < nbytes;i++)
    {
        mstr->buffer[mstr->length++] = ((char *)&value)[i];
    }
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends an int value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Short value to be appended.
 */
void mango_string_append_int(MangoString *mstr, int value)
{
    int nbytes = sizeof(value);
    mango_string_ensure_capacity(mstr, mstr->length + nbytes + 1);
    for (int i = 0;i < nbytes;i++)
    {
        mstr->buffer[mstr->length++] = ((char *)&value)[i];
    }
    mstr->buffer[mstr->length] = 0;
}

/**
 * Appends long value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Long value to be appended.
 */
void mango_string_append_long(MangoString *mstr, long value)
{
    int nbytes = sizeof(value);
    mango_string_ensure_capacity(mstr, mstr->length + nbytes + 1);
    for (int i = 0;i < nbytes;i++)
    {
        mstr->buffer[mstr->length++] = ((char *)&value)[i];
    }
    mstr->buffer[mstr->length] = 0;
}

/**
 * Formatted appending of contents to the end of the string.
 * Cannot append more than a total of 1024 characters at a time.
 *
 * \param   mstr    String to be appended.
 * \param   fmt     Format of the input.
 * \param   ...     Parameters to be appended.
 *
 * \returns Number of characters added.
 */
int mango_string_append_format(MangoString *mstr, const char *fmt, ...)
{
    char buff[1024];
    int len;
    va_list(ap);
    va_start(ap, fmt);
    len = vsnprintf(buff, 2047, fmt, ap);
    va_end(ap);
    mango_string_append(mstr, buff, len);
    return len;
}

/**
 * Ensures that the string has certain capacity.
 *
 * \param   mstr    String to be updated.
 * \param   newcap  New capacity to be made available in the string.
 */
void mango_string_ensure_capacity(MangoString *mstr, size_t newcap)
{
    if (mstr->capacity < newcap)
    {
        newcap          = (newcap * 3) / 2;
        mstr->buffer    = realloc(mstr->buffer, newcap);
        mstr->capacity  = newcap;
    }
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
int mango_string_compare(const MangoString *mstr, const char *value, size_t length)
{
    int minlen = mstr->length < length ? mstr->length : length;
    for (int i = 0;i < minlen;i++)
    {
        if (mstr->buffer[i] != value[i])
            return mstr->buffer[i] - value[i];
    }
    return mstr->length - length;
}

/**
 * Tells if two strings are equal.
 */
BOOL mango_strings_are_equal(const MangoString *mstr1, const MangoString *mstr2)
{
    return mango_string_compare(mstr1, mstr2->buffer, mstr2->length);
}


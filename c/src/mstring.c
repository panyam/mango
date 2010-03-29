
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "merror.h"
#include "mstring.h"

/**
 * Create a new string with a given capacity.
 *
 * \param   capacity    Capacity of the string.
 */
MangoString *mango_string_new(unsigned capacity)
{
    MangoString *mstr = (MangoString *)calloc(1, sizeof(MangoString));
    mstr->buffer = (char *)malloc(sizeof(char) * capacity);
    mstr->capacity = capacity;
    mstr->length = 0;
    return mstr;
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
 * Makes a copy of the string.
 *
 * \param   mstr    String to be copied.
 */
MangoString *mango_string_copy(const MangoString *mstr)
{
    if (mstr == NULL)
        return NULL;
    MangoString *newcopy = mango_string_new(mstr->length + 1);
    newcopy->length = mstr->length;
    memcpy(newcopy->buffer, mstr->buffer, mstr->length);
    newcopy->buffer[newcopy->length] = 0;
    return newcopy;
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
 *
 * \param   mstr    String to be appended.
 * \param   fmt     Format of the input.
 * \param   ...     Parameters to be appended.
 *
 * \returns Number of characters added.
 */
int mango_string_append_format(MangoString *mstr, const char *fmt, ...)
{
    return 0;
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


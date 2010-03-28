
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
}

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
void mango_string_free(MangoString *mstr)
{
}

/**
 * Clears the buffer.
 *
 * \param   mstr    String to be updated.
 */
void mango_string_clear(MangoString *mstr)
{
}

/**
 * Sets the buffer value.
 *
 * \param   mstr    String to be updated.
 */
void mango_string_set(MangoString *mstr, const char *value, size_t length)
{
}

/**
 * Appends a character.
 *
 * \param   mstr    String to be updated.
 * \param   chr     Character to be appended.
 */
void mango_string_append_char(MangoString *mstr, char ch)
{
}

/**
 * Appends a short value.
 *
 * \param   mstr    String to be updated.
 * \param   value   Character to be appended.
 */
void mango_string_append_short(MangoString *mstr, short value)
{
}

/**
 * Appends an int value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Short value to be appended.
 */
void mango_string_append_int(MangoString *mstr, int value)
{
}

/**
 * Appends long value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Long value to be appended.
 */
void mango_string_append_long(MangoString *mstr, long value)
{
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
}

/**
 * Ensures that the string has certain capacity.
 *
 * \param   mstr    String to be updated.
 * \param   newcap  New capacity to be made available in the string.
 */
void mango_string_ensure_capacity(MangoString *mstr, size_t newcap)
{
}


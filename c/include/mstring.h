
#ifndef __MANGO_STRING_H__
#define __MANGO_STRING_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoString
{
    //! Buffer that stores the data.
    char *      buffer;

    //! Buffer capacity.
    unsigned    capacity;

    //! Length of the contents.
    unsigned    length;
};

/**
 * Create a new string with a given capacity.
 *
 * \param   capacity    Capacity of the string.
 */
extern MangoString *mango_string_new(unsigned capacity);

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
extern void mango_string_free(MangoString *mstr);

/**
 * Clears the buffer.
 *
 * \param   mstr    String to be updated.
 */
extern void mango_string_clear(MangoString *mstr);

/**
 * Makes a copy of the string.
 *
 * \param   mstr    String to be copied.
 */
extern MangoString *mango_string_copy(MangoString *mstr);

/**
 * Sets the buffer value.
 *
 * \param   mstr    String to be updated.
 */
extern void mango_string_set(MangoString *mstr, const char *value, size_t length);

/**
 * Appends a value to the string buffer.
 *
 * \param   mstr    String to be updated.
 * \param   value   Value to be set to (not necessarily null terminated).
 * \param   length  Length of the input string.
 */
extern void mango_string_append(MangoString *mstr, const char *value, size_t length);

/**
 * Appends a character.
 *
 * \param   mstr    String to be updated.
 * \param   chr     Character to be appended.
 */
extern void mango_string_append_char(MangoString *mstr, char ch);

/**
 * Appends a short value.
 *
 * \param   mstr    String to be updated.
 * \param   value   Character to be appended.
 */
extern void mango_string_append_short(MangoString *mstr, short value);

/**
 * Appends an int value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Short value to be appended.
 */
extern void mango_string_append_int(MangoString *mstr, int value);

/**
 * Appends long value as binary.
 *
 * \param   mstr    String to be updated.
 * \param   value   Long value to be appended.
 */
extern void mango_string_append_long(MangoString *mstr, long value);

/**
 * Formatted appending of contents to the end of the string.
 *
 * \param   mstr    String to be appended.
 * \param   fmt     Format of the input.
 * \param   ...     Parameters to be appended.
 *
 * \returns Number of characters added.
 */
extern int mango_string_append_format(MangoString *mstr, const char *fmt, ...);

/**
 * Ensures that the string has certain capacity.
 *
 * \param   mstr    String to be updated.
 * \param   newcap  New capacity to be made available in the string.
 */
extern void mango_string_ensure_capacity(MangoString *mstr, size_t newcap);

#ifdef __cplusplus
}
#endif

#endif


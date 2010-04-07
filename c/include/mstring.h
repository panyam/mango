
#ifndef __MANGO_STRING_H__
#define __MANGO_STRING_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Immutable strings.
 */
struct MangoString
{
    /**
     * The Intern ID.
     */
    int                 internId;

    /**
     * The string table/pool to which the string belongs.
     * If this is a waste of space, we can remove this and make it the
     * caller's responsibility to ensure that the strings being compared
     * belong to the same string table.
     */
    MangoStringTable *  mstable;
};

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
extern MangoString *mango_string_new(const char *value,
                                     int length,
                                     MangoStringTable *mstable);

/**
 * Gets the buffer value of the string.
 */
extern const char *mango_string_value(const MangoString *mstr);

/**
 * Gets the length of the string.
 */
extern size_t mango_string_length(const MangoString *mstr);

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
extern void mango_string_free(MangoString *mstr);

/**
 * Compares the string contents with another buffer.
 *
 * \param   mstr    String being compared.
 * \param   value   String being compared to.
 * \param   length  Length of the string being compared to.
 *
 * \return -1 if mstr < value, 0 if equal else +1
 */
extern int mango_string_compare(const MangoString *mstr1, const MangoString *mstr2);

/**
 * Tells if two strings are equal.
 */
extern BOOL mango_strings_are_equal(const MangoString *mstr1, const MangoString *mstr2);

#ifdef __cplusplus
}
#endif

#endif


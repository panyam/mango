
#ifndef __MANGO_RCSTRING_H__
#define __MANGO_RCSTRING_H__

#include "mstring.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Immutable reference counted strings.
 */
INHERIT_STRUCT(MangoRCString, MangoString,
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
    MangoRCStringTable *  mstable;

    //! A reference to the string for easy checking
    const char *strPtr;
);

/**
 * Creates a mango RC string from a null terminated string in the default
 * string table.
 */
#define MRCSTR(x)   (MangoString *)mango_rcstring_new((x), -1, NULL)

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
extern MangoRCString *mango_rcstring_new(const char *value, int length,
                                         MangoRCStringTable *mstable);
                               

/**
 * Destroys a string.
 *
 * \param   mstr String to be destroyed.
 */
extern void mango_rcstring_dealloc(MangoRCString *mstr);

/**
 * Compares the string contents with another buffer.
 *
 * \param   mstr    String being compared.
 * \param   value   String being compared to.
 * \param   length  Length of the string being compared to.
 *
 * \return -1 if mstr < value, 0 if equal else +1
 */
extern int mango_rcstring_compare(const MangoRCString *mstr1,
                                  const MangoRCString *mstr2);

/**
 * Tells if two strings are equal.
 */
extern BOOL mango_rcstrings_are_equal(const MangoRCString *mstr1,
                                      const MangoRCString *mstr2);

/**
 * Gets the buffer value of the string.
 */
extern const char *mango_rcstring_buffer(const MangoRCString *mstr);

/**
 * Gets the length of the string.
 */
extern size_t mango_rcstring_length(const MangoRCString *mstr);

/**
 * Compares a string with the contents of a buffer.
 *
 * \param   str     String being compared.
 * \param   buff    Value being compared to.
 * \param   length  Length of the buffer.  If -ve, then buff is null terminated.
 *
 * \return  -ve if str < buff, 0 if they are equal, +ve otherwise
 */
extern int mango_rcstring_compare_to_buffer(const MangoRCString *str, const char *buffer, int length);

#ifdef __cplusplus
}
#endif

#endif


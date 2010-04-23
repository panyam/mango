
#ifndef __MANGO_STRING_H__
#define __MANGO_STRING_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * A string prototype is like a class for a string.
 * This contains the implementation specific function pointers to
 * manipulate and query strings.  This is stored outside the MangoString
 * because the pattern for using strings will be by copy/value so copying
 * MangoStrings should be quick and cheap.  This obviously comes at the
 * expense of an extra redirection (when accessing the prototype) but we
 * will let the compiler/OS worry about caching that.
 */
struct MangoStringPrototype
{
    /**
     * Base Prototype Class.
     */
    MangoPrototype __base__;

    /**
     * Gets the native string buffer.
     */
    const char *(*bufferFunc)(const void *data);

    /**
     * Gets the string size.
     */
    size_t (*sizeFunc)(const void *data);

    /**
     * Copies a string.
     */
    void (*copyFunc)(void *data, MangoString *another);
};

DECLARE_CLASS(MangoString, MangoObject,
    /**
     * Implementation specific string data.
     */
    void *data;
);

/**
 * Returns a copy of a string.
 * \param   mstr    String to be copied.
 * \return  The new copy of the string.
 */
extern MangoString *mango_string_copy(MangoString *mstr);

/**
 * Releases a string.
 *
 * \param   mstr String to be released.
 */
extern void mango_string_release(MangoString *mstr);

/**
 * Gets the buffer value of the string.
 */
extern const char *mango_string_buffer(const MangoString *mstr);

/**
 * Gets the length of the string.
 */
extern size_t mango_string_length(const MangoString *mstr);

/**
 * Tells if two strings are equal.
 *
 * \param   mstr1   String being compared.
 * \param   mstr2   String being compared to.
 *
 * \return true if strings are equal, false otherwise.
 */
extern BOOL mango_strings_are_equal(const MangoString *mstr1, const MangoString *mstr2);

#ifdef __cplusplus
}
#endif

#endif


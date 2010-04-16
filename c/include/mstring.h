
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
    MangoString (*copyFunc)(void *data);

    /**
     * Releases a string.
     */
    void (*releaseFunc)(void *data);

    /**
     * Tells if two strings are equal.
     */
    int (*equalsFunc)(const void *mstr1, const void *mstr2);

    /**
     * Compares two strings.
     */
    int (*compareFunc)(const void *mstr1, const void *mstr2);
};

/**
 * Generic string interface to allow different string implementations
 * across platforms (eg std::strings, NSString or just MangoString etc).
 */
struct MangoString
{
    /**
     * String prototype - contains the methods 
     * to manipulate and query the string in implementation specific ways.
     */
    MangoStringPrototype *prototype;

    /**
     * Implementation specific string data.
     */
    void *data;
};

/**
 * Creates a new string with its data and prototype.
 * \param   proto   Prototype for the string.
 * \param   data    Implementation specific data for the string.
 */
extern MangoString mango_string_new(MangoStringPrototype *proto, void *data);

/**
 * Copies another mango string.
 * \param   mstr    String to be copied.
 * \return  A new instance of the immutable string.
 */
extern MangoString mango_string_copy(MangoString *mstr);

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
 * Compares the string contents with another buffer.
 *
 * \param   mstr1   String being compared.
 * \param   mstr2   String being compared to.
 *
 * \return -1 if mstr < value, 0 if equal else +1
 */
extern int mango_string_compare(const MangoString *mstr1, const MangoString *mstr2);

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


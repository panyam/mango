
#ifndef __MANGO_STRING_H__
#define __MANGO_STRING_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef const char *(*StringBufferFunc)(const MangoString *str);
typedef size_t (*StringLengthFunc)(const MangoString *str);
typedef void (*StringCopyFunc)(const MangoString *str, MangoString *another);
typedef int (*StringCompareToBufferFunc)(const MangoString *str, const char *buffer, int length);

/**
 * A string prototype is like a class for a string.
 * This contains the implementation specific function pointers to
 * manipulate and query strings.  This is stored outside the MangoString
 * because the pattern for using strings will be by copy/value so copying
 * MangoStrings should be quick and cheap.  This obviously comes at the
 * expense of an extra redirection (when accessing the prototype) but we
 * will let the compiler/OS worry about caching that.
 */
INHERIT_STRUCT(MangoStringPrototype, MangoPrototype,
    /**
     * Gets the native string buffer.
     */
    const char *(*bufferFunc)(const MangoString *str);

    /**
     * Gets the string size.
     */
    size_t (*sizeFunc)(const MangoString *str);

    /**
     * Method to return the character at a given index.
     */
    int (*charAtFunc)(const MangoString *str, unsigned index);

    /**
     * Method to compare to a buffer.
     */
    int (*compareToBufferFunc)(const MangoString *str, const char *buffer, int length);
);

/**
 * Base class of all string implementations.
 */
DECLARE_CLASS(MangoString, MangoStringPrototype);

/**
 * Default string prototype.
 */
MangoStringPrototype *mango_string_prototype();

/**
 * Gets the buffer value of the string.
 */
extern const char *mango_string_buffer(const MangoString *mstr);

/**
 * Gets the length of the string.
 */
extern size_t mango_string_length(const MangoString *mstr);

/**
 * Compares a string with the contents of a buffer.
 *
 * \param   str     String being compared.
 * \param   buff    Value being compared to.
 * \param   length  Length of the buffer.  If -ve, then buff is null terminated.
 *
 * \return  -ve if str < buff, 0 if they are equal, +ve otherwise
 */
extern int mango_string_compare_to_buffer(const MangoString *str1, const char *buffer, int length);

#ifdef __cplusplus
}
#endif

#endif



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
DECLARE_PROTOTYPE(MangoStringPrototype, MangoPrototype,
    /**
     * Gets the native string buffer.
     */
    const char *(*bufferFunc)(const MangoString *str);

    /**
     * Gets the string size.
     */
    size_t (*sizeFunc)(const MangoString *str);

    /**
     * Copies a string.
     */
    void (*copyFunc)(const MangoString *str, MangoString *another);
);

/**
 * Base class of all string implementations.
 */
DECLARE_CLASS(MangoString, MangoStringPrototype);

/**
 * Returns a copy of a string.
 * \param   mstr    String to be copied.
 * \return  The new copy of the string.
 */
extern MangoString *mango_string_copy(MangoString *mstr);

/**
 * Gets the buffer value of the string.
 */
extern const char *mango_string_buffer(const MangoString *mstr);

/**
 * Gets the length of the string.
 */
extern size_t mango_string_length(const MangoString *mstr);

#ifdef __cplusplus
}
#endif

#endif


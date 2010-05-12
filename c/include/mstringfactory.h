
#ifndef __MANGO_STRING_FACTORY_H__
#define __MANGO_STRING_FACTORY_H__

#include "mstring.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef MangoString *(*MangoStringFactoryNewStringFunc)(MangoStringFactory *factory, const char *buffer, int length);
typedef MangoString *(*MangoStringFactoryFromBufferFunc)(MangoStringFactory *factory, const MangoStringBuffer *buffer);
typedef void (*MangoStringFactoryFreeStringFunc)(MangoStringFactory *factory, MangoString *str);

/**
 * A factory for creating strings.
 */
DECLARE_CLASS(MangoStringFactory, MangoPrototype,
    /**
     * Creates a new string.
     */
    MangoString *(*newStringFunc)(MangoStringFactory *factory, const char *buffer, int length);

    /**
     * Creates a new string from a string buffer.
     */
    MangoString *(*fromBufferFunc)(MangoStringFactory *factory, const MangoStringBuffer *buffer);

    /**
     * Frees a string created by the previous 2 functions.
     */
    void (*freeStringFunc)(MangoStringFactory *factory, MangoString *str);
);

/**
 * Frees a string factory.
 */
extern void mango_stringfactory_release(MangoStringFactory *factory);

/**
 * Creates a new string.
 */
extern MangoString *mango_stringfactory_new_string(MangoStringFactory *factory,
                                                   const char *buffer,
                                                   int length);

/**
 * Creates a new string from a buffer.
 */
extern MangoString *mango_stringfactory_from_buffer(MangoStringFactory *factory,
                                                    const MangoStringBuffer *buffer);

/**
 * Frees a previously created string.
 */
extern void mango_stringfactory_free_string(MangoStringFactory *factory, MangoString *str);

#ifdef __cplusplus
}
#endif

#endif


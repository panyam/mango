
#ifndef __MANGO_STRING_FACTORY_H__
#define __MANGO_STRING_FACTORY_H__

#include "mstring.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef MangoString *(*MangoStringFactoryNewStringFunc)(MangoStringFactory *factory, const char *buffer, int length);
typedef MangoString *(*MangoStringFactoryFromBufferFunc)(MangoStringFactory *factory, const MangoStringBuffer *buffer);
typedef void (*MangoStringFactoryFreeStringFunc)(MangoStringFactory *factory, MangoString *str);

INHERIT_STRUCT(MangoStringFactoryPrototype, MangoPrototype,
    /**
     * Creates a new string.
     */
    MangoString *(*newStringFunc)(MangoStringFactory *factory, const char *buffer, int length);

    /**
     * Creates a new string from a string buffer.
     */
    MangoString *(*fromBufferFunc)(MangoStringFactory *factory, const MangoStringBuffer *buffer);
);

/**
 * A factory for creating strings.
 */
DECLARE_CLASS(MangoStringFactory, MangoStringFactoryPrototype);

/**
 * Default string factory prototype.
 */
extern MangoStringFactoryPrototype *mango_stringfactory_prototype();

/**
 * String factory's dealloc method called when refcount reaches 0.
 */
extern void mango_stringfactory_dealloc(MangoStringFactory *factory);

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

#ifdef __cplusplus
}
#endif

#endif


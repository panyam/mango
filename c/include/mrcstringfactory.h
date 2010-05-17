
#ifndef __MANGO_RCSTRING_FACTORY_H__
#define __MANGO_RCSTRING_FACTORY_H__

#include "mstringfactory.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoRCStringFactory, MangoStringFactory,
    MangoRCStringTable *mrcstable;
);

/**
 * Creates a new immutale string factory.
 * \return  A new instance of the immutable string.
 */
extern MangoRCStringFactory *mango_rcstringfactory_new();

/**
 * Initialises the string factory.
 */
extern MangoRCStringFactory *mango_rcstringfactory_init(MangoRCStringFactory *rcsfactory);

/**
 * Creates a new string.
 */
extern MangoString *mango_rcstringfactory_new_string(MangoRCStringFactory *mrcsfactory,
                                                     const char *buffer,
                                                     int length);

/**
 * Creates a new string from a string buffer.
 */
extern MangoString *mango_rcstringfactory_from_buffer(MangoRCStringFactory *mrcsfactory,
                                                      const MangoStringBuffer *buffer);

/**
 * Frees a string.
 */
extern void mango_rcstringfactory_free_string(MangoRCStringFactory *factory,
                                              MangoRCString *string);

/**
 * String factory's dealloc method called when refcount reaches 0.
 */
extern void mango_rcstringfactory_dealloc(MangoRCStringFactory *factory);

#ifdef __cplusplus
}
#endif

#endif


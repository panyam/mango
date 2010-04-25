
#ifndef __MANGO_RCSTRING_FACTORY_H__
#define __MANGO_RCSTRING_FACTORY_H__

#include "mstringfactory.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_CLASS(MangoRCStringFactory, MangoStringFactory,
    MangoRCStringTable *mrcstable;
    );

/**
 * Creates a new immutale string factory.
 * \return  A new instance of the immutable string.
 */
extern MangoStringFactory *mango_rcstringfactory_new();

/**
 * Creates a new string.
 */
extern MangoString *mango_rcstringfactory_new_string(MangoRCStringTable *mstable,
                                                     const char *buffer,
                                                     int length);

/**
 * Creates a new string from a string buffer.
 */
extern MangoString *mango_rcstringfactory_from_buffer(MangoRCStringTable *mstable,
                                                      const MangoStringBuffer *buffer);

/**
 * Frees a string.
 */
extern void mango_rcstringfactory_free_string(MangoRCStringFactory *factory,
                                              MangoRCString *string);

#ifdef __cplusplus
}
#endif

#endif


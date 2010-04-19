
#ifndef __MANGO_STRING_FACTORY_H__
#define __MANGO_STRING_FACTORY_H__

#include "mstring.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * A factory for creating strings.
 */
struct MangoStringFactory
{
    /**
     * Factory data.
     */
    void *data;

    /**
     * Function to cleanup the factory data.
     */
    void (*cleanupFunc)(void *factory_data);

    /**
     * Creates a new string.
     */
    MangoString *(*newStringFunc)(void *factory_data, const char *buffer, int length);

    /**
     * Creates a new string from a string buffer.
     */
    MangoString *(*fromBufferFunc)(void *factory_data, const MangoStringBuffer *buffer);
};

/**
 * Cleans up the string factory.
 */
extern void mango_stringfactory_cleanup(MangoStringFactory *factory);

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
 * Frees a string.
 */
extern void mango_stringfactory_free_string(MangoStringFactory *factory, MangoString *str);

#ifdef __cplusplus
}
#endif

#endif


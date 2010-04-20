
#include "mstringfactory.h"

/**
 * Frees a string factory.
 */
void mango_stringfactory_free(MangoStringFactory *factory)
{
    factory->cleanupFunc(factory->data);
    free(factory);
}

/**
 * Creates a new string.
 */
MangoString *mango_stringfactory_new_string(MangoStringFactory *factory,
                                            const char *buffer,
                                            int length)
{
    return factory->newStringFunc(factory->data, buffer, length);
}


/**
 * Creates a new string from a buffer.
 */
MangoString *mango_stringfactory_from_buffer(MangoStringFactory *factory,
                                             const MangoStringBuffer *buffer)
{
    return factory->fromBufferFunc(factory->data, buffer);
}

/**
 * Frees a string.
 */
void mango_stringfactory_free_string(MangoStringFactory *factory, MangoString *str)
{
    str->prototype->releaseFunc(str->data);
    free(str);
}



#include "mstringfactory.h"

/**
 * Creates a new string.
 */
MangoString *mango_stringfactory_new_string(MangoStringFactory *factory,
                                            const char *buffer,
                                            int length)
{
    return factory->newStringFunc(factory, buffer, length);
}


/**
 * Creates a new string from a buffer.
 */
MangoString *mango_stringfactory_from_buffer(MangoStringFactory *factory,
                                             const MangoStringBuffer *buffer)
{
    return factory->fromBufferFunc(factory, buffer);
}

/**
 * Frees a previously created string.
 */
void mango_stringfactory_free_string(MangoStringFactory *factory, MangoString *str)
{
    if (factory->freeStringFunc != NULL)
        factory->freeStringFunc(factory, str);
}


/**
 * Frees a string factory.
 */
void mango_stringfactory_release(MangoStringFactory *factory)
{
    mango_object_release((MangoObject *)factory);
}


#include "mstringfactory.h"

/**
 * Creates a new string.
 */
MangoString *mango_stringfactory_new_string(MangoStringFactory *factory,
                                            const char *buffer,
                                            int length)
{
    return factory->__prototype__->newStringFunc(factory, buffer, length);
}


/**
 * Creates a new string from a buffer.
 */
MangoString *mango_stringfactory_from_buffer(MangoStringFactory *factory,
                                             const MangoStringBuffer *buffer)
{
    return factory->__prototype__->fromBufferFunc(factory, buffer);
}

/**
 * Frees a previously created string.
 */
void mango_stringfactory_free_string(MangoStringFactory *factory, MangoString *str)
{
    if (factory->__prototype__->freeStringFunc != NULL)
        factory->__prototype__->freeStringFunc(factory, str);
}

/**
 * String factory's dealloc method called when refcount reaches 0.
 */
void mango_stringfactory_dealloc(MangoStringFactory *factory)
{
    mango_object_dealloc((MangoObject *)factory);
}


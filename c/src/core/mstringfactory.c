
#include "mangopub.h"

/**
 * Default string factory prototype.
 */
DECLARE_PROTO_FUNC(mango_stringfactory_prototype, MangoStringFactoryPrototype, NULL);

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
 * String factory's dealloc method called when refcount reaches 0.
 */
void mango_stringfactory_dealloc(MangoStringFactory *factory)
{
    mango_object_dealloc((MangoObject *)factory);
}


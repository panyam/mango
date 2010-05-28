
#include "mangopub.h"

DECLARE_PROTO_FUNC("RCStringFactory", MangoStringFactoryPrototype, mango_rcstringfactory_prototype,
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_rcstringfactory_dealloc;
    __proto__.newStringFunc    = (MangoStringFactoryNewStringFunc)mango_rcstringfactory_new_string;
    __proto__.fromBufferFunc   = (MangoStringFactoryFromBufferFunc)mango_rcstringfactory_from_buffer;
);

/**
 * Creates a new immutale string factory.
 * \return  A new instance of the immutable string.
 */
MangoRCStringFactory *mango_rcstringfactory_new()
{
    MangoRCStringFactory *msfactory = NEW(MangoRCStringFactory);
    return mango_rcstringfactory_init(msfactory);
}

/**
 * Initialises the string factory.
 */
MangoRCStringFactory *mango_rcstringfactory_init(MangoRCStringFactory *rcsfactory)
{
    OBJ_INIT(rcsfactory, mango_rcstringfactory_prototype());
    rcsfactory->mrcstable    = mango_rcstring_table_new();
    return rcsfactory;
}

/**
 * Creates a new string.
 */
MangoString *mango_rcstringfactory_new_string(MangoRCStringFactory *mrcsfactory,
                                              const char *buffer, int length)
{
    return mango_rcstring_new(buffer, length, mrcsfactory->mrcstable);
}

/**
 * Creates a new string from a string buffer.
 */
MangoString *mango_rcstringfactory_from_buffer(MangoRCStringFactory *mrcsfactory,
                                               const MangoStringBuffer *buffer)
{
    return mango_rcstring_new(buffer->buffer, buffer->length, mrcsfactory->mrcstable);
}

/**
 * String factory's dealloc method called when refcount reaches 0.
 */
void mango_rcstringfactory_dealloc(MangoRCStringFactory *factory)
{
    mango_rcstring_table_free(factory->mrcstable);
    mango_stringfactory_dealloc((MangoStringFactory *)factory);
}


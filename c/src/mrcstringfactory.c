
#include "merror.h"
#include "mstringbuffer.h"
#include "mrcstring.h"
#include "mrcstringfactory.h"
#include "mrcstringtable.h"
#include "mmemutils.h"

DECLARE_PROTO_FUNC("RCStringFactory", MangoStringFactoryPrototype, mango_rcstringfactory_prototype,
    ((MangoPrototype *)&__proto__)->deallocFunc = (PrototypeDeallocFunc)mango_rcstringfactory_dealloc;
    __proto__.newStringFunc    = (MangoStringFactoryNewStringFunc)mango_rcstringfactory_new_string;
    __proto__.fromBufferFunc   = (MangoStringFactoryFromBufferFunc)mango_rcstringfactory_from_buffer;
    __proto__.freeStringFunc   = (MangoStringFactoryFreeStringFunc)mango_rcstringfactory_free_string;
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
 * Frees a string.
 */
void mango_rcstringfactory_free_string(MangoRCStringFactory *factory, MangoRCString *string)
{
}

/**
 * String factory's dealloc method called when refcount reaches 0.
 */
void mango_rcstringfactory_dealloc(MangoRCStringFactory *factory)
{
    mango_stringfactory_dealloc((MangoStringFactory *)factory);
}



#include "merror.h"
#include "mstringbuffer.h"
#include "mrcstring.h"
#include "mrcstringfactory.h"
#include "mrcstringtable.h"
#include "mmemutils.h"

MangoStringFactoryPrototype *mango_rcstringfactory_prototype()
{
    DECLARE_PROTO_VARIABLE("RCStringFactory", MangoStringFactoryPrototype, rcsfactoryProto,
        rcsfactoryProto.newStringFunc    = (MangoStringFactoryNewStringFunc)mango_rcstringfactory_new_string;
        rcsfactoryProto.fromBufferFunc   = (MangoStringFactoryFromBufferFunc)mango_rcstringfactory_from_buffer;
        rcsfactoryProto.freeStringFunc   = (MangoStringFactoryFreeStringFunc)mango_rcstringfactory_free_string;
        ((MangoPrototype *)&rcsfactoryProto)->deallocFunc = (PrototypeDeallocFunc)mango_rcstringfactory_dealloc;
    );
}

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
    msfactory->mrcstable    = mango_rcstring_table_new();
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


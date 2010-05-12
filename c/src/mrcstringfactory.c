
#include "merror.h"
#include "mstringbuffer.h"
#include "mrcstring.h"
#include "mrcstringfactory.h"
#include "mrcstringtable.h"
#include "mmemutils.h"

MangoPrototype *mango_rcstringfactory_prototype()
{
    static MangoPrototype *MRCSFACTORY_PROTOTYPE = NULL;
    if (MRCSFACTORY_PROTOTYPE == NULL)
    {
        MRCSFACTORY_PROTOTYPE = ZNEW(MangoPrototype);
    }
    return MRCSFACTORY_PROTOTYPE;
}

/**
 * Creates a new immutale string factory.
 * \return  A new instance of the immutable string.
 */
MangoStringFactory *mango_rcstringfactory_new()
{
    MangoRCStringFactory *msfactory = ZNEW(MangoRCStringFactory);
    msfactory->mrcstable            = mango_rcstring_table_new();
    ((MangoStringFactory *)msfactory)->__prototype__    = mango_rcstringfactory_prototype();
    ((MangoStringFactory *)msfactory)->newStringFunc    = (MangoStringFactoryNewStringFunc)mango_rcstringfactory_new_string;
    ((MangoStringFactory *)msfactory)->fromBufferFunc   = (MangoStringFactoryFromBufferFunc)mango_rcstringfactory_from_buffer;
    ((MangoStringFactory *)msfactory)->freeStringFunc   = (MangoStringFactoryFreeStringFunc)mango_rcstringfactory_free_string;
    return ((MangoStringFactory *)msfactory);
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



#include "merror.h"
#include "mstringbuffer.h"
#include "mrcstring.h"
#include "mrcstringfactory.h"
#include "mrcstringtable.h"
#include "mmemutils.h"

/**
 * Creates a new immutale string factory.
 * \return  A new instance of the immutable string.
 */
MangoStringFactory *mango_rcstringfactory_new()
{
    MangoRCStringFactory *msfactory = ZNEW(MangoRCStringFactory);
    msfactory->mrcstable            = mango_rcstring_table_new();
    ((MangoStringFactory *)msfactory)->__prototype__->cleanUpFunc   = mango_rcstring_table_free;
    ((MangoStringFactory *)msfactory)->newStringFunc                = mango_rcstringfactory_new_string;
    ((MangoStringFactory *)msfactory)->fromBufferFunc               = mango_rcstringfactory_from_buffer;
    ((MangoStringFactory *)msfactory)->freeStringFunc               = mango_rcstringfactory_free_string;
    return ((MangoStringFactory *)msfactory);
}

/**
 * Creates a new string.
 */
MangoString *mango_rcstringfactory_new_string(MangoRCStringTable *mstable,
                                              const char *buffer, int length)
{
    return mango_rcstring_new(buffer, length, mstable);
}

/**
 * Creates a new string from a string buffer.
 */
MangoString *mango_rcstringfactory_from_buffer(MangoRCStringTable *mstable,
                                               const MangoStringBuffer *buffer)
{
    return mango_rcstring_new(buffer->buffer, buffer->length, mstable);
}

/**
 * Frees a string.
 */
void mango_rcstringfactory_free_string(MangoRCStringFactory *factory, MangoRCString *string)
{
}


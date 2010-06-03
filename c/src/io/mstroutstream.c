
#include "mangopub.h"

void mango_stroutstream_dealloc(MangoStrOutStream *outstream);
int mango_stroutstream_write(MangoStrOutStream *outstream, void *buffer, size_t length);

DECLARE_PROTO_FUNC(mango_stroutstream_prototype, MangoOutStreamPrototype, MangoStrOutStreamPrototype, 
    mango_outstream_prototype_init((MangoOutStreamPrototype *)&__proto__);
    ((MangoPrototype *)&__proto__)->deallocFunc = (ObjectDeallocFunc)mango_stroutstream_dealloc;
    __proto__.writeFunc = (StreamWriteFunc)mango_stroutstream_write;
);

/**
 * Create a new string output stream.
 */
MangoStrOutStream *mango_stroutstream_new()
{
    return mango_stroutstream_init(ZNEW(MangoStrOutStream), NULL);
}


/**
 * Initialise a string output stream.
 */
MangoStrOutStream *mango_stroutstream_init(MangoStrOutStream *outstream, MangoOutStreamPrototype *proto)
{
    if (proto == NULL)
        proto = mango_stroutstream_prototype();
    OBJ_INIT(outstream, proto);
    outstream->strbuff = NULL;
    return outstream;
}

/**
 * Writes data to the str output stream.
 */
int mango_stroutstream_write(MangoStrOutStream *outstream, void *buffer, size_t length)
{
    if (outstream->strbuff == NULL)
    {
        outstream->strbuff = mango_stringbuffer_with_capacity(32);
    }
    mango_stringbuffer_append(outstream->strbuff, buffer, length);
    return length;
}

/**
 * Deallocs a str out stream when its refcount reaches 0.
 */
void mango_stroutstream_dealloc(MangoStrOutStream *outstream)
{
    if (outstream->strbuff != NULL)
    {
        mango_stringbuffer_free(outstream->strbuff);
        outstream->strbuff = NULL;
    }
    mango_object_dealloc(OBJ(outstream));
}


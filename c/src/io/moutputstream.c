
#include "moutputstream.h"

DECLARE_PROTO_FUNC("OutStream", MangoOutStreamPrototype, mango_outstream_prototype,
    __proto__.writeFunc = NULL;
    __proto__.writeFormatFunc = NULL;
);

DECLARE_CLASS(MangoOutStream, MangoOutStreamPrototype);

/**
 * Initialises the output stream prototype.
 */
MangoOutStreamPrototype *mango_outstream_prototype_init(const char *name);


/**
 * Write data to an output stream.
 */
int mango_outstream_write(MangoOutStream *outstream, void *data, size_t length)
{
    if (outstream->__prototype__.writeFunc != NULL)
    {
        return outstream->__prototype__.writeFunc(outstream, data, length);
    }
    return -1;
}

/**
 * Write formatted string to an output stream.
 */
int mango_outstream_writef(MangoOutStream *outstream, const char *format, ...)
{
    const size_t MAX_MESSAGE_SIZE = 512;
    if (error != NULL)
    {
        if (*error == NULL)
        {
            *error = (MangoError *)calloc(1, sizeof(MangoError));
        }
        va_list ap;
        va_start(ap, format);
        char buffer[MAX_MESSAGE_SIZE];
        int result = vsnprintf(buffer, MAX_MESSAGE_SIZE, format, ap);
        va_end(ap);
        return mango_outstream_write(outstream, buffer, result);
    }
    return 0;
}


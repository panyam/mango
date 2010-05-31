
#ifndef __MANGO_OUTPUT_STREAM_H__
#define __MANGO_OUTPUT_STREAM_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoOutStreamPrototype, MangoPrototype,
    /**
     * Write data to the stream.
     */
    int (*writeFunc)(MangoOutStream *outstream, void *buffer, size_t length);

    /**
     * Write formatted string to the stream.
     */
    int (*writeFormatFunc)(MangoOutStream *outstream, const char *format, ...);
);

DECLARE_CLASS(MangoOutStream, MangoOutStreamPrototype);

/**
 * Initialises the output stream prototype.
 */
MangoOutStreamPrototype *mango_outstream_prototype_init(const char *name);

/**
 * Write data to an output stream.
 */
int mango_outstream_write(MangoOutStream *outstream, void *data, size_t length);

/**
 * Write formatted string to an output stream.
 */
int mango_outstream_writef(MangoOutStream *outstream, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif


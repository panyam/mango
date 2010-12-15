
#ifndef __MANGO_STRING_OUTPUT_STREAM_H__ 
#define __MANGO_STRING_OUTPUT_STREAM_H__

#include "moutstream.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Output stream that writes to a string.
 */
DECLARE_CLASS(MangoStrOutStream, MangoOutStreamPrototype,
    MangoStringBuffer   *strbuff;
);

/**
 * Initialises the output stream prototype.
 */
MangoOutStreamPrototype *mango_stroutstream_prototype();

/**
 * Write data to an output stream.
 */
int mango_outstream_write(MangoOutStream *outstream, void *data, size_t length);

/**
 * Write formatted string to an output stream.
 */
int mango_outstream_writef(MangoOutStream *outstream, const char *format, ...);

/**
 * Create a new string output stream.
 */
extern MangoStrOutStream *mango_stroutstream_new();

/**
 * Initialise a string output stream.
 */
extern MangoStrOutStream *mango_stroutstream_init(MangoStrOutStream *outstream, MangoOutStreamPrototype *proto);

#ifdef __cplusplus
}
#endif

#endif


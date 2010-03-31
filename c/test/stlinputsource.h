
#ifndef __STL_INPUT_SOURCE_H__
#define __STL_INPUT_SOURCE_H__

#include "mangopub.h"
#include <istream>

#ifdef __cplusplus
extern "C" {
#endif

struct StlInputSource
{
    MangoInputSource    sourceBase;     // el cheapo inheritance
    std::istream *      inputStream;
};

/**
 * Initialises an stl input source with an std istream.
 */
extern StlInputSource *new_stl_input_source(std::istream *instream = NULL);

/**
 * Frees the input source.
 * The istream object is NOT deleted.  It must be deleted prior to calling
 * this method.
 */
extern void free_stl_input_source(StlInputSource *source);

#ifdef __cplusplus
}
#endif

#endif


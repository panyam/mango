
#ifndef __STL_INPUT_SOURCE_H__
#define __STL_INPUT_SOURCE_H__

#include "minputsource.h"
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
void init_stl_input_source(StlInputSource *source, std::istream *instream);

#ifdef __cplusplus
}
#endif

#endif


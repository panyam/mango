
#ifndef __MANGO_INPUT_SOURCE_H__
#define __MANGO_INPUT_SOURCE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoInputSource
{
    /**
     * Gets the next character in the stream.  -ve if none exist.
     */
    int (*nextChar)(MangoInputSource *inputSource);
};

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_INPUT_STREAM_H__
#define __MANGO_INPUT_STREAM_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoInputStream
{
    BOOL (*hasBytesAvailable)(MangoInputStream *inputStream);
    int (*read)(MangoInputStream *inputStream, char *buffer, size_t numToRead);
};

#ifdef __cplusplus
}
#endif

#endif


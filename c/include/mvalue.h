
#ifndef __MANGO_VALUE_H__
#define __MANGO_VALUE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generic value objects.
 */
struct MangoValue
{
    int valueType;
    union
    {
        int             intValue;
        double          doubleValue;
        MangoString *   stringValue;
    } valueData;
};


#ifdef __cplusplus
}
#endif

#endif


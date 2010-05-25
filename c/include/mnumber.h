
#ifndef __MANGO_NUMBER_H__
#define __MANGO_NUMBER_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoNumber, MangoObject,
    int numType
    union
    {
        BOOL                boolValue;
        char                charValue;
        unsigned char       ucharValue;
        short               shortValue;
        unsigned short      ushortValue;
        int                 intValue;
        unsigned int        uintValue;
        long                longValue;
        unsigned long       ulongValue;
        long long           longlongValue;
        unsigned long long  ulonglongValue;
        float               floatValue;
        double              doubleValue;
    } numValue;
);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_NUMBER_H__
#define __MANGO_NUMBER_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MV_BOOL,
    MV_CHAR,
    MV_UCHAR,
    MV_SHORT,
    MV_USHORT,
    MV_INT,
    MV_UINT,
    MV_LONG,
    MV_ULONG,
    MV_LONGLONG,
    MV_ULONGLONG,
    MV_FLOAT,
    MV_DOUBLE,
} MangoNumberType;

INHERIT_STRUCT(MangoNumber, MangoObject,
    MangoNumberType numType;
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

/**
 * Creates a number from an bool value.
 */
extern MangoNumber *mango_number_from_bool(BOOL value);

/**
 * Creates a number from an char value.
 */
extern MangoNumber *mango_number_from_char(char value);

/**
 * Creates a number from an uchar value.
 */
extern MangoNumber *mango_number_from_uchar(unsigned char value);

/**
 * Creates a number from an short value.
 */
extern MangoNumber *mango_number_from_short(short value);

/**
 * Creates a number from an ushort value.
 */
extern MangoNumber *mango_number_from_ushort(unsigned short value);

/**
 * Creates a number from an int value.
 */
extern MangoNumber *mango_number_from_int(int value);

/**
 * Creates a number from an uint value.
 */
extern MangoNumber *mango_number_from_uint(unsigned int value);

/**
 * Creates a number from an long value.
 */
extern MangoNumber *mango_number_from_long(long value);

/**
 * Creates a number from an ulong value.
 */
extern MangoNumber *mango_number_from_ulong(unsigned long value);

/**
 * Creates a number from an long long value.
 */
extern MangoNumber *mango_number_from_longlong(long long value);

/**
 * Creates a number from an unsigned long long value.
 */
extern MangoNumber *mango_number_from_ulonglong(unsigned long long value);

/**
 * Creates a number from an float value.
 */
extern MangoNumber *mango_number_from_float(float value);

/**
 * Creates a number from an double value.
 */
extern MangoNumber *mango_number_from_double(double value);

/**
 * Tells if two numbers are equal.
 */
extern BOOL mango_numbers_are_equal(const MangoNumber *num1, const MangoNumber *num2);

/**
 * Compares two numbers.
 */
extern int mango_number_compare(const MangoNumber *num1, const MangoNumber *num2);

#ifdef __cplusplus
}
#endif

#endif


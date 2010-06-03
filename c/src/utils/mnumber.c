#include "mangopub.h"


DECLARE_PROTO_FUNC(mango_number_prototype, MangoPrototype, MangoNumberPrototype, 
    ((MangoPrototype *)&__proto__)->equalsFunc  = (ObjectEqualsFunc)mango_numbers_are_equal;
    ((MangoPrototype *)&__proto__)->compareFunc = (ObjectCompareFunc)mango_number_compare;
);

/**
 * Tells if two numbers are equal.
 */
BOOL mango_numbers_are_equal(const MangoNumber *num1, const MangoNumber *num2)
{
    if (num1->numType == num2->numType)
    {
        switch (num1->numType)
        {
            case MV_BOOL: return num1->numValue.boolValue == num2->numValue.boolValue;
            case MV_CHAR: return num1->numValue.charValue == num2->numValue.charValue;
            case MV_UCHAR: return num1->numValue.ucharValue == num2->numValue.ucharValue;
            case MV_SHORT: return num1->numValue.shortValue == num2->numValue.shortValue;
            case MV_USHORT: return num1->numValue.ushortValue == num2->numValue.ushortValue;
            case MV_INT: return num1->numValue.intValue == num2->numValue.intValue;
            case MV_UINT: return num1->numValue.uintValue == num2->numValue.uintValue;
            case MV_LONG: return num1->numValue.longValue == num2->numValue.longValue;
            case MV_ULONG: return num1->numValue.ulongValue == num2->numValue.ulongValue;
            case MV_LONGLONG: return num1->numValue.longlongValue == num2->numValue.longlongValue;
            case MV_ULONGLONG: return num1->numValue.ulonglongValue == num2->numValue.ulonglongValue;
            case MV_FLOAT: return num1->numValue.floatValue == num2->numValue.floatValue;
            case MV_DOUBLE: return num1->numValue.doubleValue == num2->numValue.doubleValue;
        }
    }
    return false;
}

/**
 * Compares two numbers.
 */
int mango_number_compare(const MangoNumber *num1, const MangoNumber *num2)
{
    if (num1->numType == num2->numType)
    {
        switch (num1->numType)
        {
            case MV_BOOL: return num1->numValue.boolValue - num2->numValue.boolValue;
            case MV_CHAR: return num1->numValue.charValue - num2->numValue.charValue;
            case MV_UCHAR: return num1->numValue.ucharValue - num2->numValue.ucharValue;
            case MV_SHORT: return num1->numValue.shortValue - num2->numValue.shortValue;
            case MV_USHORT: return num1->numValue.ushortValue - num2->numValue.ushortValue;
            case MV_INT: return num1->numValue.intValue - num2->numValue.intValue;
            case MV_UINT: return num1->numValue.uintValue - num2->numValue.uintValue;
            case MV_LONG: return num1->numValue.longValue - num2->numValue.longValue;
            case MV_ULONG: return num1->numValue.ulongValue - num2->numValue.ulongValue;
            case MV_LONGLONG: return num1->numValue.longlongValue - num2->numValue.longlongValue;
            case MV_ULONGLONG: return num1->numValue.ulonglongValue - num2->numValue.ulonglongValue;
            case MV_FLOAT: return num1->numValue.floatValue - num2->numValue.floatValue;
            case MV_DOUBLE: return num1->numValue.doubleValue - num2->numValue.doubleValue;
        }
    }
    return num1->numType - num2->numType;
}

/**
 * Creates a number from an bool value.
 */
MangoNumber *mango_number_from_bool(BOOL value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_BOOL;
    number->numValue.boolValue = value;
    return number;
}

/**
 * Creates a number from an char value.
 */
MangoNumber *mango_number_from_char(char value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_CHAR;
    number->numValue.charValue = value;
    return number;
}

/**
 * Creates a number from an uchar value.
 */
MangoNumber *mango_number_from_uchar(unsigned char value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_UCHAR;
    number->numValue.ucharValue = value;
    return number;
}

/**
 * Creates a number from an short value.
 */
MangoNumber *mango_number_from_short(short value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_SHORT;
    number->numValue.shortValue = value;
    return number;
}

/**
 * Creates a number from an ushort value.
 */
MangoNumber *mango_number_from_ushort(unsigned short value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_USHORT;
    number->numValue.ushortValue = value;
    return number;
}

/**
 * Creates a number from an int value.
 */
MangoNumber *mango_number_from_int(int value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_INT;
    number->numValue.intValue = value;
    return number;
}

/**
 * Creates a number from an uint value.
 */
MangoNumber *mango_number_from_uint(unsigned int value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_UINT;
    number->numValue.uintValue = value;
    return number;
}

/**
 * Creates a number from an long value.
 */
MangoNumber *mango_number_from_long(long value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_LONG;
    number->numValue.longValue = value;
    return number;
}

/**
 * Creates a number from an ulong value.
 */
MangoNumber *mango_number_from_ulong(unsigned long value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_ULONG;
    number->numValue.ulongValue = value;
    return number;
}

/**
 * Creates a number from an long long value.
 */
MangoNumber *mango_number_from_longlong(long long value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_LONGLONG;
    number->numValue.longlongValue = value;
    return number;
}

/**
 * Creates a number from an unsigned long long value.
 */
MangoNumber *mango_number_from_ulonglong(unsigned long long value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_ULONGLONG;
    number->numValue.ulonglongValue = value;
    return number;
}

/**
 * Creates a number from an float value.
 */
MangoNumber *mango_number_from_float(float value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_FLOAT;
    number->numValue.floatValue = value;
    return number;
}

/**
 * Creates a number from an double value.
 */
MangoNumber *mango_number_from_double(double value)
{
    MangoNumber *number = OBJ_ALLOC(MangoNumber, mango_number_prototype());
    number->numType = MV_DOUBLE;
    number->numValue.doubleValue = value;
    return number;
}


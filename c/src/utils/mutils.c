
#include "mangopub.h"

/**
 * Tells if a string is an integer optionally converting it to an integer.
 */
BOOL is_integer(const char *buffer, int length, int *value)
{
    if (length < 0)
        length = strlen(buffer);

    int intValue = 0;
    for (int i = 0;i < length;i++)
    {
        if (!isdigit(buffer[i]))
            return false;
        intValue = (intValue * 10) + (buffer[i] - '0');
    }
    if (value != NULL)
        *value = intValue;
    return true;
}

/**
 * Casts a void* to an object.
 */
inline MangoObject *OBJ(void *obj) { return (MangoObject *)obj; }

/**
 * Initialises a mango object's refcount and prototype.
 */
inline MangoObject *OBJ_INIT(void *obj, void *proto) { return mango_object_init(OBJ(obj), (MangoPrototype *)proto); }

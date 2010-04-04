
#include <string.h>
#include "mutils.h"

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

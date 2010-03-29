
#define _GNU_SOURCE
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "merror.h"

/**
 * Creates a new error message.
 *
 * \param   code    Code of the error.
 * \param   msg     Message.
 *
 * \returns A MangoError instance that must be freed with mango_error_free.
 */
MangoError *mango_error_new(int code, const char *msg)
{
    MangoError *merror = (MangoError *)calloc(1, sizeof(MangoError));
    mango_error_set(&merror, code, msg);
    return merror;
}

/**
 * Destroys a mango error.
 */
void mango_error_free(MangoError *merror)
{
    if (merror != NULL)
    {
        if (merror->errorMessage != NULL)
            free(merror->errorMessage);
        free(merror);
    }
}

/**
 * Sets the message in an error if it is not null.
 */
int mango_error_set(MangoError **error, int code, const char *format, ...)
{
    const size_t MAX_MESSAGE_SIZE = 256;
    if (error != NULL)
    {
        if (*error == NULL)
        {
            *error = (MangoError *)calloc(1, sizeof(MangoError));
        }
        va_list ap;
        va_start(ap, format);
        char buffer[MAX_MESSAGE_SIZE];
        int result = vsnprintf(buffer, MAX_MESSAGE_SIZE, format, ap);
        va_end(ap);
        (*error)->errorMessage = strdup(buffer);
        return result;
    }
    return 0;
}


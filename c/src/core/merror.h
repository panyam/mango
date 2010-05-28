
#ifndef __MANGO_ERROR_H__
#define __MANGO_ERROR_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A mango error object.
 */
struct MangoError
{
    int     errorCode;
    char *  errorMessage;
};

/**
 * Creates a new error message.
 *
 * \param   code    Code of the error.
 * \param   msg     Message.
 *
 * \returns A MangoError instance that must be freed with mango_error_free.
 */
extern MangoError *mango_error_new(int code, const char *msg);

/**
 * Destroys a mango error.
 */
extern void mango_error_free(MangoError *merror);

/**
 * Sets the message in an error if it is not null.
 */
extern int mango_error_set(MangoError **error, int code, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif


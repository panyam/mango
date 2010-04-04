
#ifndef __MANGO_UTILS_H__
#define __MANGO_UTILS_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Tells if a string is an integer, optionally returning the integer value
 * if it is an integer.
 *
 * \param   buffer      The buffer that is being checked.
 * \param   length      Length of the buffer (if -ve, then it is a null
 *                      terminated string).
 * \param   outValue    Stores the int value (if not NULL).
 *
 * \return  true if the value is an integer, false otherwise.  If value is
 * an integer and outValue is non-null then the int value is stored in
 * outValue.
 */
extern BOOL is_integer(const char *buffer, int length, int *outValue);

#ifdef __cplusplus
}
#endif

#endif




#ifndef __MANGO_STRING2_H__
#define __MANGO_STRING2_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_CLASS(MangoString2,
    //! Buffer that stores the data.
    char *      buffer;

    //! Buffer capacity.
    unsigned    capacity;

    //! Length of the contents.
    unsigned    length;
);

/**
 * Tells if two strings are equal.
 */
extern BOOL mango_strings_are_equal(const MangoString *mstr1, const MangoString *mstr2);

#ifdef __cplusplus
}
#endif

#endif


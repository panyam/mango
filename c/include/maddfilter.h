#ifndef __MANGO_ADD_FILTER_H__
#define __MANGO_ADD_FILTER_H__

#include "mfilter.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new "add" filter.
 */
extern MangoFilter *mango_addfilter_new(const MangoString *name, ...);

#ifdef __cplusplus
}
#endif

#endif


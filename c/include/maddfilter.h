#ifndef __MANGO_ADD_FILTER_H__
#define __MANGO_ADD_FILTER_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initiases a filter as the "add" filter.
 */
extern void mango_addfilter_init(const MangoString *name, MangoFilter *filter, ...);

#ifdef __cplusplus
}
#endif

#endif


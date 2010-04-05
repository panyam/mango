#ifndef __MANGO_ADD_FILTER_H__
#define __MANGO_ADD_FILTER_H__

#include "mfwddefs.h"

/**
 * Creates a new "add" filter.
 */
extern MangoFilter *mango_addfilter_new(const MangoString *name, ...);

#endif


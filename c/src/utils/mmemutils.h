
#ifndef __MANGO_MEM_UTILS_H__
#define __MANGO_MEM_UTILS_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NEW(TYPE)               (TYPE *)malloc(sizeof(TYPE))
#define NEW_ARRAY(TYPE, size)   (TYPE *)malloc(size * sizeof(TYPE))

#define ZNEW(TYPE)              (TYPE *)calloc(1, sizeof(TYPE))
#define ZNEW_ARRAY(TYPE, size)  (TYPE *)calloc(size, sizeof(TYPE))

#ifdef __cplusplus
}
#endif

#endif


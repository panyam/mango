
#ifndef __MANGO_FWD_DEFS_H__
#define __MANGO_FWD_DEFS_H__

#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define true    1
#define false   0
typedef int BOOL;

typedef struct MangoInputStream MangoInputStream;
typedef struct MangoString MangoString;
typedef struct MangoToken MangoToken;
typedef struct MangoTokenizer MangoTokenizer;

#ifdef __cplusplus
}
#endif

#endif


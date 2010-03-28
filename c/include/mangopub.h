
#ifndef __MANGO_PUBLIC_H__
#define __MANGO_PUBLIC_H__

#include "mfwddefs.h"
#include "mtoken.h"
#include "mtokenizer.h"
#include "mparser.h"
#include "mlibrary.h"
#include "minputsource.h"
#include "mstring.h"
#include "mtemplateloader.h"

#ifdef __cplusplus
extern "C" {
#endif

#define true    1
#define false   0
typedef int BOOL;

typedef struct MangoInputSource MangoInputSource;
typedef struct MangoToken MangoToken;
typedef struct MangoTokenizer MangoTokenizer;

#ifdef __cplusplus
}
#endif

#endif


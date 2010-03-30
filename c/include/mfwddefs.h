
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

typedef struct MangoInputSource MangoInputSource;
typedef struct MangoString MangoString;
typedef struct MangoToken MangoToken;
typedef struct MangoTokenizer MangoTokenizer;
typedef struct MangoParser MangoParser;
typedef struct MangoError MangoError;
typedef struct MangoIterator MangoIterator;
typedef struct MangoList MangoList;
typedef struct MangoListNode MangoListNode;
typedef struct MangoNode MangoNode;
typedef struct MangoNodeContext MangoNodeContext;
typedef struct MangoTemplateLoader MangoTemplateLoader;
typedef struct MangoTemplateContext MangoTemplateContext;
typedef struct MangoLibrary MangoLibrary;
typedef struct MangoBinTree MangoBinTree;
typedef struct MangoBinTreeNode MangoBinTreeNode;

#ifdef __cplusplus
}
#endif

#endif


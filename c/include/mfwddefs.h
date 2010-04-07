
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

typedef struct MangoPrototype MangoPrototype;
typedef struct MangoObject MangoObject;
typedef struct MangoInputSource MangoInputSource;
typedef struct MangoString MangoString;
typedef struct MangoToken MangoToken;
typedef struct MangoTokenizer MangoTokenizer;
typedef struct MangoParser MangoParser;
typedef struct MangoError MangoError;
typedef struct MangoValue MangoValue;
typedef struct MangoFilter MangoFilter;
typedef struct MangoFilterNode MangoFilterNode;
typedef struct MangoVariable MangoVariable;
typedef struct MangoNode MangoNode;
typedef struct MangoNodeContext MangoNodeContext;
typedef struct MangoTemplateLoader MangoTemplateLoader;
typedef struct MangoTemplateContext MangoTemplateContext;
typedef struct MangoLibrary MangoLibrary;
typedef struct MangoFilterLibrary MangoFilterLibrary;
typedef struct MangoList MangoList;
typedef struct MangoListNode MangoListNode;
typedef struct MangoBinTree MangoBinTree;
typedef struct MangoBinTreeNode MangoBinTreeNode;
typedef struct MangoIterator MangoIterator;

/**
 * Functions that check whether two items are equal.
 */
typedef BOOL (*EqualsFunc)(const void *, const void *);

/**
 * Items that compare two items.
 */
typedef int (*CompareFunc)(const void *, const void *);

/**
 * Delete function signature.
 */
typedef void (*DeleteFunc)(void *);

#ifdef __cplusplus
}
#endif

#endif


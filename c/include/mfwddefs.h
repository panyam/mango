
#ifndef __MANGO_FWD_DEFS_H__
#define __MANGO_FWD_DEFS_H__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h>
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

typedef struct MangoArray MangoArray;
typedef struct MangoBinTree MangoBinTree;
typedef struct MangoBinTreeNode MangoBinTreeNode;
typedef struct MangoError MangoError;
typedef struct MangoFilter MangoFilter;
typedef struct MangoFilterPrototype MangoFilterPrototype;
typedef struct MangoFilterNode MangoFilterNode;
typedef struct MangoInputSource MangoInputSource;
typedef struct MangoIterator MangoIterator;
typedef struct MangoLibrary MangoLibrary;
typedef struct MangoList MangoList;
typedef struct MangoListNode MangoListNode;
typedef struct MangoNode MangoNode;
typedef struct MangoNodePrototype MangoNodePrototype;
typedef struct MangoNodeRenderContext MangoNodeRenderContext;
typedef struct MangoNodeRenderer MangoNodeRenderer;
typedef struct MangoObject MangoObject;
typedef struct MangoParser MangoParser;
typedef struct MangoParserContext MangoParserContext;
typedef struct MangoPrototype MangoPrototype;
typedef struct MangoRCString MangoRCString;
typedef struct MangoRCStringTable MangoRCStringTable;
typedef struct MangoRCStringFactory MangoRCStringFactory;
typedef struct MangoString MangoString;
typedef struct MangoStringBuffer MangoStringBuffer;
typedef struct MangoStringFactory MangoStringFactory;
typedef struct MangoStringPrototype MangoStringPrototype;
typedef struct MangoStringFactoryPrototype MangoStringFactoryPrototype;
typedef struct MangoTable MangoTable;
typedef struct MangoTagParser MangoTagParser;
typedef struct MangoTemplateContext MangoTemplateContext;
typedef struct MangoTemplateLoader MangoTemplateLoader;
typedef struct MangoToken MangoToken;
typedef struct MangoTokenizer MangoTokenizer;
typedef struct MangoValue MangoValue;
typedef struct MangoValueIterator MangoValueIterator;
typedef struct MangoVariable MangoVariable;
typedef struct MangoVariableResolver MangoVariableResolver;

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

#define NOT_IMPLEMENTED()    assert("Not Implemented" && false)

#ifdef __cplusplus
}
#endif

#endif


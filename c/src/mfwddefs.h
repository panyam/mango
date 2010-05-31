
#ifndef __MANGO_FWD_DEFS_H__
#define __MANGO_FWD_DEFS_H__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define true    1
#define false   0
typedef int BOOL;

typedef struct MangoArray MangoArray;
typedef struct MangoArrayList MangoArrayList;
typedef struct MangoBinTree MangoBinTree;
typedef struct MangoBinTreeNode MangoBinTreeNode;
typedef struct MangoCollection MangoCollection;
typedef struct MangoCollectionPrototype MangoCollectionPrototype;
typedef struct MangoError MangoError;
typedef struct MangoFilter MangoFilter;
typedef struct MangoFilterNode MangoFilterNode;
typedef struct MangoFilterPrototype MangoFilterPrototype;
typedef struct MangoFreeTextNode MangoFreeTextNode;
typedef struct MangoInputSource MangoInputSource;
typedef struct MangoIterator MangoIterator;
typedef struct MangoIteratorPrototype MangoIteratorPrototype;
typedef struct MangoLinkedList MangoLinkedList;
typedef struct MangoLinkedListNode MangoLinkedListNode;
typedef struct MangoList MangoList;
typedef struct MangoListPrototype MangoListPrototype;
typedef struct MangoNode MangoNode;
typedef struct MangoNodeContext MangoNodeContext;
typedef struct MangoNodeList MangoNodeList;
typedef struct MangoNodePrototype MangoNodePrototype;
typedef struct MangoNumber MangoNumber;
typedef struct MangoObject MangoObject;
typedef struct MangoOutStream MangoOutStream;
typedef struct MangoOutStreamPrototype MangoOutStreamPrototype;
typedef struct MangoParser MangoParser;
typedef struct MangoParserContext MangoParserContext;
typedef struct MangoPrototype MangoPrototype;
typedef struct MangoRCString MangoRCString;
typedef struct MangoRCStringFactory MangoRCStringFactory;
typedef struct MangoRCStringTable MangoRCStringTable;
typedef struct MangoRawArray MangoRawArray;
typedef struct MangoRawList MangoRawList;
typedef struct MangoRawListNode MangoRawListNode;
typedef struct MangoRenderer MangoRenderer;
typedef struct MangoRendererPrototype MangoRendererPrototype;
typedef struct MangoString MangoString;
typedef struct MangoStringBuffer MangoStringBuffer;
typedef struct MangoStringFactory MangoStringFactory;
typedef struct MangoStringFactoryPrototype MangoStringFactoryPrototype;
typedef struct MangoStringPrototype MangoStringPrototype;
typedef struct MangoTable MangoTable;
typedef struct MangoTablePrototype MangoTablePrototype;
typedef struct MangoTagNode MangoTagNode;
typedef struct MangoTagParser MangoTagParser;
typedef struct MangoTagParserPrototype MangoTagParserPrototype;
typedef struct MangoTemplateContext MangoTemplateContext;
typedef struct MangoTemplateContextPrototype MangoTemplateContextPrototype;
typedef struct MangoTemplateLoader MangoTemplateLoader;
typedef struct MangoToken MangoToken;
typedef struct MangoTokenizer MangoTokenizer;
typedef struct MangoTreeTable MangoTreeTable;
typedef struct MangoVar MangoVar;
typedef struct MangoVarNode MangoVarNode;
typedef struct MangoVarPrototype MangoVarPrototype;
typedef struct MangoVarResolver MangoVarResolver;
typedef struct MangoVarResolverPrototype MangoVarResolverPrototype;

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


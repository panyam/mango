
#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include "mangopub.h"
#include "mangoextpub.h"

/**
 * Registers an object in a library.
 */
extern void register_in_library(MangoContext *context, MangoLibrary *library, const char *key, MangoObject *value, void (*onRegistered)(MangoObject *obj) = NULL);

/**
 * Shortcut for creating a variable.
 */
extern MangoVar *create_var(MangoContext *context, const char *value, bool isQuoted, bool isNum, MangoVar *next);

#endif

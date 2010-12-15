
#include "testutils.h"

/**
 * Registers an object in a library.
 */
void register_in_library(MangoContext *context, MangoLibrary *library, const char *key, MangoObject *value, void (*onRegistered)(MangoObject *obj))
{
    MangoString *mkey = mango_stringfactory_new_string(context->string_factory, key, -1);
    mango_library_register(library, mkey, value, onRegistered);
    OBJ_DECREF(mkey);
}

/**
 * Shortcut for creating a variable.
 */
MangoVar *create_var(MangoContext *context, const char *value, bool isQuoted, bool isNum, MangoVar *next)
{
    MangoString *varValue = mango_stringfactory_new_string(context->string_factory, value, -1);
    MangoVar *var = mango_var_new(varValue, isQuoted, next);
    var->isNumber = isNum;
    if (isNum)
    {
        var->intValue = atoi(value);
    }
    return var;
}


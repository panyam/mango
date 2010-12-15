
#ifndef __MANGO_CONTEXT_H__
#define __MANGO_CONTEXT_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * MangoContexts are the bounded environment for mango.  Essentially
 * everything that mango requires (ie for parsing and rendering) is via the
 * utilities in the mango context.
 */
struct MangoContext
{
    /**
     * String factory used to create and destroy strings.
     */
    MangoStringFactory *    string_factory;

    /**
     * Filter library used through out the context.
     */
    MangoLibrary *          filter_library;

    /**
     * Variable library used through out the context.
     */
    MangoLibrary *          var_library;

    /**
     * Tag Parser library used through out the context.
     */
    MangoLibrary *          tag_library;

    /**
     * Loads the templates.
     */
    MangoTemplateLoader *   tmpl_loader;
};

/**
 * Creates a new mango context.  This is required to do practially anything
 * with/in mango.  Particular utilities can be over ridden by callers (ie
 * specialised strings etc.
 *
 * Passing NULL would create default values.
 */
extern MangoContext *mango_context_new(MangoStringFactory *    string_factory,
                                       MangoLibrary *          filter_library,
                                       MangoLibrary *          var_library,
                                       MangoLibrary *          tag_library,
                                       MangoTemplateLoader *   tmpl_loader);

/**
 * Destroys a mango context.
 */
extern void mango_context_free(MangoContext *ctx);

#ifdef __cplusplus
}
#endif

#endif


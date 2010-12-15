
#include "mangopub.h"

/**
 * Creates a new mango context.  This is required to do practially anything
 * with/in mango.  Particular utilities can be over ridden by callers (ie
 * specialised strings etc.
 *
 * Passing NULL would create default values.
 */
MangoContext *mango_context_new(MangoStringFactory *    string_factory,
                                MangoLibrary *          filter_library,
                                MangoLibrary *          var_library,
                                MangoLibrary *          tag_library,
                                MangoTemplateLoader *   tmpl_loader)
{
    MangoContext *ctx = ZNEW(MangoContext);

    if (string_factory == NULL)
        string_factory = (MangoStringFactory *)mango_rcstringfactory_default();

    if (filter_library == NULL)
        filter_library = mango_filter_library_singleton();

    if (var_library == NULL)
        var_library = mango_var_library_singleton();

    if (tag_library == NULL)
        tag_library = mango_tagparser_library_singleton();

    ctx->string_factory = OBJ_INCREF(string_factory);
    ctx->filter_library = OBJ_INCREF(filter_library);
    ctx->var_library    = OBJ_INCREF(var_library);
    ctx->tag_library    = OBJ_INCREF(tag_library);
    ctx->tmpl_loader    = OBJ_INCREF(tmpl_loader);

    return ctx;
}

/**
 * Destroys a mango context.
 */
void mango_context_free(MangoContext *ctx)
{
    OBJ_DECREF(ctx->string_factory);
    OBJ_DECREF(ctx->filter_library);
    OBJ_DECREF(ctx->var_library);
    OBJ_DECREF(ctx->tag_library);
    OBJ_DECREF(ctx->tmpl_loader);
    free(ctx);
}


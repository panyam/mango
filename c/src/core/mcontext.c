
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
                                MangoTemplateLoader *   loader)
{
    MangoContext *ctx = ZNEW(MangoContext);

    if (string_factory == NULL)
        ctx->string_factory = mango_rcstringfactory_default();
    else
        ctx->string_factory = OBJ_INCREF(string_factory);

    if (filter_library == NULL)
        ctx->filter_library = mango_filter_library_singleton();
    else
        ctx->filter_library = OBJ_INCREF(filter_library);

    if (var_library == NULL)
        ctx->var_library = mango_var_library_singleton();
    else
        ctx->var_library = OBJ_INCREF(var_library);

    if (tag_library == NULL)
        ctx->tag_library = mango_tag_library_singleton();
    else
        ctx->tag_library = OBJ_INCREF(tag_library);

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
    OBJ_DECREF(ctx->loader);
    free(ctx);
}


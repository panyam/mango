
#include "mvarresolver.h"
#include "mtemplatecontext.h"
#include "mvar.h"
#include "mvalue.h"
#include "mmemutils.h"

/**
 * The default resolver method.
 */
MangoValue *default_resolve_func(void *resolver_data,
                                 MangoValue *source,
                                 MangoVariable *variable);

/**
 * Returns a default variable resolver.
 */
MangoVariableResolver *mango_varresolver_default()
{
    MangoVariableResolver *resolver = ZNEW(MangoVariableResolver);
    resolver->resolveFunc = default_resolve_func;
    return resolver;
}

/**
 * Destroys a variable resolver.
 */
void mango_varresolver_free(MangoVariableResolver *resolver)
{
    if (resolver->data != NULL && resolver->freeFunc != NULL)
    {
        resolver->freeFunc(resolver->data);
    }
    free(resolver);
}

/**
 * Resolves the variable value with the resolver.
 * \param   resolver    Resolver doing the var resolving.
 * \param   source      The source variable from which variables are resolved.
 * \param   variable    Variable to be resolved.
 * \return  A MangoValue instance that must be freed by the caller.
 */
MangoValue *mango_varresolver_resolve(MangoVariableResolver *resolver,
                                      MangoValue *source,
                                      MangoVariable *variable)
{
    if (resolver->resolveFunc != NULL)
    {
        return resolver->resolveFunc(resolver->data, source, variable);
    }
    return NULL;
}

/**
 * Resolves a variable chain starting from the first variable using the
 * template context.
 * \param   resolver    Main resolver object.
 * \param   ctx         Context with which the variable is resolved.
 * \param   first       First variable to start resolving with.
 * \return  The value corresponding to the variable.
 */
MangoValue *mango_varresolver_resolve_chain(MangoVariableResolver *resolver,
                                            MangoTemplateContext *ctx,
                                            MangoVariable *first)
{
    // if the first item is a number then everything is ignored
    MangoVariable *curr_var = first;
    MangoVariable *prev_var = NULL;
    MangoValue ctx_value = mango_value_make(MV_CONTEXT, ctx);
    MangoValue *curr_src = &ctx_value;
    while (curr_src != NULL && curr_var != NULL)
    {
        if (prev_var == NULL)
        {
            if (curr_var->isNumber)
                return mango_value_new(MV_INT, (void*)curr_var->intValue);
            if (curr_var->isQuoted)
                return mango_value_new(MV_STRING,
                                        mango_string_copy(curr_var->value));
            if (ctx == NULL)
                return NULL;
            curr_src = mango_templatecontext_get(ctx, curr_var->value);
        }
        else
        {
            MangoValue *newsrc = mango_varresolver_resolve(resolver, curr_src, curr_var);
            if (curr_src != &ctx_value)
                mango_value_free(curr_src);
            curr_src = newsrc;
        }
        prev_var = curr_var;
        curr_var = curr_var->next;
    }
    return curr_src;
}


/**
 * The default resolver method.
 */
MangoValue *default_resolve_func(void *resolver_data,
                                 MangoValue *source,
                                 MangoVariable *variable)
{
    return NULL;
}

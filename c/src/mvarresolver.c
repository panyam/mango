
#include "marray.h"
#include "mvarresolver.h"
#include "mtemplatecontext.h"
#include "mvar.h"
#include "mmemutils.h"

/**
 * The default variable resolver function.
 */
MangoObject *default_resolver_func(MangoVarResolver *resolver, MangoObject *source, MangoVar *var);

DECLARE_PROTO_FUNC("VarResolver", MangoVarResolverPrototype, mango_varresolver_prototype, 
    __proto__.resolveFunc = NULL;
);

/**
 * Returns a default var resolver.
 */
MangoVarResolver *mango_varresolver_default()
{
    static MangoVarResolver resolver;
    static BOOL initialised = false;
    if (!initialised)
    {
        OBJ_INIT(&resolver , mango_varresolver_prototype());
        initialised = true;
    }
    return &resolver;
}

/**
 * Deallocates a resolver on destruction.
 */
void mango_varresolver_dealloc(MangoVarResolver *resolver)
{
    mango_object_dealloc((MangoObject *)resolver);
}

/**
 * Resolves the var value with the resolver.
 * \param   resolver    Resolver doing the var resolving.
 * \param   source      The source var from which vars are resolved.
 * \param   var    Var to be resolved.
 * \return  A MangoObject instance that must be freed by the caller.
 */
MangoObject *mango_varresolver_resolve(MangoVarResolver *resolver,
                                      MangoObject *source,
                                      MangoVar *var)
{
    if (resolver->__prototype__->resolveFunc != NULL && var != NULL)
    {
        return resolver->__prototype__->resolveFunc(resolver, source, var);
    }
    return NULL;
}

/**
 * Resolves a var chain starting from the first var using the
 * template context.
 * \param   resolver    Main resolver object.
 * \param   ctx         Context with which the var is resolved.
 * \param   first       First var to start resolving with.
 * \return  The value corresponding to the var.
 */
MangoObject *mango_varresolver_resolve_chain(MangoVarResolver *resolver,
                                            MangoTemplateContext *ctx,
                                            MangoVar *first)
{
    // if the first item is a number then everything is ignored
    MangoVar *curr_var = first;
    MangoVar *prev_var = NULL;
    MangoObject *curr_src = ((MangoObject *)ctx);
    while (curr_src != NULL && curr_var != NULL)
    {
        if (prev_var == NULL)
        {
            if (curr_var->isNumber)
                return mango_number_from_int(curr_var->intValue);
            if (curr_var->isQuoted)
                return OBJ_INCREF(curr_var->value);
            if (ctx == NULL)
                return NULL;
            curr_src = mango_templatecontext_get(ctx, curr_var->value);
        }
        else
        {
            // decref the previous value since it would have been increfed
            // in varresolver_resolve
            // if (curr_src != ctx) OBJ_DECREF(curr_src);
            curr_src = mango_varresolver_resolve(resolver, curr_src, curr_var);
        }
        prev_var = curr_var;
        curr_var = curr_var->next;
    }
    return curr_src;
}

/**
 * The default variable resolver function.
 * Unlike the android based resolver which has nice introspection, we do
 * nothing fancy, just check the source value type and so on.
 */
MangoObject *default_resolver_func(MangoVarResolver *resolver, MangoObject *source, MangoVar *var)
{
    /**
     * Resolves the value of a variable using a particular value.
     * The resolution strategy used is slightly different from what django
     * does, in order to make things a bit faster for the common case of
     * dictionary and index based lookups.
     *
     * ((Array)source)[value] if value is an integer
     * ((Dictionary)source)[value] if value is NOT an integer
     *
     * Returns null if the variable cannot be resolved after applying the
     * above rules.
     */
    // try as an integer first
    if (var->isNumber)
    {
        int intValue = var->intValue;
        return OBJ_GETINTATTR(source, var->intValue);
    }
    else
    {
        return OBJ_GETSTRATTR(source, var->value);
    }

    return NULL;
}


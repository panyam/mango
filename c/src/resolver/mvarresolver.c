
#include "mangopub.h"

/**
 * The default variable resolver function.
 */
MangoObject *default_resolver_func(MangoVarResolver *resolver, MangoObject *source, MangoVar *var);

DECLARE_PROTO_FUNC(mango_varresolver_prototype, MangoVarResolverPrototype, NULL, 
    __proto__.resolveFunc = default_resolver_func;
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
 * \param   source      Starting source object with which the var is resolved.
 * \param   first       First var to start resolving with.
 * \return  The value corresponding to the var.
 */
MangoObject *mango_varresolver_resolve_chain(MangoVarResolver *resolver, MangoObject *source, MangoVar *first)
{
    // if the first item is a number then everything is ignored
    MangoVar *curr_var = first;
    MangoVar *prev_var = NULL;
    MangoObject *curr_src = source;
    while (curr_src != NULL && curr_var != NULL)
    {
        if (prev_var == NULL)
        {
            if (curr_var->isNumber)
                return (MangoObject *)mango_number_from_int(curr_var->intValue);
            else if (curr_var->isQuoted)
                return (MangoObject *)OBJ_INCREF(curr_var->value);
            else if (source == NULL)
                return NULL;
            curr_src = OBJ_GETSTRATTR(source, curr_var->value);
        }
        else
        {
            // decref the previous value since it would have been increfed
            // in varresolver_resolve
            // if (curr_src != source) OBJ_DECREF(curr_src);
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
 * nothing fancy, just check the source value type and move on.
 */
MangoObject *default_resolver_func(MangoVarResolver *resolver, MangoObject *source, MangoVar *var)
{
    if (var->isNumber)
    {
        return OBJ_GETINTATTR(source, var->intValue);
    }
    return OBJ_GETSTRATTR(source, var->value);
}


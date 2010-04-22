
#ifndef __MANGO_VARIABLE_RESOLVER_H__
#define __MANGO_VARIABLE_RESOLVER_H__

#include "mvar.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoVariableResolver
{
    /**
     * Implementation specific data.
     */
    void *data;

    /**
     * Frees the resolver data.
     */
    void (*freeFunc)(void *data);

    /**
     * Callback to do the actual resolution.
     */
    MangoValue *(*resolveFunc)(void *data, MangoValue *source, MangoVariable *variable);
};

/**
 * Returns a default variable resolver.
 */
extern MangoVariableResolver *mango_varresolver_default();

/**
 * Destroys a variable resolver.
 */
extern void mango_varresolver_free(MangoVariableResolver *resolver);

/**
 * Resolves the variable value with the resolver.
 * \param   resolver    Resolver doing the var resolving.
 * \param   source      The source variable from which variables are resolved.
 * \param   variable    Variable to be resolved.
 * \return  A MangoValue instance that must be freed by the caller.
 */
extern MangoValue *mango_varresolver_resolve(MangoVariableResolver *resolver,
                                             MangoValue *source,
                                             MangoVariable *variable);

/**
 * Resolves a variable chain starting from the first variable using the
 * template context.
 * \param   resolver    Main resolver object.
 * \param   ctx         Context with which the variable is resolved.
 * \param   first       First variable to start resolving with.
 * \return  The value corresponding to the variable.
 */
extern MangoValue *mango_varresolver_resolve_chain(MangoVariableResolver *resolver,
                                                   MangoTemplateContext *ctx,
                                                   MangoVariable *first);

#ifdef __cplusplus
}
#endif

#endif


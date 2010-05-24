
#ifndef __MANGO_VARIABLE_RESOLVER_H__
#define __MANGO_VARIABLE_RESOLVER_H__

#include "mvar.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoVarResolverPrototype, MangoPrototype,
    /**
     * Callback to do the actual resolution.
     */
    MangoObject *(*resolveFunc)(MangoVarResolver *data, MangoObject *source, MangoVar *var);
);

DECLARE_CLASS(MangoVarResolver, MangoVarResolverPrototype);

/**
 * Returns a default var resolver.
 */
extern MangoVarResolver *mango_varresolver_default();

/**
 * Destroys a var resolver.
 */
extern void mango_varresolver_free(MangoVarResolver *resolver);

/**
 * Resolves the var value with the resolver.
 * \param   resolver    Resolver doing the var resolving.
 * \param   source      The source var from which vars are resolved.
 * \param   var    Var to be resolved.
 * \return  A MangoObject instance that must be freed by the caller.
 */
extern MangoObject *mango_varresolver_resolve(MangoVarResolver *resolver,
                                             MangoObject *source,
                                             MangoVar *var);

/**
 * Resolves a var chain starting from the first var using the
 * template context.
 * \param   resolver    Main resolver object.
 * \param   ctx         Context with which the var is resolved.
 * \param   first       First var to start resolving with.
 * \return  The value corresponding to the var.
 */
extern MangoObject *mango_varresolver_resolve_chain(MangoVarResolver *resolver,
                                                   MangoTemplateContext *ctx,
                                                   MangoVar *first);

#ifdef __cplusplus
}
#endif

#endif


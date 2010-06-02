
#ifndef __MANGO_VARIABLE_H__
#define __MANGO_VARIABLE_H__

#include "core/mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

// Simplified typedefs
typedef MangoVar *(*VarSetNextFunc)(MangoVar *mvar, MangoString *value, BOOL isquoted);
typedef MangoObject *(*VarResolveFunc)(MangoVar *               mvar,
                                       MangoTemplateContext *   context,
                                       MangoNodeContext *       topContext);

INHERIT_STRUCT(MangoVarPrototype, MangoPrototype,
    //! Child specific setter of the next var
    MangoVar *(*setNextVarFunc)(MangoVar *mvar, MangoString *value, BOOL isquoted);

    /**
     * Resolve a variable against a template context and an optional node context.
     */
    MangoObject *(*resolveFunc)(MangoVar *               mvar,
                                MangoTemplateContext *   context,
                                MangoNodeContext *       topContext);
);

DECLARE_CLASS(MangoVar, MangoVarPrototype,
    //! String value of the var.
    MangoString *   value;

    //! Is the value an identifier or a quoted value
    BOOL            isQuoted;

    //! Can the value be converted to a number
    BOOL            isNumber;

    //! Integer value if value can be converted to a number
    int             intValue;
    
    //! Next var section of the var (ie a.b.c)
    MangoVar * next;
);

/**
 * Creates a new mango var.
 * \param   mstr        Value of the var.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next var in the chain.
 * \return  A new MangoVar instance.
 */
extern MangoVar *mango_var_new(MangoString *mstr, BOOL isQuoted, MangoVar *next);

/**
 * Initialises a variable prototype.
 */
extern MangoVarPrototype *mango_var_prototype_init(MangoVarPrototype *proto);

/**
 * Initialises a mango var.
 * \param   mvar        Var to be initialised.
 * \param   proto       Prototype to be initialised with.
 * \param   mstr        Value of the var.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next var in the chain.
 * \return  The same var.
 */
extern MangoVar *mango_var_init(MangoVar *mvar, MangoVarPrototype *proto,
                                MangoString *mstr, BOOL isQuoted, MangoVar *next);

/**
 * Deallocs a mango var when refcount reaches 0.
 * \param   mvar        Var to be dealloced.
 */
extern void mango_var_dealloc(MangoVar *mvar);

/**
 * Sets the new value of a var.
 *
 * \param   mvar        Var whose value is to be changed.
 * \param   isQuoted    Is the value quoted?
 * \param   value       New Value.  The var gets ownership of this string.
 */
extern void mango_var_set_value(MangoVar *mvar,
                                     MangoString *value,
                                     BOOL isQuoted);

/**
 * Resolves the value of a var (for rendering purposes) given the
 * template and node contexts.
 */
extern MangoObject *mango_var_resolve(MangoVar *            mvar,
                                      MangoTemplateContext *context,
                                      MangoNodeContext *    topContext);

/**
 * Returns if two vars are equal.
 */
extern BOOL mango_vars_are_equal(const MangoVar *var1,
                                      const MangoVar *var2);

/**
 * Sets the next var for a particular var.
 *
 * \param   mvar    The var whose next var is to be set.
 * \param   value   Value of the next var.
 * \param   iquote  Is the value quoted?
 *
 * \return  A new var if it is set.
 */
extern MangoVar *mango_var_set_next(MangoVar *mvar, MangoString *value, BOOL isquoted);

/**
 * Extract a var using the parser.
 *
 * \param   ctx     Parser context containing necessary items for parsing.
 * \param   error   Errors to be set if any.
 *
 * \return A MangoVar instance if successful, otherwise NULL with the
 * error var set (if it is supplied).
 */
extern MangoVar *mango_var_extract_with_parser(MangoParser *parser, MangoContext *ctx, MangoError **error);

#ifdef __cplusplus
}
#endif

#endif


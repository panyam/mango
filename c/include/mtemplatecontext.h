
#ifndef __MANGO_TEMPLATE_CONTEXT_H__
#define __MANGO_TEMPLATE_CONTEXT_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

INHERIT_STRUCT(MangoTemplateContextPrototype, MangoPrototype,
    /**
     * Get the values for a particular var in the context.
     * \param   context Context from which the values are extracted.
     * \param   key     Var for which the values are extracted.
     * \param   create  If the key was not found, this specifies whether a new
     *                  stack it to be created.
     * \return A MangoList of values for the var.
     */
    const MangoList *(*getValuesFunc)(MangoTemplateContext *context, const MangoString *key, BOOL create);

    /**
     * Gets the value of a var by a key.
     * \param   ctx     The context where values are stored.
     * \param   key     Var whose value is to be fetched.
     * \return  Value of the var.
     */
    MangoObject *(*getFunc)(MangoTemplateContext *ctx, const MangoString *key);

    /**
     * Sets the value of a particular key.
     * \param   ctx     Context in which the value is to be set.
     * \param   key     Var key
     * \param   value   Value of the var.
     * \return  The new size of the value stack for the var.
     */
    int (*setFunc)(MangoTemplateContext *ctx, const MangoString *key, MangoObject *value);

    /**
     * Pushes the value of a particular key.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Var key
     * \param   value   Value of the var.
     * \return  The new size of the value stack for the var.
     */
    int (*pushFunc)(MangoTemplateContext *ctx, const MangoString *key, MangoObject *value);

    /**
     * Pops the value of a var and returns it.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Key/Value arguments, terminated by NULL.
     * \return  MangoObject for the var.
     */
    MangoObject *(*popFunc)(MangoTemplateContext *ctx, const MangoString *key);

    /**
     * Deletes the value of a var completely.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Key/Value arguments, terminated by NULL.
     */
    void (*deleteFunc)(MangoTemplateContext *ctx, const MangoString *key);

    /**
     * Tells if a var by a particular key exists.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Key/Value arguments, terminated by NULL.
     * \return true if the var exits, false otherwise.
     */
    BOOL (*containsFunc)(MangoTemplateContext *ctx, const MangoString *key);

    /**
     * Merge the values of another dictionary into a context.
     * \param   context Context into which the values are being merged.
     * \param   dict    Dictionary from which the values are being merged.
     */
    void (*mergeFunc)(MangoTemplateContext *context, MangoTable *dict);
);

/**
 * Context objects contain values for vars that get substituted in a
 * template.
 */
DECLARE_CLASS(MangoTemplateContext, MangoTemplateContextPrototype,
    MangoTable *values;
);

/**
 * Creates a new mango template context.
 */
extern MangoTemplateContext *mango_templatecontext_new();

/**
 * Initialises the template context and returns it.
 */
extern MangoTemplateContext *mango_templatecontext_init(MangoTemplateContext *ctx, MangoTemplateContextPrototype *proto);

/**
 * Frees the context and all values in it.
 * \param   context Context to be freed.
 */
extern void mango_templatecontext_dealloc(MangoTemplateContext *context);

/**
 * Get the values for a particular var in the context.
 * \param   context Context from which the values are extracted.
 * \param   key     Var for which the values are extracted.
 * \param   create  If the key was not found, this specifies whether a new
 *                  stack it to be created.
 * \return A MangoList of values for the var.
 */
extern const MangoList *mango_templatecontext_get_values(
            MangoTemplateContext *context,
            const MangoString *key,
            BOOL create);

/**
 * Gets the value of a var by a key.
 * \param   ctx     The context where values are stored.
 * \param   key     Var whose value is to be fetched.
 * \return  Value of the var.
 */
extern MangoObject *mango_templatecontext_get(MangoTemplateContext *ctx,
                                             const MangoString *key);

/**
 * Sets the value of a particular key, overwriting an existing one or
 * pushing onto one if necessary.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \param   push    Whether the value is to be pushed or replaced.
 * \param   The new size of the value stack for the var.
 */
extern int mango_templatecontext_set_or_push(MangoTemplateContext *ctx,
                                             const MangoString *key,
                                             MangoObject *value,
                                             BOOL push);

/**
 * Sets the value of a particular key.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
extern int mango_templatecontext_set(MangoTemplateContext *ctx,
                                     const MangoString *key,
                                     MangoObject *value);

/**
 * Sets multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be set.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
extern void mango_templatecontext_set_values(MangoTemplateContext *ctx, ...);

/**
 * Pushes the value of a particular key.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
extern int mango_templatecontext_push(MangoTemplateContext *ctx,
                                      const MangoString *key,
                                      MangoObject *value);

/**
 * Pushes multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
extern void mango_templatecontext_push_values(MangoTemplateContext *ctx, ...);

/**
 * Pops the value of a var and returns it.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return  MangoObject for the var.
 */
extern MangoObject *mango_templatecontext_pop(MangoTemplateContext *ctx, const MangoString *key);

/**
 * Deletes the value of a var completely.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 */
extern void mango_templatecontext_delete(MangoTemplateContext *ctx, const MangoString *key);

/**
 * Tells if a var by a particular key exists.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return true if the var exits, false otherwise.
 */
extern BOOL mango_templatecontext_contains(MangoTemplateContext *ctx, const MangoString *key);

/**
 * Merge the values of another dictionary into a context.
 * \param   context Context into which the values are being merged.
 * \param   dict    Dictionary from which the values are being merged.
 */
extern void mango_templatecontext_merge(MangoTemplateContext *context, MangoTable *dict);

#ifdef __cplusplus
}
#endif

#endif


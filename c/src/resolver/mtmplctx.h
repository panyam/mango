
#ifndef __MANGO_TEMPLATE_CONTEXT_H__
#define __MANGO_TEMPLATE_CONTEXT_H__

#include "core/mobject.h"

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
    MangoList *(*getValuesFunc)(MangoTemplateContext *context, MangoString *key, BOOL create);

    /**
     * Sets the value of a particular key.
     * \param   ctx     Context in which the value is to be set.
     * \param   key     Var key
     * \param   value   Value of the var.
     * \return  The new size of the value stack for the var.
     */
    int (*setFunc)(MangoTemplateContext *ctx, MangoString *key, MangoObject *value);

    /**
     * Pushes the value of a particular key.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Var key
     * \param   value   Value of the var.
     * \return  The new size of the value stack for the var.
     */
    int (*pushFunc)(MangoTemplateContext *ctx, MangoString *key, MangoObject *value);

    /**
     * Pops the value of a var and returns it.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Key/Value arguments, terminated by NULL.
     * \return  MangoObject for the var.
     */
    MangoObject *(*popFunc)(MangoTemplateContext *ctx, MangoString *key);

    /**
     * Deletes the value of a var completely.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Key/Value arguments, terminated by NULL.
     */
    void (*deleteFunc)(MangoTemplateContext *ctx, MangoString *key);

    /**
     * Tells if a var by a particular key exists.
     * \param   ctx     Context in which the value is to be pushed.
     * \param   key     Key/Value arguments, terminated by NULL.
     * \return true if the var exits, false otherwise.
     */
    BOOL (*containsFunc)(MangoTemplateContext *ctx, MangoString *key);

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
 * Default prototype for template context.
 */
extern MangoTemplateContextPrototype *mango_tmplctx_prototype();

/**
 * Creates a new mango template context.
 */
extern MangoTemplateContext *mango_tmplctx_new();

/**
 * Initialises the template context and returns it.
 */
extern MangoTemplateContext *mango_tmplctx_init(MangoTemplateContext *ctx, MangoTemplateContextPrototype *proto);

/**
 * Frees the context and all values in it.
 * \param   context Context to be freed.
 */
extern void mango_tmplctx_dealloc(MangoTemplateContext *context);

/**
 * Get the values for a particular var in the context.
 * \param   context Context from which the values are extracted.
 * \param   key     Var for which the values are extracted.
 * \param   create  If the key was not found, this specifies whether a new
 *                  stack it to be created.
 * \return A MangoList of values for the var.
 */
extern MangoList *mango_tmplctx_get_values(MangoTemplateContext *context, MangoString *key, BOOL create);

/**
 * Sets the value of a particular key, overwriting an existing one or
 * pushing onto one if necessary.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \param   push    Whether the value is to be pushed or replaced.
 * \param   The new size of the value stack for the var.
 */
extern int mango_tmplctx_set_or_push(MangoTemplateContext *ctx, MangoString *key, MangoObject *value, BOOL push);

/**
 * Sets the value of a particular key.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
extern int mango_tmplctx_set(MangoTemplateContext *ctx, MangoString *key, MangoObject *value);

/**
 * Sets multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be set.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
extern void mango_tmplctx_set_values(MangoTemplateContext *ctx, ...);

/**
 * Pushes the value of a particular key.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Var key
 * \param   value   Value of the var.
 * \return  The new size of the value stack for the var.
 */
extern int mango_tmplctx_push(MangoTemplateContext *ctx, MangoString *key, MangoObject *value);

/**
 * Pushes multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
extern void mango_tmplctx_push_values(MangoTemplateContext *ctx, ...);

/**
 * Pops the value of a var and returns it.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return  MangoObject for the var.
 */
extern MangoObject *mango_tmplctx_pop(MangoTemplateContext *ctx, MangoString *key);

/**
 * Deletes the value of a var completely.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 */
extern void mango_tmplctx_delete(MangoTemplateContext *ctx, MangoString *key);

/**
 * Tells if a var by a particular key exists.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return true if the var exits, false otherwise.
 */
extern BOOL mango_tmplctx_contains(MangoTemplateContext *ctx, MangoString *key);

/**
 * Merge the values of another dictionary into a context.
 * \param   context Context into which the values are being merged.
 * \param   dict    Dictionary from which the values are being merged.
 */
extern void mango_tmplctx_merge(MangoTemplateContext *context, MangoTable *dict);

#ifdef __cplusplus
}
#endif

#endif


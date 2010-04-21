
#ifndef __MANGO_TEMPLATE_CONTEXT_H__
#define __MANGO_TEMPLATE_CONTEXT_H__

#include <stdarg.h>
#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Context objects contain values for variables that get substituted in a
 * template.
 */
struct MangoTemplateContext
{
    MangoBinTree *values;
};

/**
 * Creates a new mango template context.
 */
extern MangoTemplateContext *mango_templatecontext_new();

/**
 * Get the values for a particular variable in the context.
 * \param   context Context from which the values are extracted.
 * \param   key     Variable for which the values are extracted.
 * \param   create  If the key was not found, this specifies whether a new
 *                  stack it to be created.
 * \return A MangoList of values for the variable.
 */
extern const MangoList *mango_templatecontext_get_values(
            MangoTemplateContext *context,
            const MangoString *key,
            BOOL create);

/**
 * Gets the value of a variable by a key.
 * \param   ctx     The context where values are stored.
 * \param   key     Variable whose value is to be fetched.
 * \return  Value of the variable.
 */
extern MangoValue *mango_templatecontext_get(MangoTemplateContext *ctx,
                                             const MangoString *key);

/**
 * Sets the value of a particular key, overwriting an existing one or
 * pushing onto one if necessary.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Variable key
 * \param   value   Value of the variable.
 * \param   push    Whether the value is to be pushed or replaced.
 * \param   The new size of the value stack for the variable.
 */
extern int mango_templatecontext_set_or_push(MangoTemplateContext *ctx,
                                             const MangoString *key,
                                             MangoValue *value,
                                             BOOL push);

/**
 * Sets the value of a particular key.
 * \param   ctx     Context in which the value is to be set.
 * \param   key     Variable key
 * \param   value   Value of the variable.
 * \return  The new size of the value stack for the variable.
 */
extern int mango_templatecontext_set(MangoTemplateContext *ctx,
                                     const MangoString *key,
                                     MangoValue *value);

/**
 * Sets multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be set.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
extern void mango_templatecontext_set_values(MangoTemplateContext *ctx, ...);

/**
 * Pushes the value of a particular key.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Variable key
 * \param   value   Value of the variable.
 * \return  The new size of the value stack for the variable.
 */
extern int mango_templatecontext_push(MangoTemplateContext *ctx,
                                      const MangoString *key,
                                      MangoValue *value);

/**
 * Pushes multiple values given by a list of key/value pairs.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   ...     Key/Value arguments, terminated by NULL.
 */
extern void mango_templatecontext_push_values(MangoTemplateContext *ctx, ...);

/**
 * Pops the value of a variable and returns it.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return  MangoValue for the variable.
 */
extern MangoValue *mango_templatecontext_pop(MangoTemplateContext *ctx,
                                             const MangoString *key);

/**
 * Deletes the value of a variable completely.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 */
extern void mango_templatecontext_delete(MangoTemplateContext *ctx,
                                         const MangoString *key);

/**
 * Tells if a variable by a particular key exists.
 * \param   ctx     Context in which the value is to be pushed.
 * \param   key     Key/Value arguments, terminated by NULL.
 * \return true if the variable exits, false otherwise.
 */
extern BOOL mango_templatecontext_contains(MangoTemplateContext *ctx,
                                           const MangoString *key);

/**
 * Merge the values of another dictionary into a context.
 * \param   context Context into which the values are being merged.
 * \param   dict    Dictionary from which the values are being merged.
 */
extern void mango_templatecontext_merge(MangoTemplateContext *context,
                                        MangoBinTree *dict);

#ifdef __cplusplus
}
#endif

#endif


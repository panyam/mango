
#ifndef __MANGO_VARIABLE_H__
#define __MANGO_VARIABLE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoVariable
{
    //! String value of the variable.
    MangoString *   value;

    //! Is the value an identifier or a quoted value
    BOOL            isQuoted;

    //! Can the value be converted to a number
    BOOL            isNumber;

    //! Integer value if value can be converted to a number
    int             intValue;
    
    //! Next variable section of the variable (ie a.b.c)
    MangoVariable * next;
};

/**
 * Creates a new mango variable.
 * \param   mstr        Value of the variable.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next variable in the chain.
 * \return  A new MangoVariable instance.
 */
extern MangoVariable *mango_variable_new(MangoString *mstr, BOOL isQuoted, MangoVariable *next);

/**
 * Destroys a mango variable.
 * \param   mstr        Variable to be destroyed.
 */
extern void mango_variable_free(MangoVariable *mvar);

/**
 * Sets the new value of a variable.
 *
 * \param   mvar        Variable whose value is to be changed.
 * \param   isQuoted    Is the value quoted?
 * \param   buffer      New Value
 * \param   length      Length of the buffer.  if < then buffer is null terminated.
 */
extern void mango_variable_set_value(MangoVariable *mvar, BOOL isQuoted, const char *buffer, int length);

/**
 * Resolves the value of a variable (for rendering purposes) given the
 * template and node contexts.
 */
extern int mango_variable_resolve(MangoVariable *mvar, MangoTemplateContext *context, MangoNodeContext *topContext, void **value);

/**
 * Returns if two variables are equal.
 */
extern BOOL mango_variable_equals(MangoVariable *var1, MangoVariable *var2);

#ifdef __cplusplus
}
#endif

#endif


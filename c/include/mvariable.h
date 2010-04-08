
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

    //! Extendible data.
    void *          varData;

    //! Child specific setter of the next variable
    MangoVariable *(*setNextVariable)(MangoVariable *mvar, MangoString *value, BOOL isquoted);
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
 * \param   value       New Value.  The variable gets ownership of this string.
 */
extern void mango_variable_set_value(MangoVariable *mvar,
                                     MangoString *value,
                                     BOOL isQuoted);

/**
 * Resolves the value of a variable (for rendering purposes) given the
 * template and node contexts.
 */
extern int mango_variable_resolve(MangoVariable *       mvar,
                                  MangoTemplateContext *context,
                                  MangoNodeContext *    topContext,
                                  void **               value);

/**
 * Returns if two variables are equal.
 */
extern BOOL mango_variables_are_equal(const MangoVariable *var1,
                                      const MangoVariable *var2);

/**
 * Sets the next variable for a particular variable.
 *
 * \param   mvar    The variable whose next variable is to be set.
 * \param   value   Value of the next variable.
 * \param   iquote  Is the value quoted?
 *
 * \return  A new variable if it is set.
 */
extern MangoVariable *mango_variable_set_next(MangoVariable *mvar, MangoString *value, BOOL isquoted);

/**
 * Extract a variable using the parser.
 *
 * \param   parser  Parser extracting the tokens.
 * \param   error   Errors to be set if any.
 * \param   varlib  Variable library to fetch "special" variables from.
 *
 * \return A MangoVariable instance if successful, otherwise NULL with the
 * error variable set (if it is supplied).
 */
extern MangoVariable *mango_variable_extract_with_parser(MangoParser *parser,
                                                         MangoError **error,
                                                         MangoLibrary *varlib);

#ifdef __cplusplus
}
#endif

#endif



#include "mvariable.h"
#include "mstring.h"
#include "mtemplatecontext.h"
#include "mnode.h"

/**
 * Creates a new mango variable.
 * \param   mstr        Value of the variable.
 * \param   isQuoted    Whether the value is quoted or not.
 * \param   next        Next variable in the chain.
 * \return  A new MangoVariable instance.
 */
MangoVariable *mango_variable_new(MangoString *mstr, BOOL isQuoted, MangoVariable *next)
{
    MangoVariable *mvar = (MangoVariable *)malloc(sizeof(MangoVariable));
    mvar->next      = next;
    mvar->value     = NULL;
    mango_variable_set_value(mvar, isQuoted, mstr->buffer, mstr->length);
    return mvar;
}

/**
 * Sets the new value of a variable.
 *
 * \param   mvar    Variable whose value is to be changed.
 * \param   buffer  New Value
 * \param   length  Length of the buffer.  if < then buffer is null terminated.
 */
void mango_variable_set_value(MangoVariable *mvar, BOOL isQuoted, const char *buffer, int length)
{
    if (mvar->value != NULL)
    {
        mango_string_free(mvar->value);
    }
    mvar->value = mango_string_from_buffer(buffer, length);
    mvar->isQuoted  = isQuoted;
    mvar->isNumber  = false;
    mvar->intValue  = 0;
    // TODO: check if integer
}

/**
 * Resolves the value of a variable (for rendering purposes) given the
 * template and node contexts.
 */
int mango_variable_resolve(MangoVariable *mvar, MangoTemplateContext *context, MangoNodeContext *topContext, void **value)
{
    return 0;
}



#ifndef __MANGO_FILTER_H__
#define __MANGO_FILTER_H__

#include "mfwddefs.h"
#include "mvariable.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Value of a variable after a filter is applied.
 */
struct MangoValue
{
    int valueType;
    union
    {
        int             intValue;
        double          doubleValue;
        MangoString *   stringValue;
    } valueData;
};

/**
 * Filters get applied on variables in how they manipulate the value stored
 * in a variable.  We do not want to have multiple instances of the same
 * filter.  So it would be better to have a single instance of the filter
 * through out the application to save memory and their performance wouldnt
 * be bad either.  Since only a certain number of filter instances are
 * created to conserve memory, this implies that Filter objects cannot have
 * shared state or state specific to each invocation(of their render)
 * method.  This is for the sake of thread safety.
 *
 * So as an extension (at a later date), this restriction on shared or
 * invocation specific state can be relaxed by having a FilterContext
 * object associated with each filter if this is a paramount requirement.
 */
struct MangoFilter
{
    //! Fiter specific data.
    void *data;

    // Deletes the filter data
    void (*deleteFunc)(void *data);

    /**
     * Transforms the string and returns the rendered value.
     * The value is modified using the arguments and an optional filterContext.
     * The filterContext holds "softened" version of the arguments that it can use
     * on multiple invocations for the sake of efficiency.  For instance in an "add"
     * filter that would increment the value of an input string by some amount, 
     * it makes sense to cache the value as an integer instead of converting the
     * stringified argument on each render call!
     * @throws IOException 
     */
    int (*applyFunc)(void *filter_data, const MangoValue *input, MangoValue *output,
                     MangoTemplateContext *context, MangoList *arguments);

    //! Creates an invocation specific context
    void *(*makeInvocationContextFunc)(MangoList *arguments);

    //! Creates an invocation specific context
    void *(*makeInstanceContextFunc)(MangoList *arguments);
};

/**
 * Creates a new filter.
 */
extern MangoFilter *mango_filter_new(void *data);

/**
 * Resets the filter contents.
 */
extern void mango_filter_reset(MangoFilter *filter, void *data);

/**
 * Destroys a filter created with mango_filter_new.
 */
extern void mango_filter_free(MangoFilter *filter);

/**
 * Applies the filter on a value and returns the new value.
 * \param   filter      Filter being applied.
 * \param   inType      Input type
 * \param   inValue     Input value
 * \param   outValue    Output value.
 * \param   context     Template Context
 * \param   arguments   Arguments for the application.
 *
 * \return  Output type with the value stored in outValue.
 */
extern int mango_filter_apply(MangoFilter *filter,
                              const MangoValue *input,
                              MangoValue *output,
                              MangoTemplateContext *context,
                              MangoList *arguments);

#ifdef __cplusplus
}
#endif

#endif


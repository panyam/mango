
#include "mmemutils.h"
#include "mfilternode.h"
#include "mfilter.h"
#include "mvariable.h"
#include "mlist.h"
#include "mtemplatecontext.h"

/**
 * Creates a new filter node given a filter.
 */
MangoFilterNode *mango_filternode_new(const MangoFilter *f)
{
    MangoFilterNode *mfn = NEW(MangoFilterNode);
    mfn->filter = f;
    mfn->arguments = NULL;
    return mfn;
}

/**
 * Frees a filter node.
 */
void mango_filternode_free(MangoFilterNode *fnode)
{
    // do not delete filter as they are shared
    if (fnode->arguments != NULL)
    {
        mango_list_clear(fnode->arguments, (DeleteFunc)mango_variable_free);
        mango_list_free(fnode->arguments);
    }
    free(fnode);
}

/**
 * Tells if two filter nodes are equal.
 */
BOOL mango_filternodes_are_equal(const MangoFilterNode *fn1, const MangoFilterNode *fn2)
{
    if (fn1 == fn2)
    {
        return true;
    }
    else if (fn1 == NULL || fn2 == NULL)
    {
        return false;
    }
    else if (fn1->filter != fn2->filter)    // filter instances are shared
    {
        return false;
    }
    return mango_lists_are_equal(fn1->arguments, fn2->arguments, mango_variables_are_equal);
}

/**
 * Applies a filter arguments to a filter and returns the value.
 */
int mango_filternode_apply(MangoFilterNode *fnode, int inType, void *inValue, void **outValue, MangoTemplateContext *context)
{
    return mango_filter_apply(fnode->filter, inType, inValue, outValue, context, fnode->arguments);
}

/**
 * Adds an argument to a filter node.
 *
 * \param   fnode   Filter node to add the variable to.
 * \param   mvar    Argument to add.
 */
void mango_filternode_add_arg(MangoFilterNode *fnode, MangoVariable *mvar)
{
    if (fnode->arguments == NULL)
        fnode->arguments = mango_list_new();
    mango_list_push_back(fnode->arguments, mvar);
}


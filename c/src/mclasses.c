
#define _GNU_SOURCE
#include <string.h>
#include "mclasses.h"
#include "mbintree.h"
#include "mmemutils.h"

typedef struct MangoClass
{
    char *      className;
    unsigned    classId;
} MangoClass;

static MangoBinTree *mango_classes;

MangoClass *mango_class_new(const char *name, unsigned id)
{
    MangoClass *mclass  = NEW(MangoClass);
    mclass->className   = strdup(name);
    mclass->classId     = id;
    return mclass;
}

/**
 * Compares two mango classes using a lexicographical ordering of the class
 * names.
 */
int mango_class_compare(const void *a, const void *b)
{
    MangoClass *node1 = (MangoClass *)a;
    MangoClass *node2 = (MangoClass *)b;
    return strcmp(node1->className, node2->className);
}

/**
 * Gets the class for a given name, registering it if necessary.
 *
 * \param   name        Name of the object to be registered.
 * \param   register    Whether a class should be registered if it was not
 *                      found?
 *
 * \returns The class integer ID for the name, if it exists.  0 otherwise.
 */
int mango_class_for_name(const char *name, BOOL reg)
{
    if (mango_classes == NULL)
    {
        if (!reg)
            return 0;
        mango_classes = mango_bintree_new();
    }

    MangoClass mclass;
    mclass.className = (char *)name;

    MangoBinTreeNode *node = mango_bintree_find(mango_classes, &mclass, mango_class_compare);
    int classId = 0;
    if (node == NULL && reg)
    {
        classId = mango_bintree_size(mango_classes) + 1;
        MangoClass *newclass = mango_class_new(name, classId);
        node = mango_bintree_insert(mango_classes, newclass, mango_class_compare);
    }
    else
    {
        classId = ((MangoClass *)node->data)->classId;
    }
    return classId;
}

/**
 * Gets the name of a class given its class ID.
 * \param   cls Class whose string name is to be returned.
 */
const char *mango_name_for_class(int cls)
{
    return "";
}


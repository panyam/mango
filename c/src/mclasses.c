
#include "mclasses.h"
#include "uthash.h"

typedef struct MangoClass
{
    unsigned    classId;
    const char *className;
    UT_hash_handle  hh;
} MangoClass;

static MangoClass * mango_classes = NULL;
static  int         mango_class_count = 0;

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
    if (mango_classes == NULL && !reg)
        return 0;
    return 0;
}

/**
 * Gets the name of a class given its class ID.
 * \param   cls Class whose string name is to be returned.
 */
const char *mango_name_for_class(int cls)
{
    return "";
}


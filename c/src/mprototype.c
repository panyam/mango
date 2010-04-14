
#include "mprototype.h"
#include "mmemutils.h"
#include "mbintree.h"

static MangoBinTree *mango_prototypes;

/**
 * Creates a new prototype object with a given name.
 * \param   name    Name of the prototype.
 * \return  The new prototype instance.
 */
MangoPrototype *mango_prototype_new(const char *name)
{
    MangoPrototype *proto = ZNEW(MangoPrototype);
    proto->name = strdup(name == NULL ? "" : name);
    return proto;
}

/**
 * Compares two prototypes.
 * They are equal if their names are equal.
 */
int mango_prototype_compare(const void *a, const void *b)
{
    MangoPrototype *proto1 = (MangoPrototype *)a;
    MangoPrototype *proto2 = (MangoPrototype *)b;
    return strcmp(proto1->name, proto2->name);
}

/**
 * Gets the prototype for a given name, registering it if necessary.
 *
 * \param   name        Name of the prototype to be registered.
 * \param   register    Whether a class should be registered if it was not
 *                      found?
 *
 * \returns The class integer ID for the name, if it exists.  0 otherwise.
 */
const MangoPrototype *mango_prototype_for_name(const char *name, BOOL reg)
{
    if (mango_prototypes == NULL)
    {
        if (!reg)
            return 0;
        mango_prototypes = mango_bintree_new();
    }

    MangoPrototype mproto;
    mproto.name = (char *)name;

    MangoBinTreeNode *node = mango_bintree_find(mango_prototypes,
                                                &mproto,
                                                mango_prototype_compare);
    if (node == NULL && reg)
    {
        MangoPrototype *newclass = mango_prototype_new(name);
        node = mango_bintree_insert(mango_prototypes, newclass, mango_prototype_compare);
    }
    return node == NULL ? NULL : (MangoPrototype *)node->data;
}


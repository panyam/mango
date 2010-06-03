
#include "mangopub.h"

/**
 * Stores the non-interface data for a prototype.
 */
struct MangoPrototypeInfo
{
    /**
     * Name of the prototype.
     */
    const char *        name;

    /**
     * ID of the prototype.
     */
    int                 protoID;

    /**
     * Size in bytes of the prototype.
     */
    size_t              protoSize;

    /**
     * ID of the parent prototype if any.
     */
    MangoPrototypeInfo *parent;
};

/**
 * All prototypes by name.
 */
static int numPrototypes = 0;

/**
 * Creates a new mango prototype info.
 * \param   size    Size of the Prototype structure.
 * \param   parent  Parent prototype (NULL if none).
 * \return NULL if name already exists, otherwise a new Prototype.  No
 * duplicates allowed.
 */
MangoPrototypeInfo *mango_protoinfo_new(size_t size, MangoPrototypeInfo *parent)
{
    MangoPrototypeInfo *proto   = ZNEW(MangoPrototypeInfo);
    proto->name                 = NULL;
    proto->protoID              = numPrototypes++;
    proto->protoSize            = size;
    proto->parent               = parent;
    return proto;
}

/**
 * Returns the default mango prototype.
 */
DECLARE_PROTO_FUNC(mango_default_prototype, MangoPrototype, NULL);

/**
 * Initialises a prototype object with a name and default methods.
 * \param   proto       Prototype type object to initialise.
 * \param   size        Size of the prototype.
 * \param   parent      Parent of the prototype if any.
 */
void mango_prototype_inherit(MangoPrototype *proto, size_t size, MangoPrototype *parent)
{
    if (proto != NULL)
    {
        // copy all methods from the parent to the child prototype
        memcpy(proto, parent, parent->protoinfo->protoSize);
    }
    proto->protoinfo        = mango_protoinfo_new(size, parent->protoinfo);
}


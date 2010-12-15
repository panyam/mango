
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
     * Level in the prototype hiearchy starting from the root.
     */
    int                 protoLevel;

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
    proto->parent               = parent;
    proto->protoID              = numPrototypes++;
    proto->protoSize            = size;
    proto->protoLevel           = parent == NULL ? 0 : parent->protoLevel + 1;
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
    if (parent != NULL)
    {
        // copy all methods from the parent to the child prototype
        memcpy(proto, parent, parent->protoinfo->protoSize);
    }
    proto->protoinfo        = mango_protoinfo_new(size, parent == NULL ? NULL : parent->protoinfo);
}


/**
 * Tells if two prototypes can be casted to each other.
 *
 * \param   proto1  First prototype.
 * \param   proto2  Second prototype.
 * \return  true if proto1 and proto2 can be casted to each other.
 */
BOOL mango_prototype_implements(MangoPrototype *proto1, MangoPrototype *proto2)
{
    MangoPrototypeInfo *protoInfo1 = proto1->protoinfo;
    MangoPrototypeInfo *protoInfo2 = proto2->protoinfo;

    if (protoInfo1->protoLevel < protoInfo2->protoLevel)
    {
        MangoPrototypeInfo *ptemp = protoInfo1;
        protoInfo1 = protoInfo2;
        protoInfo2 = ptemp;
    }

    // only bother doing this if level of first proto is lower than
    // level of second proto
    for (MangoPrototypeInfo *temp = protoInfo1; temp != NULL && temp->protoLevel >= protoInfo2->protoLevel;temp = temp->parent)
    {
        if (temp == protoInfo2)
            return true;
    }
    return false;
}



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
     * ID of the parent prototype if any.
     */
    MangoPrototypeInfo *parent;
};

/**
 * All prototypes by name.
 */
static MangoBinTree *   mango_protos_by_name = NULL;

MangoPrototypeInfo *mango_protoinfo_new(const char *name, const char *parent);
MangoPrototypeInfo *mango_protoinfo_for_name(const char *name);

/**
 * Creates a new mango prototype info.
 * \param   name    Name of the new prototype to create.
 * \param   parent  Parent prototype (NULL if none).
 * \return NULL if name already exists, otherwise a new Prototype.  No
 * duplicates allowed.
 */
MangoPrototypeInfo *mango_protoinfo_new(const char *name, const char *parent)
{
    if (mango_protoinfo_for_name(name) != NULL)
    {
        assert("Prototype is already registered.  Please use a different name." && false);
        return NULL;
    }

    if (mango_protos_by_name == NULL)
    {
        mango_protos_by_name = mango_bintree_new();
    }

    return NULL;
}

/**
 * Return the prototype corresponding to a particular name.
 */
MangoPrototypeInfo *mango_protoinfo_for_name(const char *name)
{
    return NULL;
}

/**
 * Returns the default mango prototype.
 */
MangoPrototype *mango_default_prototype()
{
    static MangoPrototype __proto__;
    static BOOL initialised = false;
    if (!initialised)
    {
        memset(&__proto__, 0, sizeof(__proto__));
        __proto__.protoinfo = mango_protoinfo_new("MangoPrototype", NULL);
        initialised = true;
    }
    return &__proto__;
}

/**
 * Initialises a prototype object with a name and default methods.
 * \param   proto       Prototype type object to initialise.
 * \param   name        Name of the prototype.
 * \return  true if initialisation went well, false if name is already
 * registered.
 */
BOOL mango_prototype_init(MangoPrototype * proto, const char *name, const char *parent)
{
    proto->protoinfo        = mango_protoinfo_new(name, parent);
    proto->deallocFunc      = NULL;
    proto->equalsFunc       = NULL;
    proto->compareFunc      = NULL;
    proto->getIntAttrFunc   = NULL;
    proto->getStrAttrFunc   = NULL;
    proto->hasIntAttrFunc   = NULL;
    proto->hasStrAttrFunc   = NULL;
    proto->iterFunc         = NULL;
    return true;
}

/**
 * Gets the ID for a particular name creating it if requested to.
 * \param   name    Name of the prototype to search for.
 * \param   create  If not found whether to create it.
 * \return  id of the prototype if it exists or was created, -1 otherwise.
 */
int mango_prototype_id_for_name(const char *name, BOOL create)
{
    return -1;
}

/**
 * Gets the ID for a particular name creating it if requested to.
 * \param   id      ID of the prototype whose name we want.
 * \return  The name of a prototype that matches the ID, NULL if none
 * exist.
 */
const char *mango_prototype_name_for_id(int id)
{
    return NULL;
}

/**
 * Tells if a prototype is either a base or a child of a given prototype.
 */
BOOL mango_prototype_is_of_type(MangoPrototype *proto, const char *name)
{
    return false;
}


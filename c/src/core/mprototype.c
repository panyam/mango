
#include "mangopub.h"

/**
 * Returns the default prototype object.
 */
DECLARE_PROTO_FUNC("MangoPrototype", MangoPrototype, mango_object_prototype);

/**
 * Initialises a prototype object with a name and default methods.
 * \param   proto       Prototype type object to initialise.
 * \param   name        Name of the prototype.
 * \param   parentID    ID of the parent prototype.
 * \return  The initialised prototype instance.
 */
MangoPrototype *mango_prototype_init(MangoPrototype * proto, const char *name, int parentID)
{
    proto->parentProtoID    = parentID;
    proto->protoID          = mango_prototype_id_for_name(name, true);
    proto->deallocFunc      = NULL;
    proto->equalsFunc       = NULL;
    proto->compareFunc      = NULL;
    proto->getIntAttrFunc   = NULL;
    proto->getStrAttrFunc   = NULL;
    proto->hasIntAttrFunc   = NULL;
    proto->hasStrAttrFunc   = NULL;
    proto->iterFunc         = NULL;
    return proto;
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


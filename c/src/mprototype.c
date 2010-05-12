
#include "mprototype.h"
#include "mmemutils.h"
#include "mbintree.h"

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


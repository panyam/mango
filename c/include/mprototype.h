
#ifndef __MANGO_PROTOTYPE_H__
#define __MANGO_PROTOTYPE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prototypes are the blueprints for objects.  Almost like classes.
 */
struct MangoPrototype
{
    /**
     * Name of the prototype.
     */
    char *name;

    /**
     * Deletes object data for this object.
     */
    void (*deleteObjectData)(void *objData);

    /**
     * Tells if the data of two objects are equal.
     */
    BOOL (*objectDataEquals)(const void *objData1, const void *objData2);

    /**
     * Compares the data of two objects.
     */
    int (*compareObjectData)(const void *objData1, const void *objData2);
};

/**
 * Gets the prototype for a given name, registering it if necessary.
 *
 * \param   name        Name of the prototype to be registered.
 * \param   register    Whether a class should be registered if it was not
 *                      found?
 *
 * \returns The class integer ID for the name, if it exists.  0 otherwise.
 */
extern const MangoPrototype *mango_prototype_for_name(const char *name, BOOL reg);

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_PROTOTYPE_H__
#define __MANGO_PROTOTYPE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*PrototypeIncRefFunc)(MangoObject *object);
typedef void (*PrototypeDecRefFunc)(MangoObject *object);
typedef void (*PrototypeCleanUpFunc)(MangoObject *object);
typedef BOOL (*PrototypeEqualsFunc)(const MangoObject *obj1, const MangoObject *obj2);
typedef int (*PrototypeCompareFunc)(const MangoObject *obj1, const MangoObject *obj2);

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
     * Called when reference is to be incremented.
     */
    void (*incRefFunc)(MangoObject *object);

    /**
     * Called when reference is to be decremented.
     */
    void (*decRefFunc)(MangoObject *object);

    /**
     * Called when reference reaches 0.
     */
    void (*cleanUpFunc)(MangoObject *object);

    /**
     * Tells if two objects are equal.
     */
    BOOL (*equalsFunc)(const MangoObject *obj1, const MangoObject *obj2);

    /**
     * Compares the data of two objects.
     */
    int (*compareFunc)(const MangoObject *obj1, const MangoObject *obj2);
};

#define DECLARE_PROTOTYPE(PROTO_NAME, BASE_PROTO_NAME, ...) \
    struct PROTO_NAME                                       \
    {                                                       \
        /**                                                 \
         * Base prototype.                                  \
         */                                                 \
        BASE_PROTO_NAME __base__;                           \
                                                            \
        __VA_ARGS__                                         \
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
extern const MangoPrototype *mango_prototype_for_name(const char *name, BOOL reg);

#ifdef __cplusplus
}
#endif

#endif


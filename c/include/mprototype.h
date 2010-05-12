
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
typedef void (*PrototypeCopyFunc)(const MangoObject *src, MangoObject *dest);

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
     * Called when reference reaches 0 and the destructor needs to be
     * called.
     */
    void (*deleteFunc)(MangoObject *object);

    /**
     * Tells if two objects are equal.
     */
    BOOL (*equalsFunc)(const MangoObject *obj1, const MangoObject *obj2);

    /**
     * Compares the data of two objects.
     */
    int (*compareFunc)(const MangoObject *obj1, const MangoObject *obj2);
};

#define DECLARE_PROTOTYPE(PROTO_NAME, BASE_PROTO_NAME, ...)     INHERIT_CLASS(PROTO_NAME, BASE_PROTO_NAME, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_OBJECT_H__
#define __MANGO_OBJECT_H__

#include "mprototype.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoObject
{
    /**
     * Prototype for the object.
     */
    const MangoPrototype *  prototype;

    /**
     * Object's reference count.
     */
    int objRefCount;

    /**
     * Object specific data.
     */
    void *objData;
};

#define DECLARE_CLASS(CLASS_NAME, ...)              \
    struct CLASS_NAME                               \
    {                                               \
        /**                                         \
         * Prototype for the object.                \
         */                                         \
        const MangoPrototype *  prototype;          \
                                                    \
        /**                                         \
         * Object's reference count.                \
         */                                         \
        int objRefCount;                            \
                                                    \
        __VA_ARGS__                                 \
    }


/**
 * Creates a mango object with default methods.
 */
extern MangoObject *mango_object_new(void *objData);

/**
 * Destroys a mango object.
 */
extern void mango_object_free(MangoObject *obj);

/**
 * Compares two objects to see if they are equal.
 *
 * \param   obj1    First obj in the comparison.
 * \param   obj2    Second obj in the comparison.
 *
 * \return  true if objects are equal (as defined by their objDataEquals
 * callback), false otherwise.
 */
extern BOOL mango_objects_are_equal(const MangoObject *obj1, const MangoObject *obj2);

#ifdef __cplusplus
}
#endif

#endif


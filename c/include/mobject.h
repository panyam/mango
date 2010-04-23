
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
    int refCount;
};

#define DECLARE_CLASS(CLASS_NAME, BASE_CLASS_NAME, ...)     \
    struct CLASS_NAME                                       \
    {                                                       \
        /**                                                 \
         * Base object.                                     \
         */                                                 \
        BASE_CLASS_NAME __base__;                           \
                                                            \
        __VA_ARGS__                                         \
    }

/**
 * Releases a reference to the object.
 * \returns false if the object's reference count has reached 0 and has been
 * deleted and is no longer valid, true otherwise.
 */
extern BOOL mango_object_release(MangoObject *obj);

/**
 * Increases the reference count to an object.
 * \param   obj Object whose reference count is to be increased.
 * \return  Pointer to the same object to simplify copy semantics.
 */
extern MangoObject *mango_object_copy(MangoObject *obj);

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

/**
 * Compares two objects to check their relative order.
 *
 * \param   obj1    First obj in the comparison.
 * \param   obj2    Second obj in the comparison.
 *
 * \return  -ve if obj1 < obj2, 0 if they are equal, +ve otherwise
 */
extern int mango_object_compare(const MangoObject *obj1, const MangoObject *obj2);

#ifdef __cplusplus
}
#endif

#endif


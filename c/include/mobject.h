
#ifndef __MANGO_OBJECT_H__
#define __MANGO_OBJECT_H__

#include "mprototype.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Declares a class of name CLASS_NAME, which has a specific prototype and
 * a reference count.
 */
#define DECLARE_CLASS(CLASS_NAME, PROTOTYPE_NAME, ...)  \
    struct CLASS_NAME                                   \
    {                                                   \
        /**                                             \
         * Base prototype.                              \
         */                                             \
        PROTOTYPE_NAME *__prototype__;                  \
                                                        \
        /**                                             \
         * object reference count.                      \
         */                                             \
        int __refCount__;                               \
                                                        \
        /**                                             \
         * The object specific data.                    \
         */                                             \
        __VA_ARGS__                                     \
    }

/**
 * "Inherits" a struct by including an instance of it as the first member of
 * the new struct.
 */
#define INHERIT_CLASS(CLASS_NAME, BASE_CLASS, ...)      \
    struct CLASS_NAME                                   \
    {                                                   \
        /**                                             \
         * Base class                                   \
         */                                             \
        BASE_CLASS __base__;                            \
                                                        \
        /**                                             \
         * The object specific data.                    \
         */                                             \
        __VA_ARGS__                                     \
    }

// CREATE_OBJECT(OBJ_CLASS, PROTO_CLASS);

/**
 * Default class of all objects.
 */
DECLARE_CLASS(MangoObject, MangoPrototype);

/**
 * Increases the reference count to an object.
 * \param   obj Object whose reference count is to be increased.
 * \return  Pointer to the same object to simplify copy semantics.
 */
extern MangoObject *mango_object_copy(MangoObject *obj);

/**
 * Releases a reference to the object.
 * \returns false if the object's reference count has reached 0 and has
 * been deleted and is no longer valid, true otherwise.
 */
extern BOOL mango_object_release(MangoObject *obj);

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


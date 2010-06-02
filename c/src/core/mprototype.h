

#ifndef __MANGO_PROTOTYPE_H__
#define __MANGO_PROTOTYPE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * "Inherits" a struct by including an instance of it as the first member of
 * the new struct.
 */
#define INHERIT_STRUCT(STRUCT_NAME, BASE_STRUCT, ...)   \
    struct STRUCT_NAME                                  \
    {                                                   \
        /**                                             \
         * Base class                                   \
         */                                             \
        BASE_STRUCT __base__;                           \
                                                        \
        /**                                             \
         * The object specific data.                    \
         */                                             \
        __VA_ARGS__                                     \
    }

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
 * Macro for generating a function that returns a specific prototype
 * object.
 */
#define DECLARE_PROTO_FUNC(VAR_CLASS_ID, VAR_TYPE, VAR_FUNC, ...)                   \
    VAR_TYPE *VAR_FUNC() {                                                          \
        static VAR_TYPE __proto__;                                                  \
        static BOOL initialised = false;                                            \
        if (!initialised)                                                           \
        {                                                                           \
            bzero(&__proto__, sizeof(__proto__));                                   \
            mango_prototype_init((MangoPrototype *)(&__proto__), VAR_CLASS_ID);     \
            __VA_ARGS__                                                             \
            initialised = true;                                                     \
        }                                                                           \
        return &__proto__;                                                          \
    }                                                                               \

/**
 * Set of Prototype related methods.
 */
typedef void (*ObjectDeallocFunc)(MangoObject *object);
typedef BOOL (*ObjectEqualsFunc)(const MangoObject *obj1, const MangoObject *obj2);
typedef int (*ObjectCompareFunc)(const MangoObject *obj1, const MangoObject *obj2);
typedef MangoObject *(*ObjectGetIntAttrFunc)(const MangoObject *obj, int index);
typedef MangoObject *(*ObjectGetStrAttrFunc)(const MangoObject *obj, const MangoString *key);
typedef BOOL (*ObjectHasIntAttrFunc)(const MangoObject *obj, int index);
typedef BOOL (*ObjectHasStrAttrFunc)(const MangoObject *obj, const MangoString *key);
typedef MangoIterator *(*ObjectIteratorFunc)(const MangoObject *obj);

/**
 * Prototypes are the blueprints for objects.  Almost like classes.
 */
struct MangoPrototype
{
    /**
     * ID of the prototype.  These are unique across all prototypes in the
     * system.  No two prototypes can have the same ID.
     */
    int protoID;

    /**
     * ID of the parent prototype.
     */
    int parentProtoID;

    /**
     * Called when reference reaches 0 and the destructor/deallocator needs
     * to be called.
     */
    void (*deallocFunc)(MangoObject *object);

    /**
     * Tells if two objects are equal.
     */
    BOOL (*equalsFunc)(const MangoObject *obj1, const MangoObject *obj2);

    /**
     * Compares the data of two objects.
     */
    int (*compareFunc)(const MangoObject *obj1, const MangoObject *obj2);

    /**
     * Gets an attribute of this object given an integer index.
     */
    MangoObject *(*getIntAttrFunc)(const MangoObject *obj, int index);

    /**
     * Gets an attribute of this object given a key.
     */
    MangoObject *(*getStrAttrFunc)(const MangoObject *obj, const MangoString *key);

    /**
     * Tells if the object can return a an attribute value for an integer
     * index.
     */
    BOOL (*hasIntAttrFunc)(const MangoObject *obj, int index);

    /**
     * Tells if the object can return a an attribute value for a key.
     */
    BOOL (*hasStrAttrFunc)(const MangoObject *obj, const MangoString *key);

    /**
     * Gets the iterator for the object if any.
     */
    MangoIterator *(*iterFunc)(MangoObject *obj);
};

#ifdef __cplusplus
}
#endif

#endif


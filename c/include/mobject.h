
#ifndef __MANGO_OBJECT_H__
#define __MANGO_OBJECT_H__

#include "mfwddefs.h"
#include <stdarg.h>

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


#define DECLARE_PROTO_VARIABLE(VAR_CLASS_ID, VAR_TYPE, VAR_NAME, ...)       \
    static VAR_TYPE VAR_NAME;                                               \
    static BOOL initialised = false;                                        \
    if (!initialised)                                                       \
    {                                                                       \
        mango_prototype_init((MangoProperty *)(&VAR_NAME), VAR_CLASS_ID);   \
        __VA_ARGS__                                                         \
        initialised = true;                                                 \
    }                                                                       \
    return &VAR_NAME;                                                       \

/**
 * Set of Prototype related methods.
 */
typedef void (*PrototypeDeallocFunc)(MangoObject *object);
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
};

/**
 * Default class of all objects.
 */
DECLARE_CLASS(MangoObject, MangoPrototype);

/**
 * A function for initialising an object.
 */
typedef void (*ObjectInitFunc)(MangoObject *obj, ...);

/**
 * Invokes an (quasi) object allocator.
 */
#define OBJ_ALLOC(OBJ_CLASS, proto)   (OBJ_CLASS *)mango_object_alloc(sizeof(OBJ_CLASS), (MangoPrototype *)proto)

/**
 * Initialises a mango object's refcount and prototype.
 */
#define OBJ_INIT(obj, proto)   mango_object_init(obj, proto)

/**
 * Invokes an initialiser function on a mango object.
 */
#define OBJ_INIT_WITH_FUNC(OBJ, INIT_FUNC, ...)   mango_object_init_with_func(OBJ, INIT_FUNC __VA_ARGS__)

/**
 * Increase an object's reference count.
 */
#define OBJ_INCREF(obj) mango_object_incref((MangoObject *)obj)

/**
 * Decrease an object's reference count.
 */
#define OBJ_DECREF(obj) mango_object_decref((MangoObject *)obj)

/**
 * Invokes an (quasi) object allocator followed by an initialiser.
 */
#define OBJ_NEW(OBJ_CLASS, proto, initFunc, ...)   (OBJ_CLASS *)mango_object_alloc(sizeof(OBJ_CLASS), proto, initFunc __VA_ARGS__)

/**
 * Create a new prototype object of a given name.
 */
extern MangoPrototype *mango_prototype_init(MangoPrototype *, const char *name);

/**
 * Allocate an object of a given size with a prototype.
 */
extern MangoObject *mango_object_alloc(size_t objSize, MangoPrototype *proto);

/**
 * Initialises an already created mango object.
 * \param   obj     Object to be initialised.
 * \param   proto   Object's prototype to be set as.
 * \return  Pointer to the same object to simplify copy semantics.
 */
extern MangoObject *mango_object_init(MangoObject *obj, MangoPrototype *proto);

/**
 * An object initializer.  The object must be allocated first (perhaps with
 * mango_object_alloc) or initialised with mango_object_init.
 * \param   obj         Object to be initialised.
 * \param   initFunc    INitialiser function to be called on the object.
 * \param   ...         Variable arguments passed to the initialiser function.
 * \return  Pointer to the same object to simplify copy semantics.
 */
extern MangoObject *mango_object_init_with_func(MangoObject *obj, ObjectInitFunc initFunc, ...);

/**
 * Clones an object.
 * \param   obj     Object that needs to be cloned.
 * \return  Returns a new object that is a clone of the original object.
 * The semantics of the cloning are that the returned object has its
 * reference count set to 1 and the original object's reference count is
 * not changed.
 */
// extern MangoObject *mango_object_clone(MangoObject *obj);

/**
 * Increases the reference count to an object.
 * \param   obj Object whose reference count is to be increased.
 * \return  Pointer to the same object to simplify copy semantics.
 */
extern MangoObject *mango_object_incref(MangoObject *obj);

/**
 * Releases a reference to the object.
 * \returns false if the object's reference count has reached 0 and has
 * been deleted and is no longer valid, true otherwise.
 */
extern BOOL mango_object_decref(MangoObject *obj);

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


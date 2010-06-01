
#ifndef __MANGO_OBJECT_H__
#define __MANGO_OBJECT_H__

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
#define DECLARE_PROTO_FUNC(VAR_CLASS_ID, VAR_TYPE, VAR_FUNC, ...)               \
    VAR_TYPE *VAR_FUNC() {                                                      \
        static VAR_TYPE __proto__;                                              \
        static BOOL initialised = false;                                        \
        if (!initialised)                                                       \
        {                                                                       \
            bzero(&__proto__, sizeof(__proto__));                               \
            mango_prototype_init((MangoPrototype *)(&__proto__),                \
                                 VAR_CLASS_ID, sizeof(__proto__));              \
            __VA_ARGS__                                                         \
            initialised = true;                                                 \
        }                                                                       \
        return &__proto__;                                                      \
    }                                                                           \

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
     * Name of the prototype.
     */
    char *name;

    /**
     * Size of the proto struct.
     */
    size_t  size;

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

/**
 * Default class of all objects.
 */
DECLARE_CLASS(MangoObject, MangoPrototype);

/**
 * A function for initialising an object.
 */
typedef void (*ObjectInitFunc)(MangoObject *obj, ...);

/**
 * Create a new prototype object of a given name.
 *
 * @test(TestPrototypeInit)
 * MangoPrototype proto;
 * mango_prototype_init(&proto, "Hello", sizeof(proto));
 * CHECK_EQUAL(sizeof(proto), proto.size);
 * CHECK(strcmp(proto.name, "Hello") == 0);
 * free(proto.name);
 * @endtest
 */
extern MangoPrototype *mango_prototype_init(MangoPrototype *, const char *name, size_t size);

/**
 * Returns the default mango prototype.
 */
extern MangoPrototype *mango_prototype_default();

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
 * Deallocates an object.
 */
extern void mango_object_dealloc(MangoObject *obj);

/**
 * Increases the reference count to an object.
 * \param   obj Object whose reference count is to be increased.
 * \return  Pointer to the same object to simplify copy semantics.
 *
 * @test(TestObjectIncDecRef, suite = "ObjectTests")
 * MangoObject *obj = OBJ_ALLOC(MangoObject, mango_prototype_default());
 * CHECK_EQUAL(1, OBJ_REFCOUNT(obj));
 * CHECK_EQUAL(2, OBJ_REFCOUNT(OBJ_INCREF(obj)));
 * CHECK_EQUAL(3, OBJ_REFCOUNT(OBJ_INCREF(obj)));
 * CHECK_EQUAL(true, OBJ_DECREF(obj)); 
 * CHECK_EQUAL(2, OBJ_REFCOUNT(obj));
 *
 * CHECK_EQUAL(true, OBJ_DECREF(obj)); 
 * CHECK_EQUAL(1, OBJ_REFCOUNT(obj));
 * CHECK_EQUAL(false, OBJ_DECREF(obj));
 * @endtest
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

/**
 * Gets an attribute of this object given an integer index.
 */
MangoObject *mango_object_get_int_attr(const MangoObject *obj, int index);

/**
 * Gets an attribute of this object given a key.
 */
MangoObject *mango_object_get_str_attr(const MangoObject *obj, const MangoString *key);

/**
 * Tells if the object can return a an attribute value for an integer
 * index.
 */
BOOL mango_object_has_int_attr(const MangoObject *obj, int index);

/**
 * Tells if the object can return a an attribute value for a key.
 */
BOOL mango_object_has_str_attr(const MangoObject *obj, const MangoString *key);

/**
 * Get an iterator for an object.
 */
extern MangoIterator *mango_object_iterator(MangoObject *obj);

/**
 * Utils on the object stuff.
 */
#include "utils/mutils.h"

#ifdef __cplusplus
}
#endif

#endif


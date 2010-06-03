

#ifndef __MANGO_PROTOTYPE_H__
#define __MANGO_PROTOTYPE_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

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
     * Prototype meta data.
     */
    MangoPrototypeInfo *protoinfo;

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
 * Macro for generating a function that returns a prototype that is
 * inheriting another prototype.
 */
#define DECLARE_BASE_PROTO_FUNC(VAR_FUNC, BASE_PROTO_TYPE, VAR_TYPE, ...)   \
    VAR_TYPE *VAR_FUNC() {                                                  \
        static VAR_TYPE __proto__;                                          \
        static BOOL initialised = false;                                    \
        if (!initialised)                                                   \
        {                                                                   \
            bzero(&__proto__, sizeof(__proto__));                           \
            mango_prototype_init((MangoPrototype *)(&__proto__),            \
                                 #VAR_TYPE, #BASE_PROTO_TYPE);              \
            __VA_ARGS__                                                     \
            initialised = true;                                             \
        }                                                                   \
        return &__proto__;                                                  \
    }                                                                       \

/**
 * Macro for generating a function that returns a prototype that is
 * not inheriting but only overriding certain methods of a prototype.
 */
#define DECLARE_PROTO_FUNC(VAR_FUNC, VAR_TYPE, NEW_PROTO_TYPE, ...)         \
    VAR_TYPE *VAR_FUNC() {                                                  \
        static VAR_TYPE __proto__;                                          \
        static BOOL initialised = false;                                    \
        if (!initialised)                                                   \
        {                                                                   \
            bzero(&__proto__, sizeof(__proto__));                           \
            mango_prototype_init((MangoPrototype *)(&__proto__),            \
                                 #NEW_PROTO_TYPE, #VAR_TYPE);               \
            __VA_ARGS__                                                     \
            initialised = true;                                             \
        }                                                                   \
        return &__proto__;                                                  \
    }                                                                       \

/**
 * Returns the default mango prototype.
 */
extern MangoPrototype *mango_default_prototype();

/**
 * Create a new prototype object of a given name.
 *
 * @test(TestPrototypeInit)
 * MangoPrototype proto;
 * CHECK(mango_prototype_init(&proto, "Hello", "World"));
 * @endtest
 */
extern BOOL mango_prototype_init(MangoPrototype *proto, const char *name, const char *parent);

/**
 * Gets the ID for a particular name creating it if requested to.
 * \param   name    Name of the prototype to search for.
 * \param   create  If not found whether to create it.
 * \return  id of the prototype if it exists or was created, -1 otherwise.
 */
extern int mango_prototype_id_for_name(const char *name, BOOL create);

/**
 * Tells if a prototype is either a base or a child of a given prototype.
 */
extern BOOL mango_prototype_is_of_type(MangoPrototype *proto, const char *name);

#ifdef __cplusplus
}
#endif

#endif


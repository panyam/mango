
#ifndef __MANGO_UTILS_H__
#define __MANGO_UTILS_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Tells if a string is an integer, optionally returning the integer value
 * if it is an integer.
 *
 * \param   buffer      The buffer that is being checked.
 * \param   length      Length of the buffer (if -ve, then it is a null
 *                      terminated string).
 * \param   outValue    Stores the int value (if not NULL).
 *
 * \return  true if the value is an integer, false otherwise.  If value is
 * an integer and outValue is non-null then the int value is stored in
 * outValue.
 */
extern BOOL is_integer(const char *buffer, int length, int *outValue);

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Inlined Macro Functions
///////////////////////////////////////////////////////////////////////////////////////////////////

// For more in inlining see - http://www.greenend.org.uk/rjk/2003/03/inline.html

/**
 * Invokes an (quasi) object allocator.
 */
#define OBJ_ALLOC(OBJ_CLASS, proto) (OBJ_CLASS *)mango_object_alloc(sizeof(OBJ_CLASS), (MangoPrototype *)proto)

/**
 * Casts a void* to an object.
 */
// extern inline MangoObject *OBJ(void *obj) { return (MangoObject *)obj; }
#define OBJ(x)      ((MangoObject *)(x))

/**
 * Initialises a mango object's refcount and prototype.
 */
// extern inline MangoObject *OBJ_INIT(void *obj, void *proto) { return mango_object_init(OBJ(obj), (MangoPrototype *)proto); }
#define OBJ_INIT(obj, proto)        mango_object_init(OBJ(obj), (MangoPrototype *)proto)

/**
 * Gets an object's reference count
 */
#define OBJ_REFCOUNT(obj)           (OBJ((obj))->__refCount__)

/**
 * Increase an object's reference count.
 */
#define OBJ_INCREF(obj)             (__typeof__(obj))mango_object_incref((MangoObject *)(obj))

/**
 * Decrease an object's reference count.
 */
#define OBJ_DECREF(obj)             mango_object_decref((MangoObject *)(obj))

/**
 * Compares two MangoObject derived objects.
 */
#define OBJ_EQUALS(obj1, obj2)      mango_objects_are_equal((MangoObject *)(obj1), (MangoObject *)(obj2))

/**
 * Compares two MangoObject derived objects.
 */
#define OBJ_COMPARE(obj1, obj2)     mango_object_compare((MangoObject *)(obj1), (MangoObject *)(obj2))

/**
 * Tells if an object is instance of a particular prototype.
 */
#define OBJ_INSTANCEOF(obj, proto)  mango_object_instanceof((MangoObject *)(obj), (const MangoPrototype *)proto)

/**
 * Gets attribute of an object given an integer index.
 */
#define OBJ_GETINTATTR(obj, index)  mango_object_get_int_attr((MangoObject *)(obj), index)

/**
 * Gets attribute of an object given a key.
 */
#define OBJ_GETSTRATTR(obj, key)    mango_object_get_str_attr((MangoObject *)(obj), key)

/**
 * Tells whether an attribute of an object given an integer index exists.
 */
#define OBJ_HASINTATTR(obj, index)  mango_object_has_int_attr((MangoObject *)(obj), index)

/**
 * Tells whether an attribute of an object given a key exists.
 */
#define OBJ_HASSTRATTR(obj, key)    mango_object_has_str_attr((MangoObject *)(obj), key)

#ifdef __cplusplus
}
#endif

#endif



#ifndef __MANGO_OBJECT_H__
#define __MANGO_OBJECT_H__

#include "mprototype.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Default class of all objects.
 */
DECLARE_CLASS(MangoObject, MangoPrototype);

/**
 * Returns the default mango prototype.
 */
extern MangoPrototype *mango_object_prototype();

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
 * MangoObject *obj = OBJ_ALLOC(MangoObject, mango_object_prototype());
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


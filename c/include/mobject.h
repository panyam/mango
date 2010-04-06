
#ifndef __MANGO_OBJECT_H__
#define __MANGO_OBJECT_H__

#include "mfwddefs.h"

struct MangoObject
{
    /**
     * Class of the object.
     */
    int objClass;

    /**
     * Object specific data.
     */
    void *objData;

    /**
     * Object's reference count.
     */
    int objRefCount;

    /**
     * Deletes object data for this object.
     */
    void (*deleteObjectData)(void *objData);

    /**
     * Tells if the data of two objects are equal.
     */
    BOOL (*objectDataEquals)(const void *objData1, const void *objData2);

    /**
     * Compares the data of two objects.
     */
    int (*compareObjectData)(const void *objData1, const void *objData2);
};

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

#endif


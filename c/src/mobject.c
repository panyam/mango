#include "mobject.h"
#include "mmemutils.h"
#include "mclasses.h"

void default_delete_object_data(void *objData);
int  default_object_compare(const void *objdata1, const void *objdata2);
BOOL default_objects_are_equal(const void *objdata1, const void *objdata2);

/**
 * Creates a object with default methods.
 */
MangoObject *mango_object_new(MangoPrototype *proto, void *objData)
{
    MangoObject *obj        = ZNEW(MangoObject);
    obj->prototype          = proto;
    obj->refCount           = 1;
    obj->objData            = objData;
    return obj;
}

/**
 * Increases the reference count of the object and returns int.
 */
MangoObject *mango_object_retain(MangoObject *obj)
{
    obj->refCount++;
    return obj;
}

/**
 * Decreases the reference count of the object and returns int.
 */
BOOL mango_object_release(MangoObject *obj)
{
    obj->refCount--;
    if (obj->refCount == 0)
    {
        mango_object_free(obj);
        return false;
    }
    return true;
}

/**
 * Destroys a mango object.
 */
void mango_object_free(MangoObject *obj)
{
    if (obj->objData != NULL && obj->prototype->deleteObjectData != NULL)
    {
        obj->prototype->deleteObjectData(obj->objData);
    }
    free(obj);
}

/**
 * Compares two objects to check their relative order.
 *
 * \param   obj1    First obj in the comparison.
 * \param   obj2    Second obj in the comparison.
 *
 * \return  -ve if obj1 < obj2, 0 if they are equal, +ve otherwise
 */
int mango_object_compare(const MangoObject *obj1, const MangoObject *obj2)
{
    if (obj1 == obj2)
    {
        return 0;
    }
    else if (obj1 == NULL || obj2 == NULL)
    {
        return obj1 - obj2;
    }
    else if (obj1->prototype == obj2->prototype)
    {
        if (obj1->objData == obj2->objData)
        {
            return 0;
        }
        else if (obj1->objData == NULL || obj2->objData == NULL)
        {
            return obj1->objData - obj2->objData;
        }
        else if (obj1->prototype->objectDataCompare != NULL)
        {
            return obj1->prototype->objectDataCompare(obj1->objData, obj2->objData);
        }
        else if (obj2->prototype->objectDataCompare != NULL)
        {
            return obj2->prototype->objectDataCompare(obj2->objData, obj1->objData);
        }
        return 0;
    }
    return obj1->prototype - obj2->prototype;
}

/**
 * Compares two objects to see if they are equal.
 *
 * \param   obj1   First node in the comparison.
 * \param   obj2   Second node in the comparison.
 *
 * \return  true if nodes are equal (as defined by their objectDataEquals
 * callback), false otherwise.
 */
BOOL mango_object_equal(const MangoObject *obj1, const MangoObject *obj2)
{
    if (obj1 == obj2)
    {
        return true;
    }
    else if (obj2 == NULL || obj1 == NULL)
    {
        return false;
    }
    else if (obj1->prototype == obj2->prototype)
    {
        if (obj1->objData == obj2->objData)
        {
            return true;
        }
        else if (obj1->objData == NULL || obj2->objData == NULL)
        {
            return false;
        }
        else if (obj1->prototype->objectDataEquals != NULL)
        {
            return obj1->prototype->objectDataEquals(obj1->objData, obj2->objData);
        }
        else if (obj2->prototype->objectDataEquals != NULL)
        {
            return obj2->prototype->objectDataEquals(obj2->objData, obj1->objData);
        }
        return true;
    }
    return false;
}

void default_delete_object_data(void *objData)
{
    if (objData != NULL)
        free(objData);
}

int default_object_compare(const void *objdata1, const void *objdata2)
{
    return objdata1 - objdata2;
}

BOOL default_objects_are_equal(const void *objdata1, const void *objdata2)
{
    return objdata1 == objdata2;
}

#include "mobject.h"
#include "mmemutils.h"
#include "mclasses.h"

void default_delete_object_data(void *objData);
int  default_object_compare(const void *objdata1, const void *objdata2);
BOOL default_objects_are_equal(const void *objdata1, const void *objdata2);

/**
 * Creates a object with default methods.
 */
MangoObject *mango_object_new(void *objData)
{
    MangoObject *obj        = ZNEW(MangoObject);
    obj->objRefCount        = 1;
    obj->objClass           = mango_class_for_name("Object", true);
    obj->objData            = objData;
    obj->deleteObjectData   = default_delete_object_data;
    obj->objectDataEquals   = default_objects_are_equal;
    obj->compareObjectData  = default_object_compare;
    return obj;
}

/**
 * Destroys a mango object.
 */
void mango_object_free(MangoObject *obj)
{
    if (obj->objData != NULL && obj->deleteObjectData != NULL)
    {
        obj->deleteObjectData(obj->objData);
    }
    free(obj);
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
    else if (obj1->objClass == obj2->objClass)
    {
        if (obj1->objData == obj2->objData)
        {
            return true;
        }
        else if (obj1->objData == NULL || obj2->objData == NULL)
        {
            return false;
        }
        else if (obj1->objectDataEquals != NULL)
        {
            return obj1->objectDataEquals(obj1->objData, obj2->objData);
        }
        else if (obj2->objectDataEquals != NULL)
        {
            return obj2->objectDataEquals(obj2->objData, obj1->objData);
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

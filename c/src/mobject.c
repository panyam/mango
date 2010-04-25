#include "mobject.h"
#include "mmemutils.h"
#include "mclasses.h"

/**
 * Increases the reference count of the object and returns int.
 */
MangoObject *mango_object_copy(MangoObject *obj)
{
    obj->__refCount__++;
    if (obj->__prototype__->incRefFunc != NULL)
        obj->__prototype__->incRefFunc(obj);
    return obj;
}

/**
 * Decreases the reference count of the object and deletes it if the
 * reference count reaches 0.
 */
BOOL mango_object_release(MangoObject *obj)
{
    obj->__refCount__--;
    if (obj->__prototype__->decRefFunc != NULL)
        obj->__prototype__->decRefFunc(obj);
    if (obj->__refCount__ == 0)
    {
        if (obj->__prototype__->cleanUpFunc != NULL)
            obj->__prototype__->cleanUpFunc(obj);
        free(obj);
        return false;
    }
    return true;
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
    else if (obj1->__prototype__ == obj2->__prototype__)
    {
        if (obj1->__prototype__->compareFunc != NULL)
        {
            return obj1->__prototype__->compareFunc(obj1, obj2);
        }
        else if (obj2->__prototype__->compareFunc != NULL)
        {
            return obj2->__prototype__->compareFunc(obj2, obj1);
        }
        return 0;
    }
    return obj1->__prototype__ - obj2->__prototype__;
}

/**
 * Compares two objects to see if they are equal.
 *
 * \param   obj1   First node in the comparison.
 * \param   obj2   Second node in the comparison.
 *
 * \return  true if nodes are equal (as defined by their equalsFunc
 * callback), false otherwise.
 */
BOOL mango_objects_are_equal(const MangoObject *obj1, const MangoObject *obj2)
{
    if (obj1 == obj2)
    {
        return true;
    }
    else if (obj2 == NULL || obj1 == NULL)
    {
        return false;
    }
    else if (obj1->__prototype__ == obj2->__prototype__)
    {
        if (obj1->__prototype__->equalsFunc != NULL)
        {
            return obj1->__prototype__->equalsFunc(obj1, obj2);
        }
        else if (obj2->__prototype__->equalsFunc != NULL)
        {
            return obj2->__prototype__->equalsFunc(obj2, obj1);
        }
        return true;
    }
    return false;
}


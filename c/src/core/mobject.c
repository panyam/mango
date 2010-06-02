#include "mangopub.h"

/**
 * Allocates an object of a given size.
 * \param   obj     Size of the object to be created.
 * \param   proto   Object's prototype to be set as.
 * \return  A bit of memory (of objSize) casted as a MangoObject.
 */
MangoObject *mango_object_alloc(size_t objSize, MangoPrototype *proto)
{
    if (proto == NULL)
        proto = mango_object_prototype();

    MangoObject *obj    = (MangoObject *)malloc(objSize);
    mango_object_init(obj, proto);
    return obj;
}

/**
 * Initialises an already created mango object.
 * \param   obj     Object to be initialised.
 * \param   proto   Object's prototype to be set as.
 * \return the original object being initialised.
 */
MangoObject *mango_object_init(MangoObject *obj, MangoPrototype *proto)
{
    obj->__prototype__  = proto;
    obj->__refCount__   = 1;
    return obj;
}

/**
 * Increases the reference count of the object and returns int.
 */
MangoObject *mango_object_incref(MangoObject *obj)
{
    if (obj != NULL)
        obj->__refCount__++;
    return obj;
}

/**
 * Decreases the reference count of the object and deletes it if the
 * reference count reaches 0.
 */
BOOL mango_object_decref(MangoObject *obj)
{
    if (obj == NULL)
        return false;

    obj->__refCount__--;
    if (obj->__refCount__ == 0)
    {
        if (obj->__prototype__->deallocFunc != NULL)
            obj->__prototype__->deallocFunc(obj);
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
        assert("Object prototype cannot be NULL" && obj1->__prototype__ != NULL);

        return obj1->__prototype__->compareFunc(obj1, obj2);
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
        assert("Object prototype cannot be NULL" && obj1->__prototype__ != NULL);

        return obj1->__prototype__->equalsFunc(obj1, obj2);
    }
    return false;
}

/**
 * Deallocates an object.
 */
void mango_object_dealloc(MangoObject *obj)
{
    // nothing!
}

/**
 * Tells if an object can be casted to a particular prototype.
 */
BOOL mango_object_instanceof(const MangoObject *obj, const char *proto)
{
    return false;
}

/**
 * Gets an attribute of this object given an integer index.
 */
MangoObject *mango_object_get_int_attr(const MangoObject *obj, int index)
{
    if (obj->__prototype__->getIntAttrFunc != NULL)
        return obj->__prototype__->getIntAttrFunc(obj, index);
    return NULL;
}

/**
 * Gets an attribute of this object given a key.
 */
MangoObject *mango_object_get_str_attr(const MangoObject *obj, const MangoString *key)
{
    if (obj->__prototype__->getStrAttrFunc != NULL)
        return obj->__prototype__->getStrAttrFunc(obj, key);
    return NULL;
}

/**
 * Tells if the object can return a an attribute value for an integer
 * index.
 */
BOOL mango_object_has_int_attr(const MangoObject *obj, int index)
{
    if (obj->__prototype__->hasIntAttrFunc != NULL)
        return obj->__prototype__->hasIntAttrFunc(obj, index);
    return false;
}

/**
 * Tells if the object can return a an attribute value for a key.
 */
BOOL mango_object_has_str_attr(const MangoObject *obj, const MangoString *key)
{
    if (obj->__prototype__->hasStrAttrFunc != NULL)
        return obj->__prototype__->hasStrAttrFunc(obj, key);
    return false;
}

/**
 * Get an iterator for an object.
 */
MangoIterator *mango_object_iterator(MangoObject *obj)
{
    if (obj != NULL && obj->__prototype__->iterFunc != NULL)
        return obj->__prototype__->iterFunc(obj);
    return NULL;
}


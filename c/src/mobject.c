#include <stdarg.h>
#include "mobject.h"
#include "mmemutils.h"
#include "mclasses.h"

BOOL mango_prototype_default_equals(const MangoObject *obj1, const MangoObject *obj2)
{
    return obj1 == obj2;
}

int mango_prototype_default_compare(const MangoObject *obj1, const MangoObject *obj2)
{
    return obj1 - obj2;
}

/**
 * Initialises a prototype object with a name and default methods.
 * \param   proto   Prototype type object to initialise.
 * \param   name    Name of the prototype.
 * \return  The initialised prototype instance.
 */
MangoPrototype *mango_prototype_init(MangoPrototype * proto, const char *name, size_t size)
{
    proto->name         = strdup(name == NULL ? "" : name);
    proto->size         = size;
    proto->deallocFunc  = NULL;
    proto->equalsFunc   = mango_prototype_default_equals;
    proto->compareFunc  = mango_prototype_default_compare;
    return proto;
}


/**
 * Allocates an object of a given size.
 * \param   obj     Size of the object to be created.
 * \param   proto   Object's prototype to be set as.
 * \return  A bit of memory (of objSize) casted as a MangoObject.
 */
MangoObject *mango_object_alloc(size_t objSize, MangoPrototype *proto)
{
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
 * An object initializer.  The object must be allocated first (perhaps with
 * mango_object_alloc) or initialised with mango_object_init.
 * \param   obj         Object to be initialised.
 * \param   initFunc    INitialiser function to be called on the object.
 * \param   ...         Var arguments passed to the initialiser function.
 * \return The original object.
 */
MangoObject *mango_object_init_with_func(MangoObject *obj, ObjectInitFunc initFunc, ...)
{
    if (initFunc != NULL)
    {
        va_list ap;
        va_start(ap, initFunc);
        initFunc(obj, ap);
        va_end(ap);
    }
    return obj;
}

/**
 * Increases the reference count of the object and returns int.
 */
MangoObject *mango_object_incref(MangoObject *obj)
{
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
BOOL mango_object_instanceof(const MangoObject *obj, const MangoPrototype *proto)
{
    if (obj->__prototype__->size >= proto->size)
    {
        return memcmp(obj->__prototype__, proto, proto->size) == 0;
    }
    return false;
}


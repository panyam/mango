
#ifndef __MANGO_OBJECT_PTR_H__
#define __MANGO_OBJECT_PTR_H__

#include <istream>
#include "mangopub.h"

template <typename MangoObjType>
class objptr
{
    typedef MangoObjType*(*mango_object_creator)();

public:
    objptr(mango_object_creator creatorFunc)
    {
        mangoObj = creatorFunc();
    }

    objptr(MangoObjType *obj)
    {
        mangoObj = obj;
    }

    /**
     * Copy constructor.
     */
    objptr(const objptr &another)
    {
        mangoObj = OBJ_INCREF(another.mangoObj);
    }

    /**
     * Decrements the object's ref count.
     */
    virtual ~objptr()
    {
        if (mangoObj != NULL)
            OBJ_DECREF(mangoObj);
    }

    /**
     * Assignment operator.
     */
    objptr & operator = (const objptr & other)
    {
        if (this != &other)
        {
            if (this->mangoObj != other.mangoObj)
                // decrement our current object's reference
                OBJ_DECREF(this->mangoObj);

            // copy another obj over
            mangoObj = OBJ_INCREF(other.mangoObj);
        }
        return *this;
    }

    // Overloaded dereferencing operator.
    inline MangoObjType *operator->() const { return mangoObj; }

    inline MangoObjType *operator()() const { return mangoObj; }

    inline MangoObject *obj() const { return OBJ(mangoObj); }

    inline MangoObjType *get() const { return (MangoObjType *)mangoObj; }

    template <typename ReturnType>
    inline ReturnType *get() const { return (ReturnType *)mangoObj; }

    // Short cut for getting, incrementing and decrementing ref counts
    inline int refcount() const { return mangoObj == NULL ? 0 : OBJ_REFCOUNT(mangoObj); }
    inline MangoObjType *incref() { OBJ_INCREF(mangoObj); }
    inline bool decref()
    {
        if (!OBJ_DECREF(mangoObj))
        {
            mangoObj = NULL;
            return false;
        }
        return true;
    }

private:
    MangoObjType *  mangoObj;
};

#endif


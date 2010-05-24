
#include "mcollection.h"

/**
 * Initiliases with the collection interface.
 */
MangoCollectionPrototype *mango_collection_prototype_init(MangoCollectionPrototype *proto)
{
    proto->sizeFunc = NULL;
    proto->clearFunc = NULL;
    proto->isEmptyFunc = NULL;
    return proto;
}

/**
 * Frees the collection.
 * \param   collection  Collection to be freed.
 */
void mango_collection_dealloc(MangoCollection *collection)
{
    mango_object_dealloc((MangoObject *)collection);
}

/**
 * Returns the collection size.
 * \param   collection  Collection whose size is to be returned.
 * \return size of the collection.
 */
int mango_collection_size(MangoCollection *collection)
{
    if (collection->__prototype__->sizeFunc != NULL)
    {
        return collection->__prototype__->sizeFunc(collection);
    }
    return 0;
}

/**
 * Tells if the collection is empty or not.
 * \param   collection  Collection to see if empty or not.
 * \return true if collection is empty, false otherwise.
 */
BOOL mango_collection_is_empty(MangoCollection *collection)
{
    if (collection->__prototype__->isEmptyFunc!= NULL)
    {
        return collection->__prototype__->isEmptyFunc(collection);
    }
    return true;
}

/**
 * Clears the collection.
 * \param   collection  Collection to be cleared.
 */
void mango_collection_clear(MangoCollection *collection)
{
    if (collection->__prototype__->clearFunc!= NULL)
    {
        return collection->__prototype__->clearFunc(collection);
    }
}

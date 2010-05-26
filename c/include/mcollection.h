
#ifndef __MANGO_COLLECTION_H__
#define __MANGO_COLLECTION_H__

#include "mobject.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*CollectionSizeFunc)(MangoCollection *collection);
typedef void (*CollectionClearFunc)(MangoCollection *collection);
typedef BOOL (*CollectionIsEmptyFunc)(MangoCollection *collection);
typedef BOOL (*CollectionRemoveFunc)(MangoCollection *collection, MangoObject *obj);
typedef BOOL (*CollectionContainsFunc)(MangoCollection *collection, MangoObject *obj);

/**
 * Base interface of all collections.
 */
INHERIT_STRUCT(MangoCollectionPrototype, MangoPrototype,
    /**
     * Returns the number of entries.
     */
    int (*sizeFunc)(MangoCollection *collection);

    /**
     * Clears the collection
     */
    void (*clearFunc)(MangoCollection *collection);

    /**
     * Tells if the collection is empty.
     */
    BOOL (*isEmptyFunc)(MangoCollection *collection);

    /**
     * Tells if the collection contains an object.
     */
    BOOL (*containsFunc)(MangoCollection *collection, MangoObject *obj);

    /**
     * Removes the first occurence of an object from the collection and
     * drecrements its count.
     */
    BOOL (*removeFunc)(MangoCollection *collection, MangoObject *obj);
);

/**
 * Super class of all associative containers.
 */
DECLARE_CLASS(MangoCollection, MangoCollectionPrototype);

#define COLLECTION_SIZE(coll)       mango_collection_size((MangoCollection *)coll)
#define COLLECTION_IS_EMPTY(coll)   mango_collection_is_empty((MangoCollection *)coll)
#define COLLECTION_CLEAR(coll)      mango_collection_clear((MangoCollection *)coll)

/**
 * Initialises a collection.
 */
MangoCollection *mango_collection_init(MangoCollection *collection, MangoCollectionPrototype *proto);

/**
 * Frees the collection.
 * \param   collection  Collection to be freed.
 */
extern void mango_collection_dealloc(MangoCollection *collection);

/**
 * Returns the collection size.
 * \param   collection  Collection whose size is to be returned.
 * \return size of the collection.
 */
extern int mango_collection_size(MangoCollection *collection);

/**
 * Tells if the collection is empty or not.
 * \param   collection  Collection to see if empty or not.
 * \return true if collection is empty, false otherwise.
 */
extern BOOL mango_collection_is_empty(MangoCollection *collection);

/**
 * Clears the collection.
 * \param   collection  Collection to be cleared.
 */
extern void mango_collection_clear(MangoCollection *collection);

#ifdef __cplusplus
}
#endif

#endif


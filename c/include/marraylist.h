
#ifndef __MANGO_ARRAYLIST_H__
#define __MANGO_ARRAYLIST_H__

#include "mlist.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Array structures.
 */
DECLARE_CLASS(MangoArrayList, MangoListPrototype,
    /*
     * Members
     */
    MangoObject **  items;
    unsigned        length;
    unsigned        capacity;
);

/**
 * Creates a new array.
 */
extern MangoArrayList *mango_arraylist_new();

/**
 * Initialises an array list.
 */
extern MangoArrayList *mango_arraylist_init(MangoArrayList *list, MangoListPrototype *proto);

/**
 * Returns the prototype for a Mango Array List
 */
extern MangoListPrototype *mango_arraylist_prototype();

/*
 * Initialise an array.
 */
extern void mango_arraylist_reserve(MangoArrayList *array, int capacity);

#ifdef __cplusplus
}
#endif

#endif


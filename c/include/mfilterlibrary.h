
#ifndef __MANGO_FILTER_LIBRARY_H__
#define __MANGO_FILTER_LIBRARY_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A generic library that acts as a factory of objects.
 */
struct MangoFilterLibrary
{
    /**
     * A tree of filters.
     */
    MangoBinTree *filters;
};

/**
 * Creates a new mango filter library.
 * \param name  Name of the library.
 * \return  A new MangoLibrary instance.
 */
extern MangoFilterLibrary *mango_filter_library_new();

/**
 * Frees the filter library created with the above new method.
 * \param   library Filter library to be destroyed.
 */
extern void mango_filter_library_free(MangoFilterLibrary *library);

/**
 * Registers a new creator method for a new type of object.
 * \param   library     Library where the new creator is to be registered.
 * \param   name        Name of the filter to be registered.
 * \param   filter      Filter to be registered.
 */
extern void mango_filter_library_register(MangoFilterLibrary *library,
                                          MangoString *name,
                                          MangoFilter *filter);

/**
 * Gets a filter by a given name.
 *
 * \param   library Library where the creator methods are stored.
 * \param   name    Name of the object class to be created.
 *
 * \return  The filter by a given name or NULL if it does not exist.
 */
extern const MangoFilter *mango_filter_library_get(MangoFilterLibrary *library,
                                                   const MangoString *name);

#ifdef __cplusplus
}
#endif

#endif


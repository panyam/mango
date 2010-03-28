
#ifndef __MANGO_NODE_CLASSES_H__
#define __MANGO_NODE_CLASSES_H__

#include "mfwddefs.h"

/**
 * Gets the class for a given name, registering it if necessary.
 *
 * \param   name        Name of the object to be registered.
 * \param   register    Whether a class should be registered if it was not
 *                      found?
 *
 * \returns The class integer ID for the name, if it exists.  0 otherwise.
 */
extern int mango_class_for_name(const char *name, BOOL register);

/**
 * Gets the name of a class given its class ID.
 * \param   cls Class whose string name is to be returned.
 */
extern const char *mango_name_for_class(int cls);

#endif


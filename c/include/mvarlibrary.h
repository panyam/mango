
#ifndef __MANGO_VARIABLE_LIBRARY_H__
#define __MANGO_VARIABLE_LIBRARY_H__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A "special" variable library.
 * Creates an instance of a special variable.
 *
 * \param   name    Name of the variable instance to be created.
 * \param   library Library where the variable creators are stored.  If NULL
 *                  the default instance is used.
 *
 * \return  The variable for a given name or NULL if it does not exist.
 */
extern MangoVariable *mango_variable_library_new_instance(const MangoString *name, const MangoLibrary *library);

#ifdef __cplusplus
}
#endif

#endif


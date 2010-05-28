
#ifndef __MANGO_VARIABLE_LIBRARY_H__
#define __MANGO_VARIABLE_LIBRARY_H__

#include "mtable.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A "special" var library.
 * Creates an instance of a special var.
 *
 * \param   name    Name of the var instance to be created.
 * \param   library Library where the var creators are stored.  If NULL
 *                  the default instance is used.
 *
 * \return  The var for a given name or NULL if it does not exist.
 */
extern MangoVar *mango_var_library_new_instance(const MangoString *name, MangoTable *library);

#ifdef __cplusplus
}
#endif

#endif


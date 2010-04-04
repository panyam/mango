
#define _GNU_SOURCE
#include "mlibrary.h"
#include "mlist.h"
#include "mstring.h"

/**
 * Creates a new mango library.
 * \param name  Name of the library.
 * \return  A new MangoLibrary instance.
 */
MangoLibrary *mango_library_new(const MangoString *name)
{
    MangoLibrary *mlib  = (MangoLibrary *)calloc(1, sizeof(MangoLibrary *));
    mlib->name          = mango_string_from_buffer(name->buffer, name->length);
    return mlib;
}

/**
 * Frees a library created with the above new method.
 * \param   library Library to be destroyed.
 */
void mango_library_free(MangoLibrary *library)
{
    if (library->name != NULL)
        mango_string_free(library->name);
    free(library);
}

/**
 * Registers a new creator method for a new type of object.
 * \param   library Library where the new creator is to be registered.
 * \param   name    Name of the creator to be registered.
 * \param   func    Creator method to be used.
 */
void mango_library_register(MangoLibrary *library, const MangoString *name, CreatorFunc func)
{
    if (library->creators == NULL)
    {
        library->creators = mango_list_new();
    }

    // creators list contains name and creator func interleaved
    for (MangoListNode *temp = library->creators->head;temp != NULL;temp = temp->next->next)
    {
        if (mango_strings_are_equal((MangoString *)temp->data, name))
        {
            temp->next->data = func;
            return ;
        }
    }

    // add it otherwise
    mango_list_push_back(library->creators, mango_string_from_buffer(name->buffer, name->length));
    mango_list_push_back(library->creators, func);
}

/**
 * Creates a new instance of a particular object by invoking the registered
 * creator method in the library.
 *
 * \param   library Library where the creator methods are stored.
 * \param   name    Name of the object class to be created.
 * \param   ...     Parameters to be passed to the creator.
 *
 * \return  A new instance of the object created by the registered creator
 * method or NULL if a creator was not found for the name.
 */
void *mango_library_new_instance(MangoLibrary *library, const MangoString *name, ...)
{
    void *new_instance = NULL;
    if (library != NULL && library->creators != NULL)
    {
        // creators list contains name and creator func interleaved
        for (MangoListNode *temp = library->creators->head;temp != NULL;temp = temp->next->next)
        {
            if (mango_strings_are_equal((MangoString *)temp->data, name))
            {
                assert(false);
                CreatorFunc func = (CreatorFunc)temp->next->data;

                break ;
            }
        }
    }
    return new_instance;
}


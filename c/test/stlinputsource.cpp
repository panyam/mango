
#include "stlinputsource.h"
#include <iostream>

int stl_input_source_next_char(MangoInputSource *);

/**
 * Initialises an stl input source with an std istream.
 * \param   instream    The stream to initialise with
 * \returns New input source object.
 */
StlInputSource *new_stl_input_source(std::istream *instream)
{
    StlInputSource *source = (StlInputSource *)malloc(sizeof(StlInputSource));
    source->sourceBase.nextChar = stl_input_source_next_char;
    source->inputStream = instream;
    return source;
}

/**
 * Frees the input source.
 * The istream object is NOT deleted.  It must be deleted prior to calling
 * this method.
 */
void free_stl_input_source(StlInputSource *source)
{
    free(source);
}

/**
 * Gets the next character from the input source if any.
 * \param   source  Input source to get the next char from.
 * \returns -1 if eof or error, otherwise the character.
 */
int stl_input_source_next_char(MangoInputSource *source)
{
    StlInputSource *stlSource = (StlInputSource *)source;
    int out = stlSource->inputStream->get();
    if (stlSource->inputStream->eof())
        return 0;
    if (stlSource->inputStream->bad() || stlSource->inputStream->fail())
        return -1;
    return out;
}


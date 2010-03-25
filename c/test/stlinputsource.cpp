
#include "stlinputsource.h"

int stl_input_source_next_char(MangoInputSource *);

/**
 * Initialises an input source with an input stream.
 *
 * \param   source      The input source to initialise
 * \param   instream    The stream to initialise with
 */
void init_stl_input_source(StlInputSource *source, std::istream *instream)
{
    source->sourceBase.nextChar = stl_input_source_next_char;
    source->inputStream = instream;
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
    else if (stlSource->inputStream->bad() || stlSource->inputStream->fail())
        return -1;
    return out;
}


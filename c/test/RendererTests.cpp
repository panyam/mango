
#include "RendererTests.h"
#include "testutils.h"

RendererTestFixture::RendererTestFixture() :
    context(mango_context_new(NULL, NULL, NULL, NULL, NULL)),
    tokenizer(NULL),
    parser(NULL),
    input_source(NULL),
    input_string(""),
    tmplctx(mango_tmplctx_new()),
    resolver(mango_varresolver_default())
{
    // register filters
    register_in_library(context, context->filter_library, "add", (MangoObject *)mango_addfilter_default());

    // and register the "for" tag
    register_in_library(context, context->tag_library, "for", (MangoObject *)mango_fortagparser_default());
}

RendererTestFixture::~RendererTestFixture()
{
    if (input_source != NULL)
    {
        if (input_source->inputStream != NULL)
            delete input_source->inputStream;
        free_stl_input_source(input_source);
        input_source = NULL;
    }

    if (tokenizer != NULL) 
    {
        mango_tokenizer_free(tokenizer);
        tokenizer = NULL;
    }

    if (parser != NULL) 
    {
        mango_parser_free(parser);
        parser = NULL;
    }
    mango_context_free(context);
}

/**
 * Setup the fixture with an input string.
 */
void RendererTestFixture::SetUpWithInputString(const std::string &input)
{
    input_string = input;
    input_source = new_stl_input_source(new std::istringstream(input));
    tokenizer = mango_tokenizer_new((MangoInputSource *)input_source);
    parser = mango_parser_new(tokenizer);
}

/**
 * Check that the given string matches against the rendered output.
 */
void RendererTestFixture::CheckRenderedOutput(const char *output)
{
    // parse the input string
    MangoError *error = NULL;
    MangoNode *parsedNode = mango_parser_parse(parser, context, &error);
    if (error != NULL)
    {
        printf("Parse Error (%d): %s\n", error->errorCode, error->errorMessage);
        CHECK(false);
        mango_error_free(error);
    }
    else
    {
        puts("==============================================");
        objptr<MangoStrOutStream> outstream(mango_stroutstream_new());

        // render
        mango_render_node(parsedNode, tmplctx, outstream.get<MangoOutStream>(), &error);

        if (error != NULL)
        {
            printf("Renderer Error (%d): %s\n", error->errorCode, error->errorMessage);
            CHECK(false);
            mango_error_free(error);
        }
        else
        {
            // check
            if (outstream->strbuff != NULL)
            {
                CHECK_EQUAL(output, outstream->strbuff->buffer);
            }
            CHECK(mango_stringbuffer_compare(outstream->strbuff, output, -1) == 0);
        }
    }

    OBJ_DECREF(parsedNode);
}



#include "RendererTests.h"
#include "testutils.h"

RendererTestFixture::RendererTestFixture() :
    tokenizer(NULL),
    parser(NULL),
    loader(NULL),       // create a mock loader sometime
    input_source(NULL),
    input_string(""),
    filterLibrary(mango_filter_library_singleton()),
    tagLibrary(mango_tagparser_library_singleton()),
    context(mango_tmplctx_new()),
    resolver(mango_varresolver_default())
{
    parser_context.filterlib    = filterLibrary;
    parser_context.taglib       = tagLibrary;
    parser_context.strfactory   = (MangoStringFactory *)mango_rcstringfactory_default();
    parser_context.loader       = NULL;

    // register filters
    register_in_library(filterLibrary, "add", (MangoObject *)mango_addfilter_default());

    // and register the "for" tag
    register_in_library(tagLibrary, "for", (MangoObject *)mango_fortagparser_default());
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

    if (loader != NULL) 
    {
        delete loader;
        loader = NULL;
    }
}

/**
 * Check that the given string matches against the rendered output.
 */
void RendererTestFixture::CheckRenderedOutput(const char *output)
{
    // parse the input string
    MangoError *error = NULL;
    MangoNode *parsedNode = mango_parser_parse(&parser_context, &error);
    if (error != NULL)
    {
        printf("Error (%d): %s\n", error->errorCode, error->errorMessage);
        CHECK(false);
        mango_error_free(error);
    }
    else
    {
        puts("==============================================");
        MangoStringBuffer *sbuffer = mango_stringbuffer_with_capacity(256);

        // render

        // check
        CHECK_EQUAL(output, sbuffer->buffer);
        CHECK(mango_stringbuffer_compare(sbuffer, output, -1) == 0);

        mango_stringbuffer_free(sbuffer);
    }

    OBJ_DECREF(parsedNode);

    /*
    StringWriter writer = new StringWriter();
    if (parsedNodes != null)
    {
        try {
            renderer.renderNode(parsedNodes, writer, context);
        } catch (IOException e) {
            fail("Unexpected IO Exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
    assertEquals("Expected and Rendered outputs do not match", output, writer.getBuffer().toString());
    */
}

void RendererTestFixture::SetUpWithInputString(const std::string &input)
{
    input_string = input;
    input_source = new_stl_input_source(new std::istringstream(input));
    tokenizer = mango_tokenizer_new((MangoInputSource *)input_source);
    parser = mango_parser_new(tokenizer);
    parser_context.parser = parser;
}


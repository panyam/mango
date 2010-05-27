
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"

/**
 * Superclass of all renderer based test suites.
 */
class RendererTestFixture
{
public:
    MangoTokenizer *        tokenizer;
    MangoParser *           parser;
    MangoTemplateLoader *   loader;
    StlInputSource *        input_source;
    std::string             input_string;
    MangoTable *            filterLibrary;
    MangoTable *            tagLibrary;
    MangoStringFactory *    string_factory;
    MangoParserContext      parser_context;
    MangoTemplateContext *  context;
    MangoVarResolver *      resolver;

public:
    RendererTestFixture() :
        tokenizer(NULL),
        parser(NULL),
        loader(NULL),       // create a mock loader sometime
        input_source(NULL),
        input_string(""),
        filterLibrary(mango_filter_library_singleton()),
        tagLibrary(mango_tagparser_library_singleton()),
        string_factory((MangoStringFactory *)mango_rcstringfactory_new()),
        context(mango_tmplctx_new()),
        resolver(mango_varresolver_default())
    {
        parser_context.filterlib    = filterLibrary;
        parser_context.taglib       = tagLibrary;
        parser_context.strfactory   = string_factory;
        parser_context.loader       = NULL;

        // register filters
        register_in_library(filterLibrary, string_factory, "add", (MangoObject *)mango_addfilter_default());

        // and register the "for" tag
        register_in_library(tagLibrary, string_factory, "for", (MangoObject *)mango_fortagparser_default());
    }

    static void register_in_library(MangoTable *library, MangoStringFactory *string_factory, const char *key, MangoObject *value)
    {
        MangoString *mkey = mango_stringfactory_new_string(string_factory, key, -1);
        mango_table_put(library, mkey, value);
        OBJ_DECREF(mkey);
    }

    virtual ~RendererTestFixture()
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

        if (string_factory != NULL)
        {
            // string_factory(mango_rcstringfactory_new())
            string_factory = NULL;
        }
    }

    MangoVar *create_var(const char *value,
                                   bool isQuoted, bool isNum,
                                   MangoVar *next)
    {
        MangoString *varValue = mango_stringfactory_new_string(string_factory, value, -1);
        MangoVar *var = mango_var_new(varValue, isQuoted, next);
        var->isNumber = isNum;
        if (isNum)
        {
            var->intValue = atoi(value);
        }
        return var;
    }

	void CheckRenderedOutput(MangoString *output)
	{
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
        CHECK(false);
	}

protected:
    void SetUpWithInputString(const std::string &input)
    {
        input_string = input;
        input_source = new_stl_input_source(new std::istringstream(input));
        tokenizer = mango_tokenizer_new((MangoInputSource *)input_source);
        parser = mango_parser_new(tokenizer);
        parser_context.parser = parser;
    }
};


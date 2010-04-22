
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

class ResolverTestFixture
{
protected:
    MangoTokenizer *        tokenizer;
    MangoParser *           parser;
    MangoTemplateLoader *   loader;
    StlInputSource *        input_source;
    std::string             input_string;
    MangoLibrary *          filterLibrary;
    MangoLibrary *          tagLibrary;
    MangoStringFactory *    string_factory;
    MangoParserContext      parser_context;
    MangoTemplateContext *  context;
    MangoVariableResolver * resolver;
    MangoVariable *         variable;

public:
    ResolverTestFixture() :
        tokenizer(NULL),
        parser(NULL),
        loader(NULL),
        input_source(NULL),
        input_string(""),
        filterLibrary(mango_filter_library_singleton()),
        tagLibrary(mango_tagparser_library_singleton()),
        string_factory(mango_rcstringfactory_new())
    {
        parser_context.filterlib    = filterLibrary;
        parser_context.taglib       = tagLibrary;
        parser_context.strfactory   = string_factory;
        parser_context.loader       = NULL;
        context = mango_templatecontext_new();
        resolver = mango_varresolver_default();
    }

    virtual ~ResolverTestFixture()
    {
        DeleteFixture();
    }

    void DeleteFixture()
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

        if (context != NULL)
        {
            mango_templatecontext_free(context);
            context = NULL;
        }

        if (resolver != NULL)
        {
            mango_varresolver_free(resolver);
            resolver = NULL;
        }
    }

    void setupParserAndParseVariable(const std::string &input)
    {
        DeleteFixture();
        input_string = input;
        input_source = new_stl_input_source(new std::istringstream(input));
        tokenizer = mango_tokenizer_new((MangoInputSource *)input_source);
        parser = mango_parser_new(tokenizer);
        parser_context.parser = parser;
    }

    void checkResolvedVariable(const MangoValue *expectedValue)
    {
        MangoError *error = NULL;
        mango_parser_expect_token(parser, TOKEN_OPEN_VARIABLE, false, &error);
        variable = mango_variable_extract_with_parser(&parser_context, &error);
        mango_parser_expect_token(parser, TOKEN_CLOSE_VARIABLE, false, &error);
        MangoValue source = mango_value_make(MV_CONTEXT, context);
        MangoValue *resolvedValue = mango_varresolver_resolve(resolver, &source, variable);
    }
};

/**
 * Tests the creation of a string table.
 */
TEST_FIXTURE(ResolverTestFixture, TestCreate)
{
    // CHECK(mstable != NULL);
}

#if 0
public void testUnresolvedVariable()
{
    setupParserAndParseVariable("{{a}}");
    checkResolvedVariable(null);
}

public void testNumericVariable()
{
    setupParserAndParseVariable("{{a}}");
    context.setValue("a", 3);
    checkResolvedVariable(3);
}

public void testStringVariable()
{
    setupParserAndParseVariable("{{a}}");
    context.setValue("a", "Hello World");
    checkResolvedVariable("Hello World");
}

public void testDeleteContextValue()
{
    setupParserAndParseVariable("{{a}}");
    context.setValue("a", "Hello World");
    context.deleteValue("a");
    checkResolvedVariable(null);
}

public void testValueAsHashTable()
{
    setupParserAndParseVariable("{{a.b}}");
    context.setValue("a", Utils.makeHashtable("b", 3));
    checkResolvedVariable(3);
}

public void testValueAsMap()
{
    setupParserAndParseVariable("{{a.b}}");
    context.setValue("a", Utils.makeHashMap("b", 3));
    checkResolvedVariable(3);
}

public void testValueAsIndex()
{
    context.setValue("a", Utils.makeHashMap("b", Utils.makeArrayList(3, 4, 5)));
    setupParserAndParseVariable("{{a.b.0}}");
    checkResolvedVariable(3);
    setupParserAndParseVariable("{{a.b.1}}");
    checkResolvedVariable(4);
    setupParserAndParseVariable("{{a.b.2}}");
    checkResolvedVariable(5);
}

public void testValueAsClassWithSimpleMethod()
{
    context.setValue("a", Utils.makeHashMap("b", 
            new Object() { @SuppressWarnings("unused")
            public Object elementAtIndex(final int i) { return i; } } ));
    setupParserAndParseVariable("{{a.b.4}}");
    checkResolvedVariable(4);
}

public void testValueAsClassWithComplexMethod()
{
    context.setValue("a", Utils.makeHashMap("b", 
            new Object() { 
                @SuppressWarnings("unused")
                public Object elementAtIndex(final int i) {
                    return new Object() {
                        public Object elementAtIndex(int j)
                        {
                            return i * j;
                        }
                    };
                } }));
    setupParserAndParseVariable("{{a.b.4.3}}");
    checkResolvedVariable(12);
}

public void testValueAsSimpleField()
{
    context.setValue("a", new Object() { @SuppressWarnings("unused") public int b = 3; });
    setupParserAndParseVariable("{{a.b}}");
    checkResolvedVariable(3);
}

public void testValueAsSimpleMethod()
{
    context.setValue("a", new Object() { @SuppressWarnings("unused") public int b() { return 666; } });
    setupParserAndParseVariable("{{a.b}}");
    checkResolvedVariable(666);
}
#endif

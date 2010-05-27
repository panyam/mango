
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
    StlInputSource *        input_source;
    std::string             input_string;
    MangoTable *            filterLibrary;
    MangoTable *            tagLibrary;
    MangoStringFactory *    string_factory;
    MangoParserContext      parser_context;
    MangoTemplateContext *  context;
    MangoVarResolver * resolver;
    MangoVar *         var;

public:
    ResolverTestFixture() :
        tokenizer(NULL),
        parser(NULL),
        input_source(NULL),
        input_string(""),
        filterLibrary(mango_filter_library_singleton()),
        tagLibrary(mango_tagparser_library_singleton()),
        string_factory((MangoStringFactory *)mango_rcstringfactory_new())
    {
        parser_context.filterlib    = filterLibrary;
        parser_context.taglib       = tagLibrary;
        parser_context.strfactory   = string_factory;
        parser_context.loader       = NULL;
        context                     = mango_tmplctx_new();
        resolver                    = mango_varresolver_default();
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

        if (context != NULL)
        {
            OBJ_DECREF(context);
            context = NULL;
        }
    }

    void SetupParserAndParseVar(const std::string &input)
    {
        input_string = input;
        input_source = new_stl_input_source(new std::istringstream(input));
        tokenizer = mango_tokenizer_new((MangoInputSource *)input_source);
        parser = mango_parser_new(tokenizer);
        parser_context.parser = parser;
    }

    void CheckResolvedVar(const MangoObject *expectedValue)
    {
        MangoError *error = NULL;
        mango_parser_expect_token(parser, TOKEN_OPEN_VARIABLE, false, &error);
        var = mango_var_extract_with_parser(&parser_context, &error);
        mango_parser_expect_token(parser, TOKEN_CLOSE_VARIABLE, false, &error);
        MangoObject *resolvedValue = mango_varresolver_resolve_chain(resolver, (MangoObject *)context, var);
        CHECK(OBJ_EQUALS(expectedValue, resolvedValue));
    }
};

/**
 * Tests the creation of a string table.
 */
TEST_FIXTURE(ResolverTestFixture, TestCreate)
{
    // CHECK(mstable != NULL);
}

TEST_FIXTURE(ResolverTestFixture, TestUnresolvedVar)
{
    SetupParserAndParseVar("{{a}}");
    CheckResolvedVar(NULL);
}

TEST_FIXTURE(ResolverTestFixture, TestNumericVar)
{
    MangoString *key = mango_stringfactory_new_string(string_factory, "a", -1);
    SetupParserAndParseVar("{{a}}");
    mango_tmplctx_set(context, key, (MangoObject *)mango_number_from_int(3));
    CheckResolvedVar((MangoObject *)mango_number_from_int(3));
    OBJ_DECREF(key);
}

TEST_FIXTURE(ResolverTestFixture, TestStringVar)
{
    MangoString *key = mango_stringfactory_new_string(string_factory, "a", -1);
    MangoString *inval = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    MangoString *outval = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    SetupParserAndParseVar("{{a}}");
    mango_tmplctx_set(context, key, OBJ(inval));
    CheckResolvedVar(OBJ(outval));
    OBJ_DECREF(key);
    OBJ_DECREF(inval);
    OBJ_DECREF(outval);
}

TEST_FIXTURE(ResolverTestFixture, TestValueAsTable)
{
    MangoString *keya = mango_stringfactory_new_string(string_factory, "a", -1);
    MangoString *keyb = mango_stringfactory_new_string(string_factory, "b", -1);

    MangoTable *table   = (MangoTable *)mango_treetable_new();
    mango_table_put(table, keyb, OBJ(mango_number_from_int(3)));

    mango_tmplctx_set(context, keya, OBJ(table));

    SetupParserAndParseVar("{{a.b}}");
    CheckResolvedVar(OBJ(mango_number_from_int(3)));

    OBJ_DECREF(keya);
    OBJ_DECREF(keyb);
    OBJ_DECREF(table);
}

TEST_FIXTURE(ResolverTestFixture, TestValueAsIndex)
{
    MangoString *keya = mango_stringfactory_new_string(string_factory, "a", -1);
    MangoString *keyb = mango_stringfactory_new_string(string_factory, "b", -1);


    MangoArrayList *array = mango_arraylist_new();
    LIST_PUSH_BACK(array, mango_number_from_int(3));
    LIST_PUSH_BACK(array, mango_number_from_int(4));
    LIST_PUSH_BACK(array, mango_number_from_int(5));

    MangoTable *table   = (MangoTable *)mango_treetable_new();
    mango_table_put(table, keyb, OBJ(array));

    mango_tmplctx_set(context, keya, OBJ(table));

    SetupParserAndParseVar("{{a.b.0}}");
    CheckResolvedVar((MangoObject *)mango_number_from_int(3));
    SetupParserAndParseVar("{{a.b.1}}");
    CheckResolvedVar((MangoObject *)mango_number_from_int(4));
    SetupParserAndParseVar("{{a.b.2}}");
    CheckResolvedVar((MangoObject *)mango_number_from_int(5));

    OBJ_DECREF(keya);
    OBJ_DECREF(keyb);
    OBJ_DECREF(array);
    OBJ_DECREF(table);
}

#if 0

TEST_FIXTURE(ResolverTestFixture, TestValueAsClassWithSimpleMethod)
{
    mango_tmplctx_set(context, "a", Utils.makeHashMap("b", 
            new Object() { @SuppressWarnings("unused")
            public Object elementAtIndex(final int i) { return i; } } ));
    SetupParserAndParseVar("{{a.b.4}}");
    CheckResolvedVar(4);
}

TEST_FIXTURE(ResolverTestFixture, TestValueAsClassWithComplexMethod)
{
    mango_tmplctx_set(context, "a", Utils.makeHashMap("b", 
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
    SetupParserAndParseVar("{{a.b.4.3}}");
    CheckResolvedVar(12);
}

TEST_FIXTURE(ResolverTestFixture, TestValueAsSimpleField)
{
    mango_tmplctx_set(context, "a", new Object() { @SuppressWarnings("unused") public int b = 3; });
    SetupParserAndParseVar("{{a.b}}");
    CheckResolvedVar(3);
}

TEST_FIXTURE(ResolverTestFixture, TestValueAsSimpleMethod)
{
    mango_tmplctx_set(context, "a", new Object() { @SuppressWarnings("unused") public int b() { return 666; } });
    SetupParserAndParseVar("{{a.b}}");
    CheckResolvedVar(666);
}
#endif

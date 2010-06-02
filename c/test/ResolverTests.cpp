
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
    MangoContext *          context;
    MangoTokenizer *        tokenizer;
    MangoParser *           parser;
    StlInputSource *        input_source;
    std::string             input_string;
    MangoTemplateContext *  tmplctx;
    MangoVarResolver *      resolver;
    MangoVar *              var;

public:
    ResolverTestFixture() :
        context(mango_context_new(NULL, NULL, NULL, NULL, NULL)),
        tokenizer(NULL),
        parser(NULL),
        input_source(NULL),
        input_string("")
    {
        tmplctx                     = mango_tmplctx_new();
        resolver                    = mango_varresolver_default();
    }

    virtual ~ResolverTestFixture()
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

        if (tmplctx != NULL)
        {
            OBJ_DECREF(tmplctx);
            tmplctx = NULL;
        }

        mango_context_free(context);
    }

    void SetupParserAndParseVar(const std::string &input)
    {
        input_string = input;
        input_source = new_stl_input_source(new std::istringstream(input));
        tokenizer = mango_tokenizer_new((MangoInputSource *)input_source);
        parser = mango_parser_new(tokenizer);
    }

    void CheckResolvedVar(const MangoObject *expectedValue)
    {
        MangoError *error = NULL;
        mango_parser_expect_token(parser, TOKEN_OPEN_VARIABLE, false, &error);
        var = mango_var_extract_with_parser(parser, context, &error);
        mango_parser_expect_token(parser, TOKEN_CLOSE_VARIABLE, false, &error);
        MangoObject *resolvedValue = mango_varresolver_resolve_chain(resolver, (MangoObject *)tmplctx, var);
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
    MangoString *key = mango_stringfactory_new_string(context->string_factory, "a", -1);
    SetupParserAndParseVar("{{a}}");
    mango_tmplctx_set(tmplctx, key, (MangoObject *)mango_number_from_int(3));
    CheckResolvedVar((MangoObject *)mango_number_from_int(3));
    OBJ_DECREF(key);
}

TEST_FIXTURE(ResolverTestFixture, TestStringVar)
{
    MangoString *key = mango_stringfactory_new_string(context->string_factory, "a", -1);
    MangoString *inval = mango_stringfactory_new_string(context->string_factory, "Hello World", -1);
    MangoString *outval = mango_stringfactory_new_string(context->string_factory, "Hello World", -1);
    SetupParserAndParseVar("{{a}}");
    mango_tmplctx_set(tmplctx, key, OBJ(inval));
    CheckResolvedVar(OBJ(outval));
    OBJ_DECREF(key);
    OBJ_DECREF(inval);
    OBJ_DECREF(outval);
}

TEST_FIXTURE(ResolverTestFixture, TestValueAsTable)
{
    MangoString *keya = mango_stringfactory_new_string(context->string_factory, "a", -1);
    MangoString *keyb = mango_stringfactory_new_string(context->string_factory, "b", -1);

    MangoTable *table   = (MangoTable *)mango_treetable_new();
    mango_table_put(table, keyb, OBJ(mango_number_from_int(3)));

    mango_tmplctx_set(tmplctx, keya, OBJ(table));

    SetupParserAndParseVar("{{a.b}}");
    CheckResolvedVar(OBJ(mango_number_from_int(3)));

    OBJ_DECREF(keya);
    OBJ_DECREF(keyb);
    OBJ_DECREF(table);
}

TEST_FIXTURE(ResolverTestFixture, TestValueAsIndex)
{
    MangoString *keya = mango_stringfactory_new_string(context->string_factory, "a", -1);
    MangoString *keyb = mango_stringfactory_new_string(context->string_factory, "b", -1);


    MangoArrayList *array = mango_arraylist_new();
    LIST_PUSH_BACK(array, mango_number_from_int(3));
    LIST_PUSH_BACK(array, mango_number_from_int(4));
    LIST_PUSH_BACK(array, mango_number_from_int(5));

    MangoTable *table   = (MangoTable *)mango_treetable_new();
    mango_table_put(table, keyb, OBJ(array));

    mango_tmplctx_set(tmplctx, keya, OBJ(table));

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


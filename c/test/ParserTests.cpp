
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"

class ParserTestFixture
{
public:
    MangoTokenizer *        tokenizer;
    MangoParser *           parser;
    MangoTemplateLoader *   loader;
    StlInputSource *        input_source;
    std::string             input_string;
    MangoLibrary *          filterLibrary;
    MangoLibrary *          tagLibrary;
    MangoStringFactory *    string_factory;
    MangoParserContext      parser_context;

public:
    ParserTestFixture() :
        tokenizer(NULL),
        parser(NULL),
        loader(NULL),
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

        // register filters
        register_in_library(filterLibrary, string_factory, "add", mango_addfilter_default());

        // and register the "for" tag
        register_in_library(tagLibrary, string_factory, "for", mango_fortagparser_default());
    }

    static void register_in_library(MangoLibrary *library, MangoStringFactory *string_factory, const char *key, void *value)
    {
        MangoString *mkey = mango_stringfactory_new_string(string_factory, key, -1);
        mango_library_register(library, mkey, value);
        OBJ_DECREF(mkey);
    }

    virtual ~ParserTestFixture()
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

    MangoVariable *create_variable(const char *value,
                                   bool isQuoted, bool isNum,
                                   MangoVariable *next)
    {
        MangoString *varValue = mango_stringfactory_new_string(string_factory, value, -1);
        MangoVariable *var = mango_variable_new(varValue, isQuoted, next);
        var->isNumber = isNum;
        if (isNum)
        {
            var->intValue = atoi(value);
        }
        return var;
    }

    /**
     * Checkes that the parsed node matches what we are expecting.
     */
    virtual void CheckParsedNodeWith(int numNodes, ...)
    {
        MangoError *error   = NULL;
		MangoNode *node     = mango_parser_parse(&parser_context, &error);

        if (numNodes == 1)
        {
            va_list ap;
            va_start(ap, numNodes);
            MangoNode *expectedNode = va_arg(ap, MangoNode *);
            CHECK(OBJ_EQUALS(expectedNode, node));
            va_end(ap);
        }
        else if (numNodes > 1)
        {
            MangoNodeList *nodelist = (MangoNodeList *)node;
            int nodeCount       = mango_nodelist_childcount(nodelist);
            CHECK_EQUAL(nodeCount, numNodes);

            va_list ap;
            va_start(ap, numNodes);
            for (int i = 0;i < nodeCount;i++)
            {
                MangoNode *expectedNode = va_arg(ap, MangoNode *);
                MangoNode *childNode = mango_nodelist_childat(nodelist, i);
                CHECK(OBJ_EQUALS(expectedNode, childNode));
            }
            va_end(ap);
        }
        OBJ_DECREF(node);
        if (error != NULL)
        {
            printf("Error (%d): %s\n", error->errorCode, error->errorMessage);
            CHECK(false);
            mango_error_free(error);
        }
    }

    virtual void CheckParsedNodeForException(int code, std::string message)
    {
        MangoError *error   = NULL;
		MangoNode *node     = mango_parser_parse(&parser_context, &error);
        if (node != NULL)
            OBJ_DECREF(node);
        CHECK(error != NULL);
        if (error != NULL)
        {
            CHECK_EQUAL(code, error->errorCode);
            CHECK_EQUAL(message.c_str(), message.c_str());
            mango_error_free(error);
        }
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

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ParserTestFixture, TestParserCreate)
{
    SetUpWithInputString("");
    MangoError *error = NULL;
    MangoNode * nodeList = mango_parser_parse(&parser_context, &error);
    CHECK(NULL == nodeList);
    OBJ_DECREF(nodeList);
    if (error != NULL)
    {
        printf("Error (%d): %s\n", error->errorCode, error->errorMessage);
        CHECK(false);
        mango_error_free(error);
    }
}

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ParserTestFixture, TestOnlyFreeText)
{
    SetUpWithInputString("Hello World");
    MangoString *hello = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    CheckParsedNodeWith(1, mango_freetext_new(hello));
    OBJ_DECREF(hello);
}

TEST_FIXTURE(ParserTestFixture, TestFreeTextWithComments)
{
    SetUpWithInputString("Hello{# A Huge Comment#}World");
    MangoString *hello = mango_stringfactory_new_string(string_factory, "Hello", -1);
    MangoString *world = mango_stringfactory_new_string(string_factory, "World", -1);
    CheckParsedNodeWith(2, mango_freetext_new(hello), mango_freetext_new(world));
}

TEST_FIXTURE(ParserTestFixture, TestSingleVariable)
{
    SetUpWithInputString("{{variable}}");
    CheckParsedNodeWith(1, mango_varnode_new(create_variable("variable", false, false, NULL), NULL));
}

TEST_FIXTURE(ParserTestFixture, TestMultipleVariables)
{
    SetUpWithInputString("{{a.b.c}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_variable("a", false, false,
                                                create_variable("b", false, false,
                                                    create_variable("c", false, false, NULL))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleQuotedVariables)
{
    SetUpWithInputString("{{a.'b'.'c'}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_variable("a", false, false,
                                                create_variable("b", true, false,
                                                    create_variable("c", true, false, NULL))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithNumericIndexes)
{
    SetUpWithInputString("{{a.0.1.d}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_variable("a", false, false,
                                                create_variable("0", false, true,
                                                    create_variable("1", false, true,
                                                        create_variable("d", false, false, NULL)))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithQuotedIndexes)
{
    SetUpWithInputString("{{a.0.'1'.d}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_variable("a", false, false, 
                                                create_variable("0", false, true,
                                                    create_variable("1", true, true,
                                                        create_variable("d", false, false, NULL)))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestFiltersAreSingletons)
{
    MangoString *add = mango_stringfactory_new_string(string_factory, "add", -1);
    MangoFilter *f1 = (MangoFilter *)mango_filter_library_get(add, filterLibrary);
    MangoFilter *f2 = (MangoFilter *)mango_filter_library_get(add, filterLibrary);
    OBJ_DECREF(add);
    CHECK(f1 != NULL);
    CHECK(f2 != NULL);
    CHECK_EQUAL(f1, f2);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilter)
{
    SetUpWithInputString("{{a|add}}");
    MangoString *add = mango_stringfactory_new_string(string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)mango_filter_library_get(add, filterLibrary);
    MangoVarNode *expectedNode = mango_varnode_new(create_variable("a", false, false, NULL), NULL);
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneArgument)
{
    SetUpWithInputString("{{a|add:3}}");
    MangoString *add = mango_stringfactory_new_string(string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)mango_filter_library_get(add, filterLibrary);
    MangoVarNode *expectedNode = mango_varnode_new(create_variable("a", false, false, NULL), NULL);
    MangoFilterNode *filternode = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, filternode);
    mango_filternode_add_arg(filternode, create_variable("3", false, true, NULL));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneQuotedArgument)
{
    SetUpWithInputString("{{a|add:\"3\"}}");
    MangoString *add = mango_stringfactory_new_string(string_factory, "add", -1);
    MangoVarNode *expectedNode = mango_varnode_new(create_variable("a", false, false, NULL), NULL);
    MangoFilterNode *filternode = mango_filternode_new((MangoFilter *)mango_filter_library_get(add, NULL));
    mango_varnode_add_filter(expectedNode, filternode);
    mango_filternode_add_arg(filternode, create_variable("3", true, true, NULL));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithMultipleArguments)
{
    SetUpWithInputString("{{a|add:(3,'4',five)}}");
    MangoString *add = mango_stringfactory_new_string(string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)mango_filter_library_get(add, filterLibrary);
    MangoVarNode *expectedNode = mango_varnode_new(create_variable("a", false, false, NULL), NULL);
    MangoFilterNode *filternode = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, filternode);
    mango_filternode_add_arg(filternode, create_variable("3", false, true, NULL));
    mango_filternode_add_arg(filternode, create_variable("4", true, true, NULL));
    mango_filternode_add_arg(filternode, create_variable("five", false, false, NULL));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFilters)
{
    SetUpWithInputString("{{a|add|add|add}}");
    MangoString *add = mango_stringfactory_new_string(string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)mango_filter_library_get(add, filterLibrary);
    MangoVarNode *expectedNode = mango_varnode_new(create_variable("a", false, false, NULL), NULL);
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFiltersWithArguments)
{
    SetUpWithInputString("{{a|add|add:1|add:(2,'3')}}");
    MangoString *add = mango_stringfactory_new_string(string_factory, "add", -1);
    MangoFilter *addfilter      = (MangoFilter *)mango_filter_library_get(add, NULL);
    MangoVarNode *expectedNode     = mango_varnode_new(create_variable("a", false, false, NULL), NULL);

    MangoFilterNode *fnode1     = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, fnode1);

    MangoFilterNode *fnode2     = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, fnode2);
    mango_filternode_add_arg(fnode2, create_variable("1", false, true, NULL));

    MangoFilterNode *fnode3     = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, fnode3);
    mango_filternode_add_arg(fnode3, create_variable("2", false, true, NULL));
    mango_filternode_add_arg(fnode3, create_variable("3", true, true, NULL));

    CheckParsedNodeWith(1, expectedNode);
}

///////////////	Testing tags now!!!

TEST_FIXTURE(ParserTestFixture, TestDiscardingTokens)
{
    SetUpWithInputString("{% a b c %}Hello World");
    MangoError *error = NULL;
    mango_parser_discard_till_token(parser, TOKEN_CLOSE_TAG, &error);
    MangoString *hello = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    CheckParsedNodeWith(1, mango_freetext_new(hello));
    OBJ_DECREF(hello);
    if (error != NULL)
    {
        printf("Error (%d): %s\n", error->errorCode, error->errorMessage);
        CHECK(false);
        mango_error_free(error);
        CHECK(false);
    }
}

#if 0
TEST_FIXTURE(ParserTestFixture, TestSingleUnclosedTag)
{
    SetUpWithInputString("{% for a in listofas %}");
    CheckParsedNodeForException(-1, "End nodes were not found");
}

TEST_FIXTURE(ParserTestFixture, TestSimpleForTag)
{
    SetUpWithInputString("{% for a in listofas %}{%endfor%}");
    ForTagNode ftn = new ForTagNode(create_variable("listofas"));
    ftn.addItem(create_variable("a"));
    CheckParsedNodeWith(ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChild)
{
    SetUpWithInputString("{% for a in listofas %}Hello World{%endfor%}");
    ForTagNode ftn = new ForTagNode(create_variable("listofas"));
    ftn.addItem(create_variable("a"));
    ftn.childNodes = mango_freetext_new(mango_string_from_buffer("Hello World", -1));
    CheckParsedNodeWith(ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChildAndEmpty)
{
    SetUpWithInputString("{% for a in listofas %}Hello World{%empty%}Empty Content{%endfor%}");
    ForTagNode ftn = new ForTagNode(create_variable("listofas"));
    ftn.addItem(create_variable("a"));
    ftn.childNodes = mango_freetext_new(mango_string_from_buffer("Hello World", -1));
    ftn.emptyNodes = mango_freetext_new(mango_string_from_buffer("Empty Content", -1));
    CheckParsedNodeWith(ftn);
}

#endif

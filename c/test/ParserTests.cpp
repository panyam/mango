
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include "testutils.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

class ParserTestFixture
{
public:
    MangoContext *          context;
    MangoTokenizer *        tokenizer;
    MangoParser *           parser;
    StlInputSource *        input_source;
    std::string             input_string;

public:
    ParserTestFixture() :
        context(mango_context_new(NULL, NULL, NULL, NULL, NULL)),
        tokenizer(NULL),
        parser(NULL),
        input_source(NULL),
        input_string("")
    {
        // register filters
        register_in_library(context, context->filter_library, "add", (MangoObject *)mango_addfilter_default());

        // and register the "for" tag
        register_in_library(context, context->tag_library, "for", (MangoObject *)mango_fortagparser_default());
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
        mango_context_free(context);
    }

    MangoVar *create_var(const char *value,
                                   bool isQuoted, bool isNum,
                                   MangoVar *next)
    {
        MangoString *varValue = mango_stringfactory_new_string(context->string_factory, value, -1);
        MangoVar *var = mango_var_new(varValue, isQuoted, next);
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
        MangoNode *node     = mango_parser_parse(parser, context, &error);

        if (numNodes == 1)
        {
            va_list ap;
            va_start(ap, numNodes);
            MangoNode *expectedNode = va_arg(ap, MangoNode *);
            CHECK(OBJ_EQUALS(expectedNode, node));
            va_end(ap);

            // delete the expected node now that we are done with it
            OBJ_DECREF(expectedNode);
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

                // delete the expected node now that we are done with it
                OBJ_DECREF(expectedNode);
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
        MangoNode *node     = mango_parser_parse(parser, context, &error);
        if (node != NULL)
            OBJ_DECREF(node);
        CHECK(error != NULL);
        if (error != NULL)
        {
            CHECK_EQUAL(code, error->errorCode);
            CHECK_EQUAL(message.c_str(), error->errorMessage);
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
    }
};

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ParserTestFixture, TestParserCreate)
{
    SetUpWithInputString("");
    MangoError *error = NULL;
    MangoNode * nodeList = mango_parser_parse(parser, context, &error);
    CHECK(NULL == nodeList);
    OBJ_DECREF(nodeList);
    if (error != NULL)
    {
        printf("Error (%d): %s\n", error->errorCode, error->errorMessage);
        CHECK(false);
        mango_error_free(error);
    }
}

#if 0
/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ParserTestFixture, TestOnlyFreeText)
{
    SetUpWithInputString("Hello World");
    MangoString *hello = mango_stringfactory_new_string(context->string_factory, "Hello World", -1);
    CheckParsedNodeWith(1, mango_freetext_new(hello));
    OBJ_DECREF(hello);
}

TEST_FIXTURE(ParserTestFixture, TestFreeTextWithComments)
{
    SetUpWithInputString("Hello{# A Huge Comment#}World");
    MangoString *hello = mango_stringfactory_new_string(context->string_factory, "Hello", -1);
    MangoString *world = mango_stringfactory_new_string(context->string_factory, "World", -1);
    CheckParsedNodeWith(2, mango_freetext_new(hello), mango_freetext_new(world));
}

TEST_FIXTURE(ParserTestFixture, TestSingleVar)
{
    SetUpWithInputString("{{var}}");
    CheckParsedNodeWith(1, mango_varnode_new(create_var("var", false, false, NULL), NULL));
}

TEST_FIXTURE(ParserTestFixture, TestMultipleVars)
{
    SetUpWithInputString("{{a.b.c}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_var("a", false, false,
                                                create_var("b", false, false,
                                                    create_var("c", false, false, NULL))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleQuotedVars)
{
    SetUpWithInputString("{{a.'b'.'c'}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_var("a", false, false,
                                                create_var("b", true, false,
                                                    create_var("c", true, false, NULL))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVarWithNumericIndexes)
{
    SetUpWithInputString("{{a.0.1.d}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_var("a", false, false,
                                                create_var("0", false, true,
                                                    create_var("1", false, true,
                                                        create_var("d", false, false, NULL)))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVarWithQuotedIndexes)
{
    SetUpWithInputString("{{a.0.'1'.d}}");
    MangoNode *expectedNode = (MangoNode *)mango_varnode_new(
                                            create_var("a", false, false, 
                                                create_var("0", false, true,
                                                    create_var("1", true, true,
                                                        create_var("d", false, false, NULL)))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestFiltersAreSingletons)
{
    MangoString *add = mango_stringfactory_new_string(context->string_factory, "add", -1);
    MangoFilter *f1 = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    MangoFilter *f2 = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    OBJ_DECREF(add);
    CHECK(f1 != NULL);
    CHECK(f2 != NULL);
    CHECK_EQUAL(f1, f2);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilter)
{
    SetUpWithInputString("{{a|add}}");
    MangoString *add = mango_stringfactory_new_string(context->string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    MangoVarNode *expectedNode = mango_varnode_new(create_var("a", false, false, NULL), NULL);
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneArgument)
{
    SetUpWithInputString("{{a|add:3}}");
    MangoString *add = mango_stringfactory_new_string(context->string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    MangoVarNode *expectedNode = mango_varnode_new(create_var("a", false, false, NULL), NULL);
    MangoFilterNode *filternode = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, filternode);
    mango_filternode_add_arg(filternode, create_var("3", false, true, NULL));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneQuotedArgument)
{
    SetUpWithInputString("{{a|add:\"3\"}}");
    MangoString *add = mango_stringfactory_new_string(context->string_factory, "add", -1);
    MangoVarNode *expectedNode = mango_varnode_new(create_var("a", false, false, NULL), NULL);
    MangoFilter *addfilter = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    MangoFilterNode *filternode = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, filternode);
    mango_filternode_add_arg(filternode, create_var("3", true, true, NULL));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithMultipleArguments)
{
    SetUpWithInputString("{{a|add:(3,'4',five)}}");
    MangoString *add = mango_stringfactory_new_string(context->string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    MangoVarNode *expectedNode = mango_varnode_new(create_var("a", false, false, NULL), NULL);
    MangoFilterNode *filternode = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, filternode);
    mango_filternode_add_arg(filternode, create_var("3", false, true, NULL));
    mango_filternode_add_arg(filternode, create_var("4", true, true, NULL));
    mango_filternode_add_arg(filternode, create_var("five", false, false, NULL));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFilters)
{
    SetUpWithInputString("{{a|add|add|add}}");
    MangoString *add = mango_stringfactory_new_string(context->string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    MangoVarNode *expectedNode = mango_varnode_new(create_var("a", false, false, NULL), NULL);
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    mango_varnode_add_filter(expectedNode, mango_filternode_new(addfilter));
    OBJ_DECREF(add);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFiltersWithArguments)
{
    SetUpWithInputString("{{a|add|add:1|add:(2,'3')}}");
    MangoString *add = mango_stringfactory_new_string(context->string_factory, "add", -1);
    MangoFilter *addfilter = (MangoFilter *)OBJ_GETSTRATTR(context->filter_library, add);
    MangoVarNode *expectedNode     = mango_varnode_new(create_var("a", false, false, NULL), NULL);

    MangoFilterNode *fnode1     = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, fnode1);

    MangoFilterNode *fnode2     = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, fnode2);
    mango_filternode_add_arg(fnode2, create_var("1", false, true, NULL));

    MangoFilterNode *fnode3     = mango_filternode_new(addfilter);
    mango_varnode_add_filter(expectedNode, fnode3);
    mango_filternode_add_arg(fnode3, create_var("2", false, true, NULL));
    mango_filternode_add_arg(fnode3, create_var("3", true, true, NULL));

    CheckParsedNodeWith(1, expectedNode);
}

///////////////    Testing tags now!!!

TEST_FIXTURE(ParserTestFixture, TestDiscardingTokens)
{
    SetUpWithInputString("{% a b c %}Hello World");
    MangoError *error = NULL;
    mango_parser_discard_till_token(parser, TOKEN_CLOSE_TAG, &error);
    MangoString *hello = mango_stringfactory_new_string(context->string_factory, "Hello World", -1);
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

TEST_FIXTURE(ParserTestFixture, TestSingleUnclosedTag)
{
    SetUpWithInputString("{% for a in listofas %}");
    CheckParsedNodeForException(-1, "Unexpected EOF encountered without reaching end node.");
}

TEST_FIXTURE(ParserTestFixture, TestSimpleForTag)
{
    SetUpWithInputString("{% for a in listofas %}{%endfor%}");
    MangoForTagNode *ftn = mango_fortag_new(create_var("listofas", false, false, NULL), NULL, NULL);
    mango_fortag_add_item(ftn, create_var("a", false, false, NULL));
    CheckParsedNodeWith(1, ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChild)
{
    SetUpWithInputString("{% for a in listofas %}Hello World{%endfor%}");
    MangoForTagNode *ftn = mango_fortag_new(create_var("listofas", false, false, NULL), NULL, NULL);
    mango_fortag_add_item(ftn, create_var("a", false, false, NULL));
    ftn->childNodes = (MangoNode *)mango_freetext_new(mango_stringfactory_new_string(context->string_factory, "Hello World", -1));
    CheckParsedNodeWith(1, ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChildAndEmpty)
{
    SetUpWithInputString("{% for a in listofas %}Hello World{%empty%}Empty Content{%endfor%}");
    MangoForTagNode *ftn = mango_fortag_new(create_var("listofas", false, false, NULL), NULL, NULL);
    mango_fortag_add_item(ftn, create_var("a", false, false, NULL));
    ftn->childNodes = (MangoNode *)mango_freetext_new(mango_stringfactory_new_string(context->string_factory, "Hello World", -1));
    ftn->emptyNodes = (MangoNode *)mango_freetext_new(mango_stringfactory_new_string(context->string_factory, "Empty Content", -1));
    CheckParsedNodeWith(1, ftn);
}


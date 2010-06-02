
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include "testutils.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

/**
 * Suite for testing expression parsing (as used in if tags)
 */
class ExprTestFixture
{
public:
    MangoContext *          context;
    MangoTokenizer *        tokenizer;
    MangoParser *           parser;
    StlInputSource *        input_source;
    std::string             input_string;

public:
    ExprTestFixture() :
        context(mango_context_new(NULL, NULL, NULL, NULL, NULL)),
        tokenizer(NULL),
        parser(NULL),
        input_source(NULL),
        input_string("")
    {
        // register filters
        register_in_library(context->filter_library, "add", (MangoObject *)mango_addfilter_default());

        // and register the "for" tag
        register_in_library(context->tag_library, "for", (MangoObject *)mango_fortagparser_default());
    }

    virtual ~ExprTestFixture()
    {
        if (input_source != NULL)
        {
            if (input_source->inputStream != NULL)
                delete input_source->inputStream;
            free_stl_input_source(input_source);
            input_source = NULL;
        }

        if (parser != NULL) 
        {
            mango_parser_free(parser);
            parser = NULL;
        }

        if (tokenizer != NULL) 
        {
            mango_tokenizer_free(tokenizer);
            tokenizer = NULL;
        }

        mango_context_free(context);
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
        MangoNode *node     = mango_parser_parse(&parser_context, &error);
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
        tokenizer->_insideNode = NODETYPE_TAG;
        parser = mango_parser_new(tokenizer);
        parser_context.parser = parser;
    }
};

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ExprTestFixture, TestExprCreate)
{
}


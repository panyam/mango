
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <stdarg.h>

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

public:
    ParserTestFixture() :
        tokenizer(NULL),
        parser(NULL),
        loader(NULL),
        input_source(NULL),
        input_string(""),
        filterLibrary(mango_filter_library_singleton()),
        tagLibrary(mango_tag_library_singleton())
    {
    }

    virtual ~ParserTestFixture()
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
    }

    /**
     * Checkes that the parsed node matches what we are expecting.
     * @param expectedNode
     */
    virtual void CheckParsedNodeWith(int numNodes, ...)
    {
        MangoError *error   = NULL;
		MangoNode *node     = mango_parser_parse(parser, loader, &error);
        int nodeCount       = node->nodeCount(node->nodeData);
        if (nodeCount > 0)
        {
            CHECK_EQUAL(nodeCount, numNodes);

            va_list ap;
            va_start(ap, numNodes);
            for (int i = 0;i < nodeCount;i++)
            {
                MangoNode *expectedNode = va_arg(ap, MangoNode *);
                MangoNode *childNode = node->getChildNode(node->nodeData, i);
                CHECK(mango_node_equal(expectedNode, childNode));
            }
            va_end(ap);
        }
        else if (node != NULL)
        {
            va_list ap;
            va_start(ap, numNodes);
            MangoNode *expectedNode = va_arg(ap, MangoNode *);
            CHECK_EQUAL(numNodes, 1);
            CHECK(mango_node_equal(expectedNode, node));
            va_end(ap);
        }
        else
        {
            if (numNodes == 1)
            {
                va_list ap;
                va_start(ap, numNodes);
                MangoNode *expectedNode = va_arg(ap, MangoNode *);
                CHECK(NULL == expectedNode);
                va_end(ap);
            }
            else if (numNodes > 1)
            {
                CHECK(false);
            }
        }
        mango_node_free(node);
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
		MangoNode *node     = mango_parser_parse(parser, loader, &error);
        if (node != NULL)
            mango_node_free(node);
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
        DeleteFixture();
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
    MangoNode * nodeList = mango_parser_parse(parser, loader, &error);
    CHECK(NULL == nodeList);
    mango_node_free(nodeList);
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
    CheckParsedNodeWith(1, mango_freetext_new(mango_string_from_buffer("Hello World", -1)));
}

TEST_FIXTURE(ParserTestFixture, TestFreeTextWithComments)
{
    SetUpWithInputString("Hello{# A Huge Comment#}World");
    CheckParsedNodeWith(2, 
                        mango_freetext_new(mango_string_from_buffer("Hello", -1)), 
                        mango_freetext_new(mango_string_from_buffer("World", -1)));
}

MangoVariable *create_variable(const char *value, bool isQuoted, bool isNum, MangoVariable *next)
{
    MangoVariable *var = mango_variable_new(mango_string_from_buffer(value, -1), isQuoted, next);
    var->isNumber = isNum;
    if (isNum)
    {
        var->intValue = atoi(value);
    }
    return var;
}

TEST_FIXTURE(ParserTestFixture, TestSingleVariable)
{
    SetUpWithInputString("{{variable}}");
    CheckParsedNodeWith(1, mango_varnode_new(create_variable("variable", false, false, NULL), NULL));
}

TEST_FIXTURE(ParserTestFixture, TestMultipleVariables)
{
    SetUpWithInputString("{{a.b.c}}");
    MangoNode *expectedNode = mango_varnode_new(
                                create_variable("a", false, false,
                                    create_variable("b", false, false,
                                        create_variable("c", false, false, NULL))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleQuotedVariables)
{
    SetUpWithInputString("{{a.'b'.'c'}}");
    MangoNode *expectedNode = mango_varnode_new(
                                create_variable("a", false, false,
                                    create_variable("b", true, false,
                                        create_variable("c", true, false, NULL))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithNumericIndexes)
{
    SetUpWithInputString("{{a.0.1.d}}");
    MangoNode *expectedNode = mango_varnode_new(
                                create_variable("a", false, false,
                                    create_variable("0", false, true,
                                        create_variable("1", false, true,
                                            create_variable("d", false, false, NULL)))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithQuotedIndexes)
{
    SetUpWithInputString("{{a.0.'1'.d}}");
    MangoNode *expectedNode = mango_varnode_new(
                                create_variable("a", false, false, 
                                    create_variable("0", false, true,
                                        create_variable("1", true, true,
                                            create_variable("d", false, false, NULL)))), NULL);
    CheckParsedNodeWith(1, expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestFiltersAreSingletons)
{
    MangoString *add = mango_string_from_buffer("add", 3);
    MangoFilter *f1 = (MangoFilter *)mango_library_new_instance(filterLibrary, add);
    MangoFilter *f2 = (MangoFilter *)mango_library_new_instance(tagLibrary, add);
    mango_string_free(add);
    CHECK_EQUAL(f1, f2);
}

#if 0
TEST_FIXTURE(ParserTestFixture, TestSingleFilter)
{
    SetUpWithInputString("{{a|add}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, NULL));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    CheckParsedNodeWith(expectedNode);
}


TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneArgument)
{
    SetUpWithInputString("{{a|add:3}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, NULL));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("3", false));
    expectedNode.addFilterNode(addNode);
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneQuotedArgument)
{
    SetUpWithInputString("{{a|add:\"3\"}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, NULL));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("3", true));
    expectedNode.addFilterNode(addNode);
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithMultipleArguments)
{
    SetUpWithInputString("{{a|add:(3,'4',five)}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, NULL));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("3", false));
    addNode.addArgument(new Variable("4", true));
    addNode.addArgument(new Variable("five", false));
    expectedNode.addFilterNode(addNode);
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFilters)
{
    SetUpWithInputString("{{a|add|add|add}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, NULL));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFiltersWithArguments)
{
    SetUpWithInputString("{{a|add|add:1|add:(2,'3')}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, NULL));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));

    addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("1", false));
    expectedNode.addFilterNode(addNode);		

    addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("2", false));
    addNode.addArgument(new Variable("3", true));
    expectedNode.addFilterNode(addNode);		

    CheckParsedNodeWith(expectedNode);
}

///////////////	Testing tags now!!!

TEST_FIXTURE(ParserTestFixture, TestSingleUnclosedTag)
{
    SetUpWithInputString("{% for a in listofas %}");
    CheckParsedNodeForException(-1, "End nodes were not found");
}

TEST_FIXTURE(ParserTestFixture, TestDiscardingTokens)
{
    SetUpWithInputString("{% a b c %}Hello World");
    try {
        parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
        CheckParsedNodeWith(mango_freetext_new(mango_string_from_buffer("Hello World", -1)));
    } catch (ParserException e) {
        e.printStackTrace();
    }
}

TEST_FIXTURE(ParserTestFixture, TestSimpleForTag)
{
    SetUpWithInputString("{% for a in listofas %}{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    CheckParsedNodeWith(ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChild)
{
    SetUpWithInputString("{% for a in listofas %}Hello World{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    ftn.childNodes = mango_freetext_new(mango_string_from_buffer("Hello World", -1));
    CheckParsedNodeWith(ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChildAndEmpty)
{
    SetUpWithInputString("{% for a in listofas %}Hello World{%empty%}Empty Content{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    ftn.childNodes = mango_freetext_new(mango_string_from_buffer("Hello World", -1));
    ftn.emptyNodes = mango_freetext_new(mango_string_from_buffer("Empty Content", -1));
    CheckParsedNodeWith(ftn);
}

#endif

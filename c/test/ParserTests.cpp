
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
    MangoLibrary *          filterLibrary;
    MangoLibrary *          tagLibrary;
    MangoTemplateLoader *   loader;
    StlInputSource *        input_source;
    std::string             input_string;

public:
    ParserTestFixture() :
        tokenizer(NULL),
        parser(NULL),
        filterLibrary(NULL),
        tagLibrary(NULL),
        loader(NULL),
        input_source(NULL),
        input_string("")
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

        if (filterLibrary != NULL) 
        {
            mango_library_free(filterLibrary);
            filterLibrary = NULL;
        }

        if (tagLibrary != NULL) 
        {
            mango_library_free(tagLibrary);
            tagLibrary = NULL;
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
        filterLibrary = mango_library_new("filters");
        tagLibrary = mango_library_new("tags");
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

MangoVariable *create_variable(const char *value, bool isQuoted, MangoVariable *next)
{
    return mango_variable_new(mango_string_from_buffer(value, -1), isQuoted, next);
}

TEST_FIXTURE(ParserTestFixture, TestSingleVariable)
{
    SetUpWithInputString("{{variable}}");
    CheckParsedNodeWith(1, mango_varnode_new(create_variable("variable", false, NULL), NULL));
}

#if 0
TEST_FIXTURE(ParserTestFixture, TestMultipleVariables)
{
    SetUpWithInputString("{{a.b.c}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("b",
                                                        new Variable("c", NULL))), NULL);
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleQuotedVariables)
{
    SetUpWithInputString("{{a.'b'.'c'}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("b", true,
                                                        new Variable("c", true, NULL))), NULL);
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithNumericIndexes)
{
    SetUpWithInputString("{{a.0.1.d}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("0", 
                                                        new Variable("1", 
                                                            new Variable("d", NULL)))), NULL);
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithQuotedIndexes)
{
    SetUpWithInputString("{{a.0.'1'.d}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("0", 
                                                        new Variable("1", true,
                                                            new Variable("d", NULL)))), NULL);
    CheckParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestFiltersAreSingletons)
{
    Filter f1 = filterLibrary.makeNewInstance("add");
    Filter f2 = filterLibrary.makeNewInstance("add");
    CHECK_EQUAL("Filters are not equal as should be with singletons", f1, f2);
}

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

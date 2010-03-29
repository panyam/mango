
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>

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
        input_string(NULL)
    {
    }

    ~ParserTestFixture()
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

protected:
    void setUpWithInputString(const std::string &input)
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

#if 0

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ParserTestFixture, TestParserCreate)
{
    setUpWithInputString("");
    try {
        Node nodeList = parser.parse(loader);
        assertEquals("Node should be null for empty string", null, nodeList);
    } catch (ParserException e) {
        e.printStackTrace();
    }
}

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ParserTestFixture, TestOnlyFreeText)
{
    setUpWithInputString("Hello World");
    checkParsedNodeWith(new FreeTextNode("Hello World"));
}

TEST_FIXTURE(ParserTestFixture, TestFreeTextWithComments)
{
    setUpWithInputString("Hello{# A Huge Comment#}World");
    checkParsedNodeWith(new FreeTextNode("Hello"), 
                        new FreeTextNode("World"));
}

TEST_FIXTURE(ParserTestFixture, TestSingleVariable)
{
    setUpWithInputString("{{variable}}");
    checkParsedNodeWith(new VariableNode(new Variable("variable", false, null)));
}

TEST_FIXTURE(ParserTestFixture, TestMultipleVariables)
{
    setUpWithInputString("{{a.b.c}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("b",
                                                        new Variable("c", null))), null);
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleQuotedVariables)
{
    setUpWithInputString("{{a.'b'.'c'}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("b", true,
                                                        new Variable("c", true, null))), null);
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithNumericIndexes)
{
    setUpWithInputString("{{a.0.1.d}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("0", 
                                                        new Variable("1", 
                                                            new Variable("d", null)))), null);
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestVariableWithQuotedIndexes)
{
    setUpWithInputString("{{a.0.'1'.d}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", 
                                                    new Variable("0", 
                                                        new Variable("1", true,
                                                            new Variable("d", null)))), null);
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestFiltersAreSingletons)
{
    Filter f1 = filterLibrary.makeNewInstance("add");
    Filter f2 = filterLibrary.makeNewInstance("add");
    assertEquals("Filters are not equal as should be with singletons", f1, f2);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilter)
{
    setUpWithInputString("{{a|add}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    checkParsedNodeWith(expectedNode);
}


TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneArgument)
{
    setUpWithInputString("{{a|add:3}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("3", false));
    expectedNode.addFilterNode(addNode);
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithOneQuotedArgument)
{
    setUpWithInputString("{{a|add:\"3\"}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("3", true));
    expectedNode.addFilterNode(addNode);
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestSingleFilterWithMultipleArguments)
{
    setUpWithInputString("{{a|add:(3,'4',five)}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("3", false));
    addNode.addArgument(new Variable("4", true));
    addNode.addArgument(new Variable("five", false));
    expectedNode.addFilterNode(addNode);
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFilters)
{
    setUpWithInputString("{{a|add|add|add}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
    checkParsedNodeWith(expectedNode);
}

TEST_FIXTURE(ParserTestFixture, TestMultipleFiltersWithArguments)
{
    setUpWithInputString("{{a|add|add:1|add:(2,'3')}}");
    VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
    FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));

    addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("1", false));
    expectedNode.addFilterNode(addNode);		

    addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
    addNode.addArgument(new Variable("2", false));
    addNode.addArgument(new Variable("3", true));
    expectedNode.addFilterNode(addNode);		

    checkParsedNodeWith(expectedNode);
}

///////////////	Testing tags now!!!

TEST_FIXTURE(ParserTestFixture, TestSingleUnclosedTag)
{
    setUpWithInputString("{% for a in listofas %}");
    checkParsedNodeForException(-1, "End nodes were not found");
}

TEST_FIXTURE(ParserTestFixture, TestDiscardingTokens)
{
    setUpWithInputString("{% a b c %}Hello World");
    try {
        parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
        checkParsedNodeWith(new FreeTextNode("Hello World"));
    } catch (ParserException e) {
        e.printStackTrace();
    }
}

TEST_FIXTURE(ParserTestFixture, TestSimpleForTag)
{
    setUpWithInputString("{% for a in listofas %}{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    checkParsedNodeWith(ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChild)
{
    setUpWithInputString("{% for a in listofas %}Hello World{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    ftn.childNodes = new FreeTextNode("Hello World");
    checkParsedNodeWith(ftn);
}

TEST_FIXTURE(ParserTestFixture, TestForTagWithChildAndEmpty)
{
    setUpWithInputString("{% for a in listofas %}Hello World{%empty%}Empty Content{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    ftn.childNodes = new FreeTextNode("Hello World");
    ftn.emptyNodes = new FreeTextNode("Empty Content");
    checkParsedNodeWith(ftn);
}

#endif

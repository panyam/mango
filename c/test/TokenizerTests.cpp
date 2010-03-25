
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlstringtoken.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>

class TokenizerTestFixture
{
public:
    class ExpectedToken
    {
    public:
        MangoTokenType  tokenType;
        std::string     tokenValue;

        ExpectedToken(MangoTokenType tType, const std::string &tValue) : tokenType(tType), tokenValue(tValue)
        {
        }
    };

public:
    std::vector<ExpectedToken>  expectedTokens;
    MangoTokenizer *            tokenizer;
    StlInputSource *            stl_input_source;
    std::string                 input_string;

public:
    TokenizerTestFixture() : tokenizer(NULL), stl_input_source(NULL)
    {
    }

    ~TokenizerTestFixture()
    {
        DeleteTokenizer();

        expectedTokens.clear();
    }

    void DeleteTokenizer()
    {
        if (stl_input_source != NULL)
        {
            if (stl_input_source->inputStream != NULL)
                delete stl_input_source->inputStream;
            free_stl_input_source(stl_input_source);
        }

        if (tokenizer != NULL)
            delete tokenizer;

        tokenizer = NULL;
        stl_input_source = NULL;
    }

protected:
    void setUpWithInputString(const std::string &input)
    {
        DeleteTokenizer();
        input_string = input;
        stl_input_source = new_stl_input_source(new std::istringstream(input));
        tokenizer = mango_tokenizer_create((MangoInputSource *)stl_input_source);
    }
    
    void expectToken(MangoTokenType tType, const std::string &value = "")
    {
        expectedTokens.push_back(ExpectedToken(tType, value));
    }

    void satisfyExpectation(int expectation)
    {
        MangoToken *token = stl_string_token_new(TOKEN_UNKNOWN, "");
        CHECK(mango_tokenizer_has_tokens(tokenizer));
        BOOL foundToken;
        CHECK((foundToken = mango_tokenizer_next_token(tokenizer, token, NULL)));
        ExpectedToken expectedToken = expectedTokens.at(expectation);
        CHECK_EQUAL(expectedToken.tokenType, token->tokenType);
        if (expectedToken.tokenValue.size() != 0)
        {
            std::string expectedTokenValue  = expectedToken.tokenValue;
            std::string tokenValue(((StlStringTokenData *)token->tokenData)->tokenValue.str());
            CHECK_EQUAL(expectedTokenValue, tokenValue);
        }
    }

    /**
     * Goes through the expectations and ensures that all expectations
     * on the tokens extracted are satisfied.
     */
    void satisfyExpectations()
    {
        for (int expectation = 0, numExpectations = expectedTokens.size();
            expectation < numExpectations; ++expectation)
        {
        	satisfyExpectation(expectation);
        }
    }
};

TEST_FIXTURE(TokenizerTestFixture, TestTokenizerCreation)
{
    setUpWithInputString("Hello World");
}

/**
 * test case to see if an empty string returns an EOF token
 */
TEST_FIXTURE(TokenizerTestFixture, TestEmptyTokenizer)
{
    setUpWithInputString("");
    satisfyExpectations();
}

/**
 * test case to see if an empty string returns an EOF token
 */
TEST_FIXTURE(TokenizerTestFixture, TestOnlyFreeText)
{
    setUpWithInputString("Hello World");
    expectToken(TOKEN_FREETEXT, "Hello World");
    satisfyExpectations();
}

TEST_FIXTURE(TokenizerTestFixture, TestEmptyCommentOnly)
{
	setUpWithInputString("{##}");
	expectToken(TOKEN_COMMENT);
    satisfyExpectations();
}

TEST_FIXTURE(TokenizerTestFixture, TestOnlyComments)
{
	setUpWithInputString("{#A comment#}");
	expectToken(TOKEN_COMMENT);
    satisfyExpectations();
}

TEST_FIXTURE(TokenizerTestFixture, TestCommentsWithSpaces)
{
	setUpWithInputString("{#   A comment  with spaces  #}");
	expectToken(TOKEN_COMMENT);
    satisfyExpectations();
}


TEST_FIXTURE(TokenizerTestFixture, TestMultiLineComments)
{
	setUpWithInputString("{#   A comment  \nwith \nspaces  #}");
	expectToken(TOKEN_COMMENT);
    satisfyExpectations();
}

TEST_FIXTURE(TokenizerTestFixture, TestCommentsBetweenText)
{
	setUpWithInputString("Part1OfText{#TheComment#}Part2OfText");
	expectToken(TOKEN_FREETEXT, "Part1OfText");
	expectToken(TOKEN_COMMENT);
	expectToken(TOKEN_FREETEXT, "Part2OfText");
    satisfyExpectations();
}

TEST_FIXTURE(TokenizerTestFixture, TestUnterminatedComments)
{
	setUpWithInputString("{#This comment has no close token");
	expectToken(TOKEN_ERROR);
    satisfyExpectations();
}


// tests empty nodes
TEST_FIXTURE(TokenizerTestFixture, TestEmptyNodes)
{
	setUpWithInputString("{{}}{%%}{##}");
	expectToken(TOKEN_OPEN_VARIABLE);
	expectToken(TOKEN_CLOSE_VARIABLE);
	expectToken(TOKEN_OPEN_TAG);
	expectToken(TOKEN_CLOSE_TAG);
	expectToken(TOKEN_COMMENT);
    satisfyExpectations();
}


// tests to do with variables and tags
TEST_FIXTURE(TokenizerTestFixture, TestSingleVariable)
{
	setUpWithInputString("{{variable}}");
	expectToken(TOKEN_OPEN_VARIABLE);
	expectToken(TOKEN_IDENTIFIER, "variable");
	expectToken(TOKEN_CLOSE_VARIABLE);
    satisfyExpectations();
}

// tests to do with variables and tags
TEST_FIXTURE(TokenizerTestFixture, TestSingleVariableWithSpaces)
{
	setUpWithInputString("{{ variable }}");
	expectToken(TOKEN_OPEN_VARIABLE);
	expectToken(TOKEN_IDENTIFIER, "variable");
	expectToken(TOKEN_CLOSE_VARIABLE);
    satisfyExpectations();
}

// tests to do with variables and tags
TEST_FIXTURE(TokenizerTestFixture, TestMultipleIdentifiers)
{
	setUpWithInputString("{{ abc  de f }}");
	expectToken(TOKEN_OPEN_VARIABLE);
	expectToken(TOKEN_IDENTIFIER, "abc");
	expectToken(TOKEN_IDENTIFIER, "de");
	expectToken(TOKEN_IDENTIFIER, "f");
	expectToken(TOKEN_CLOSE_VARIABLE);
    satisfyExpectations();
}

TEST_FIXTURE(TokenizerTestFixture, TestMultipleTokensInNode)
{
	setUpWithInputString("{{ a . b . c. d | filter:( a, b, c) }}");
	expectToken(TOKEN_OPEN_VARIABLE);
	expectToken(TOKEN_IDENTIFIER, "a");
	expectToken(TOKEN_DOT);
	expectToken(TOKEN_IDENTIFIER, "b");
	expectToken(TOKEN_DOT);
	expectToken(TOKEN_IDENTIFIER, "c");
	expectToken(TOKEN_DOT);
	expectToken(TOKEN_IDENTIFIER, "d");
	expectToken(TOKEN_FILTER_SEPERATOR);
	expectToken(TOKEN_IDENTIFIER, "filter");
	expectToken(TOKEN_COLON);
	expectToken(TOKEN_OPEN_PAREN);
	expectToken(TOKEN_IDENTIFIER, "a");
	expectToken(TOKEN_COMA);
	expectToken(TOKEN_IDENTIFIER, "b");
	expectToken(TOKEN_COMA);
	expectToken(TOKEN_IDENTIFIER, "c");
	expectToken(TOKEN_CLOSE_PAREN);
	// expectToken(TOKEN_ERROR);
	expectToken(TOKEN_CLOSE_VARIABLE);
    satisfyExpectations();
}


TEST_FIXTURE(TokenizerTestFixture, TestTwoEmptyTags)
{
    setUpWithInputString("{% %}{% %}");
    expectToken(TOKEN_OPEN_TAG);
    expectToken(TOKEN_CLOSE_TAG);
    expectToken(TOKEN_OPEN_TAG);
    expectToken(TOKEN_CLOSE_TAG);
    satisfyExpectations();
}

TEST_FIXTURE(TokenizerTestFixture, TestFreeTextThenTag)
{
    setUpWithInputString("Hello World{% %}");
    expectToken(TOKEN_FREETEXT);
    expectToken(TOKEN_OPEN_TAG);
    expectToken(TOKEN_CLOSE_TAG);
    satisfyExpectations();
}


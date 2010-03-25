
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlstringtoken.h"
#include <vector>

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

public:
    TokenizerTestFixture() : tokenizer(NULL)
    {
    }

    ~TokenizerTestFixture()
    {
        if (tokenizer != NULL)
            delete tokenizer;
    }

protected:
    void satisfyExpectation(int expectation)
    {
    	StlStringToken token;
        init_stl_string_token(&token);
        CHECK(mango_tokenizer_has_tokens(tokenizer));
        BOOL foundToken;
        CHECK((foundToken = mango_tokenizer_next_token(tokenizer, ((MangoToken *)&token))));
        ExpectedToken expectedToken = expectedTokens.at(expectation);
        CHECK_EQUAL(expectedToken.tokenType, token.tokenBase.tokenType);
        if (expectedToken.tokenValue.size() != 0)
        {
            std::string expectedTokenValue  = expectedToken.tokenValue;
            std::string tokenValue(token.tokenValue.str());
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

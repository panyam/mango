//
//  TokenizerTests.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 31/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "TokenizerTests.h"

@implementation ExpectedToken

@synthesize tokenType;
@synthesize tokenValue;

+ (id) fromExpectation:(TokenType)type
                 value:(NSString *)value
{
    ExpectedToken *expectation = [[ExpectedToken alloc] init];
    expectation->tokenType = type;
    expectation->tokenValue = [value copy];
    return expectation;
}

- (BOOL) tokenMatches:(Token *)token
{
    return tokenType == token.tokenType &&
           (tokenValue == nil || ([tokenValue compare:token.tokenValue] == NSOrderedSame));
}

- (void) dealloc
{
    [tokenValue release];
    [super dealloc];
}

@end

@implementation TokenizerTests

- (void) setUp
{
	expectedTokens = [[NSMutableArray alloc] init];
}

- (void) setUpWithInputString:(NSString *)input
{
	tokenizer = [Tokenizer allocFromString:input];
}

- (void) tearDown
{
    [tokenizer release];
	[expectedTokens removeAllObjects];
	[expectedTokens release];
}

/**
 * Add an expectation for this token to be found
 * so when we do a tokenize, the expectations in this order need to be
 * satisfied.
 */
- (void) expectToken:(TokenType)type value:(NSString *)value
{
	ExpectedToken *expectedToken = [ExpectedToken fromExpectation:type value:value];
    [expectedTokens addObject:expectedToken];
	[expectedToken release];
}

/**
 * Goes through the expectations and ensures that all expectations
 * on the tokens extracted are satisfied.
 */
- (void) satisfyExpectations
{
	Token *token = [[Token alloc] init];
	for (int expectation = 0, numExpectations = [expectedTokens count];
		expectation < numExpectations; ++expectation)
	{
		STAssertTrue([tokenizer hasTokensAvailable], @"No tokens left, but expectations left.");
		BOOL foundToken = [tokenizer nextToken:token];
		STAssertTrue(foundToken, @"No tokens left, but expectations left.");
        ExpectedToken *expectedToken = [expectedTokens objectAtIndex:expectation];
		STAssertTrue(expectedToken.tokenType == token.tokenType, 
					 @"Expectation: %d, Expected TokenType: %d, But Found: %d", expectation, expectedToken.tokenType, token.tokenType);
		if (expectedToken.tokenValue != nil)
		{
			STAssertTrue([expectedToken.tokenValue compare:token.tokenValue] == NSOrderedSame, 
						 @"Expectation: %d, Expected TokenValue: '%@', But Found: '%@'", expectation, expectedToken.tokenValue, token.tokenValue);
		}
	}
	[token release];
}

- (void) testTokenizerAllocFromString
{
    [self setUpWithInputString:@"Hello World"];
}

/**
 * test case to see if an empty string returns an EOF token
 */
- (void) testEmptyTokenizer
{
    [self setUpWithInputString:@""];
    [self satisfyExpectations];
}


/**
 * test case to see if an empty string returns an EOF token
 */
- (void) testOnlyFreeText
{
    [self setUpWithInputString:@"Hello World"];
	[self expectToken:TOKEN_FREETEXT value:@"Hello World"];
    [self satisfyExpectations];
}


- (void) testEmptyCommentOnly
{
	[self setUpWithInputString:@"{##}"];
	[self expectToken:TOKEN_COMMENT value:nil];
    [self satisfyExpectations];
}

- (void) testOnlyComments
{
	[self setUpWithInputString:@"{#A comment#}"];
	[self expectToken:TOKEN_COMMENT value:nil];
    [self satisfyExpectations];
}

- (void) testCommentsWithSpaces
{
	[self setUpWithInputString:@"{#   A comment  with spaces  #}"];
	[self expectToken:TOKEN_COMMENT value:nil];
    [self satisfyExpectations];
}


- (void) testMultiLineComments
{
	[self setUpWithInputString:@"{#   A comment  \nwith \nspaces  #}"];
	[self expectToken:TOKEN_COMMENT value:nil];
    [self satisfyExpectations];
}

- (void) testCommentsBetweenText
{
	[self setUpWithInputString:@"Part1OfText{#TheComment#}Part2OfText"];
	[self expectToken:TOKEN_FREETEXT value:@"Part1OfText"];
	[self expectToken:TOKEN_COMMENT value:nil];
	[self expectToken:TOKEN_FREETEXT value:@"Part2OfText"];
    [self satisfyExpectations];
}

- (void) testUnterminatedComments
{
	[self setUpWithInputString:@"{#This comment has no close token"];
	[self expectToken:TOKEN_ERROR value:nil];
    [self satisfyExpectations];
}


// tests empty nodes
- (void) testEmptyNodes
{
	[self setUpWithInputString:@"{{}}{%%}{##}"];
	[self expectToken:TOKEN_OPEN_VARIABLE value:nil];
	[self expectToken:TOKEN_CLOSE_VARIABLE value:nil];
	[self expectToken:TOKEN_OPEN_TAG value:nil];
	[self expectToken:TOKEN_CLOSE_TAG value:nil];
	[self expectToken:TOKEN_COMMENT value:nil];
    [self satisfyExpectations];
}



// tests to do with variables and tags
- (void) testSingleVariable
{
	[self setUpWithInputString:@"{{variable}}"];
	[self expectToken:TOKEN_OPEN_VARIABLE value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"variable"];
	[self expectToken:TOKEN_CLOSE_VARIABLE value:nil];
    [self satisfyExpectations];
}

// tests to do with variables and tags
- (void) testSingleVariableWithSpaces
{
	[self setUpWithInputString:@"{{ variable }}"];
	[self expectToken:TOKEN_OPEN_VARIABLE value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"variable"];
	[self expectToken:TOKEN_CLOSE_VARIABLE value:nil];
    [self satisfyExpectations];
}

// tests to do with variables and tags
- (void) testMultipleIdentifiers
{
	[self setUpWithInputString:@"{{ abc  de f }}"];
	[self expectToken:TOKEN_OPEN_VARIABLE value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"abc"];
	[self expectToken:TOKEN_IDENTIFIER value:@"de"];
	[self expectToken:TOKEN_IDENTIFIER value:@"f"];
	[self expectToken:TOKEN_CLOSE_VARIABLE value:nil];
    [self satisfyExpectations];
}


- (void) testMultipleTokensInNode
{
	[self setUpWithInputString:@"{{ a . b . c. d | filter:( a, b, c) }}"];
	[self expectToken:TOKEN_OPEN_VARIABLE value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"a"];
	[self expectToken:TOKEN_DOT value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"b"];
	[self expectToken:TOKEN_DOT value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"c"];
	[self expectToken:TOKEN_DOT value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"d"];
	[self expectToken:TOKEN_FILTER_SEPERATOR value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"filter"];
	[self expectToken:TOKEN_COLON value:nil];
	[self expectToken:TOKEN_OPEN_PAREN value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"a"];
	[self expectToken:TOKEN_COMA value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"b"];
	[self expectToken:TOKEN_COMA value:nil];
	[self expectToken:TOKEN_IDENTIFIER value:@"c"];
	[self expectToken:TOKEN_CLOSE_PAREN value:nil];
	// [self expectToken:TOKEN_ERROR value:nil];
	[self expectToken:TOKEN_CLOSE_VARIABLE value:nil];
    [self satisfyExpectations];
}


- (void) testTwoEmptyTags
{
    [self setUpWithInputString:@"{% %}{% %}"];
    [self expectToken:TOKEN_OPEN_TAG value:nil];
    [self expectToken:TOKEN_CLOSE_TAG value:nil];
    [self expectToken:TOKEN_OPEN_TAG value:nil];
    [self expectToken:TOKEN_CLOSE_TAG value:nil];
    [self satisfyExpectations];
}

- (void) testFreeTextThenTag
{
    [self setUpWithInputString:@"Hello World{% %}"];
    [self expectToken:TOKEN_FREETEXT value:nil];
    [self expectToken:TOKEN_OPEN_TAG value:nil];
    [self expectToken:TOKEN_CLOSE_TAG value:nil];
    [self satisfyExpectations];
}

@end

//
//  Parser.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Parser.h"
#import "Node.h"
#import "FreeTextNode.h"
#import "VariableNode.h"
#import "TagNode.h"
#import "Tokenizer.h"
#import "Stack.h"

@implementation Parser

@synthesize tokenizer;

+(id)allocWithTokenizer:(Tokenizer *)tokenizer
{
	return [[Parser alloc] initWithTokenizer:tokenizer];
}

-(id)initWithTokenizer:(Tokenizer *)_tokenizer
{
	if (self = [super init])
	{
		tokenizer = [_tokenizer retain];
		currToken = [[Token alloc] init];
        peekedToken = nil;
		endNodeStack = [[Stack alloc] init];
	}
	return self;
}

-(void)dealloc
{
	[currToken release];
	[tokenizer release];
	[endNodeStack release];
	[super dealloc];
}

/**
 * Creates an error with a default code and error message.
 */
- (id) throwError:(NSError **)error message:(NSString *)message
{
    return [self throwErrorWithCode:error code:-1 message:message];
}

/**
 * Creates an error with a code and error message.
 */
- (id) throwErrorWithCode:(NSError **)error code:(int)code message:(NSString *)message
{
    [NSException raise:@"Exception in Parsing" format:@"Code: %d, Message: %@", code, message];
	return nil;
}

- (Token *)getTokenWithPeek:(BOOL)peekOnly error:(NSError **)error 
{
    // do we have a cached token?
    if (peekedToken != nil)
    {
        Token *out = peekedToken;
        if (!peekOnly)
        {
            // clear the peeked token so next time we do a clean extract
            peekedToken = nil;
        }
        return out;
    }

    BOOL result;
    do
    {
        result = [tokenizer nextToken:currToken];
    } while (result && currToken.tokenType == TOKEN_COMMENT);

    if (!result)    // EOF
        return nil;

    // check errors:
    if (currToken.tokenType == TOKEN_ERROR)
    {
        return [self throwError:error message:currToken.tokenValue];
    }

    // if we are peeking then save the peeked token
    if (peekOnly)
        peekedToken = currToken;

    return currToken;
}

/**
 * Gets a token and throws an error if it doesnt match an expected token.
 * @param tokenType    The token type which we are expecting.
 * @return The extracted token if it matches the expected type.
 */
- (Token *)expectToken:(TokenType)tokenType error:(NSError **)error
{
    return [self expectTokenWithPeek:tokenType peekOnly:NO error:error];
}

/**
 * Gets a token and throws an error if it doesnt match an expected token.
 * @param tokenType    The token type which we are expecting.
 * @param peekOnly    Tells whether to only peek the token instead of extracting it.
 * @return The extracted token if it matches the expected type.
 */
- (Token *) expectTokenWithPeek:(TokenType) tokenType peekOnly:(BOOL)peekOnly  error:(NSError **)error
{
    Token *token = [self getTokenWithPeek:peekOnly error:error];
    if (token == nil)
        [self throwError:error 
				 message:[NSString stringWithFormat:@"Expected %s, Found EOF instead", tokenType]];
    if (token.tokenType == TOKEN_ERROR)
		[self throwError:error message:token.tokenValue];
    if (token.tokenType != tokenType)
        [self throwError:error 
				 message:[NSString stringWithFormat:@"Expected %s, Found %s instead", tokenType, token.tokenType]];
    return token;
}


/**
 * Gets a token and throws an error if it doesnt match an expected token.
 * @param tokens    The list of tokens which we are ok with.
 * @return The extracted token if it matches the expected type.
 */
- (Token *) expectTokenInList:(TokenType [])tokens error:(NSError **)error
{
    return [self expectTokenInListWithPeek:tokens peekOnly:NO error:error];
}

/**
 * Gets a token and throws an error if it is not one of the expected token types.
 * @param tokens    The list of tokens which we are ok with.
 * @param peekOnly    Whether we are only peeking or extracting the token as well.
 * @return The extracted token if it matches the expected type.
 */
- (Token *) expectTokenInListWithPeek:(TokenType [])tokens
                             peekOnly:(BOOL)peekOnly
                                error:(NSError **)error
{
    Token *token = [self getTokenWithPeek:peekOnly error:error];
    if (token == nil)
        return [self throwError:error message:@"Unexpected EOF. "];
    
    if (token.tokenType == TOKEN_ERROR)
        return [self throwError:error message:token.tokenValue];
    
    for (int i = 0;i < tokens[i] != TOKEN_UNKNOWN;i++)
    {
        if (token.tokenType == tokens[i])
            return token;
    }
    
    NSMutableString *tokensString = [[NSMutableString alloc] initWithString:@""];
    for (int i = 0;i < tokens[i] != TOKEN_UNKNOWN;i++)
    {
        if (i != 0)
            [tokensString appendString:@", "];
        [tokensString appendFormat:@"'%d'", tokens[i]];
    }
    [self throwError:error 
			 message:[NSString stringWithFormat:@"Expected one of [%@], Found: %d instead.", tokensString, token.tokenType]];
    return nil;
}

/**
 * Peeks at the next token.
 * @return     The peeked token.
 */
- (Token *) peekToken:(NSError **)error
{
    return [self getTokenWithPeek:YES error:error];
}

/**
 * Gets the next token.
 * @return     The token extracted.
 */
- (Token *) getToken:(NSError **)error
{
    return [self getTokenWithPeek:NO error:error];
}

/**
 * Discards tokens till a particular token.
 * @param lastToken
 */
- (void) discardTokensTill:(TokenType)lastToken error:(NSError **)error
{
    Token *token = [self getToken:error];
    while (token.tokenType != lastToken)
        token = [self getToken:error];
}

/**
 * Parses the entire input and returns a parse tree.
 */
- (Node *)parse:(NSError **)error
{
    Node *firstNode = nil;
    Node *lastNode  = nil;
    Node *nextNode  = [self parseNode:error];
    while (nextNode != nil)
    {
        if (lastNode != nil)
        {
            lastNode.nextNode = nextNode;
            lastNode = nextNode;
        }
        else
        {
            firstNode = lastNode = nextNode;
        }
        nextNode  = [self parseNode:error];
    }
    return firstNode;
}

/**
 * Reads the next node whether it be a freetext node, a variable node 
 * or a tag node and returns it.  If no more nodes are left or an error 
 * was found, then a nil is returned.
 */
- (Node *)parseNode:(NSError **)error
{
    Token *token = [self getToken:error];
    if (token != nil)
    {
        if (token.tokenType == TOKEN_FREETEXT)
        {
            // easy
            return [[FreeTextNode alloc] initWithContent:token.tokenValue];
        }
        else if (token.tokenType == TOKEN_OPEN_VARIABLE)
        {
            return [[VariableNode alloc] initWithParser:self error:error];
        }
        else if (token.tokenType == TOKEN_OPEN_TAG)
        {
            // see if the tag is part of the end node stack
            if (!endNodeStack.isEmpty)
            {
                token = [self expectTokenWithPeek:TOKEN_IDENTIFIER peekOnly:YES error:error];
                if (token != nil)
                {
                    NSString **nameList = (NSString **)endNodeStack.top; 
                    for (int i = 0;nameList[i] != nil;i++)
                    {
                        if ([nameList[i] compare:token.tokenValue] == NSOrderedSame)
                        {
                            // we are at an end tag so pop the endtag list and return an endtag indicator
                            [endNodeStack pop];
                            return nil;
                        }
                    }
                }
            }
            // its a normal (non-end) tag so extract it as usual
            return [TagNode allocWithParser:self error:error];
        }
        [self throwError:error message:[NSString stringWithFormat:@"Invalid token found: %d", token.tokenType]];
    }
    return nil;
}

/**
 * This is called by a TagNode (or its derivative) to parse "upto" a certain 
 * tag node in the input stream.  For example in a "for loop" node, after reading
 * the initial {% for x in blah %}, the tag will want to read everything upto 
 * an "empty" or "endfor" node and store the resulting nodes as child nodes.
 * So for this the parser must be handed back control to read upto that point.
 * This function does that.
 * Also this itself can be recursive, so if there is a forloop inside a forloop,
 * then the first empty (or end) node that is encountered must be given to the 
 * second forloop and not the first one.
 * 
 * @param nodeList
 * @return
 */
- (Node *)parseTillNodeInList:(NSString [])nameList error:(NSError **)error
{
    [endNodeStack push:nameList];
    return [self parse:error];
}

@end

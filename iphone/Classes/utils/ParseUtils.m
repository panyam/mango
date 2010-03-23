//
//  ParseUtils.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ParseUtils.h"
#import "Tokenizer.h"
#import "Parser.h"
#import "Variable.h"
#import "TokenLists.h"
#import "Filter.h"
#import "FilterNode.h"
#import "FilterLibrary.h"

/**
 * Parse a variable expression.
 * @param parser
 * @return
 */
Variable *parseVariable(Parser * parser, NSError **error)
{
    Variable *firstVar = nil;
    Variable *lastVar = nil;
    Token *token = [parser expectToken:TOKEN_IDENTIFIER error:error];
    while (YES)
    {
        NSString *varValue = token.tokenValue;
        Variable *nextVar = [[Variable alloc] initWithValueQuotedAndNext:varValue 
														 isquoted:(token.tokenType == TOKEN_QUOTED_STRING) 
															 next:nil];
        if (firstVar == nil)
        {
            firstVar = lastVar = nextVar;
        }
        else
        {
            lastVar.nextVariable = nextVariable;
            lastVar = nextVar;
        }
        
        // peek at the next token...
        token = [parser peekToken:error];
        if (token != nil && token.tokenType == TOKEN_DOT)
        {
            [parser getToken:error];    // discard the DOT
            token = [parser expectTokenInList:IDENT_OR_STRING error:error];
        }
        else
        {
            break ;
        }
    }
    return firstVar;
}

/**
 * Parses a filter including the final }} which indicates the end of the variable node.
 * @param parser
 */
NSMutableArray *	parseFilterList(Parser *parser, NSError **error)
{
    NSMutableArray *output = nil;
    Token *token = [parser peekToken:error];
    while (token.tokenType == TOKEN_FILTER_SEPERATOR)
    {
        [parser getToken:error];    // Discard the '|'
        FilterNode *filterNode = parseFilterExpression(parser, error);
        if (output == nil)
            output = [[NSMutableArray alloc] init];
        [output addObject:filterNode];
		token = [parser peekToken:error];
    }
    return output;
}

/**
 * Parses each filter expression in the filter list.  This assumes that the next 
 * token being read will be an identifier indicating the name of the filter.
 * 
 * Filter expressions are of the form:
 * ident
 * ident COLON value
 * ident COLON OPEN_PAREN value_list CLOSE_PAREN
 * @param parser
 */
FilterNode *parseFilterExpression(Parser *parser, NSError **error)
{
    Token *token = [parser expectToken:TOKEN_IDENTIFIER error:error];
    NSString *filterName = token.tokenValue;
    Filter *filter = [[FilterLibrary sharedInstance] getObjectInstance:filterName];
    if (filter == nil)
        [parser throwError:error message:[NSString stringWithFormat:@"Filter not found: %@", filterName]];
    FilterNode *newFilter = [[FilterNode alloc] initWithFilter:filter];

    token = [parser peekToken:error];

    if (token != nil && token.tokenType == TOKEN_COLON)
    {
        // consume the token
        [parser getToken:error];
        parseFilterArguments(parser, newFilter, error);
    }
    return newFilter;
}

/**
 * Parses the arguments of a filter expression.  This assumes that next token
 * that will be read is either a "(@" or a variable.
 * @param parser
 */
BOOL parseFilterArguments(Parser *parser, FilterNode *filterNode, NSError **error)
{
    // now read the tokens
    Token *token = [parser expectTokenInList:IDENT_STRING_OR_OPEN_PAREN error:error];
    if (token.tokenType == TOKEN_OPEN_PAREN)
    {
        token = [parser expectTokenInList:IDENT_OR_STRING error:error];
        while (YES)
        {
            NSString *varValue = token.tokenValue;
            Variable *nextVar = [[Variable alloc] initWithValueQuoted:varValue 
															isquoted:(token.tokenType == TOKEN_QUOTED_STRING) 
																next:nil];
			[filterNode addArgument:nextVar];
            token = [parser expectTokenInList:COMA_OR_CLOSE_PAREN error:error];
            if (token.tokenType == TOKEN_CLOSE_PAREN)
                break ;
            else if (token.tokenType == TOKEN_COMA)
                token = [parser expectTokenInList:IDENT_OR_STRING error:error];
        }
    }
    else if (token.tokenType == TOKEN_IDENTIFIER || 
            token.tokenType == TOKEN_QUOTED_STRING)
    {
        NSString *varValue = token.tokenValue;
        Variable *nextVar = [[Variable alloc] initWithValueQuoted:varValue 
														 isquoted:(token.tokenType == TOKEN_QUOTED_STRING) 
															 next:nil];
        [filterNode addArgument:nextVar];
    }
    else
    {
        [parser throwError:error 
				   message:@"Internal Error.  This case should have been caught by expectTokensInList"];
		return NO;
    }
	return YES;
}


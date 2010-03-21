//
//  VariableNode.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 12/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "VariableNode.h"
#import "Variable.h"
#import "Tokenizer.h"
#import "Parser.h"
#import "ParseUtils.h"
#include "CompareUtils.h"

/**
 * A parse tree node that holds information to render a variable.
 */
@implementation VariableNode

@synthesize variable;

/**
 * Extracts a variable out of the parser.
 *
 * Variable Nodes have the following structure:
 *
 * VariableNode :=      OPEN_VARIABLE_NODE var_exp CLOSE_VARIABLE_NODE 
 *                  |   OPEN_VARIABLE_NODE var_exp filter_list CLOSE_VARIABLE_NODE 
 *                  ;
 *
 * var_exp  :=      ident
 *              |   ident ; var_exp
 *              ;
 *
 * filter_list  := filter_exp
 *              |   filter_exp filter_list
 *              ;
 *
 * filter_exp   := ident 
 *              |  ident COLON ident
 *              |  ident COLON OPEN_PAREN filter_arg_list CLOSE_PAREN
 *              ;
 *
 * filter_arg_list  :=  ident 
 *                  |   ident COMA filter_arg_list
 *                  ;
 */

- (id) initWithVariable:(Variable *)var next:(Node *)next
{
    return [self initWithVariableAndFilters:var filters:nil next:next];
}

- (id) initWithVariableAndFilters:(Variable *)var filters:(NSArray *)filters next:(Node *)next
{
    if (self = [super initWithNextNode:next])
    {
        variable = [var retain];
        filterNodes = nil;
    }
    return self;
}

- (id) initWithParser:(Parser *)parser error:(NSError **)error
{
    if (self = [super initWithNextNode:nil])
    {
        variable = nil;
        filterNodes = nil;
        [self parseVariableNode:parser error:error];
    }
    return self;
}

- (void) dealloc
{
    [variable release];
    [filterNodes removeAllObjects];
    [filterNodes release];
    [super dealloc];
}

/**
 * Adds a new filter node programmatically.
 * @param filterNode
 */
- (void) addFilterNode:(FilterNode *)filterNode;
{
    if (filterNodes == nil)
        filterNodes = [[NSArray alloc] init];
    [filterNodes addObject:filterNode];
}

/**
 * Tells if this object is equal to another.
 */
- (BOOL) isEqual:(NSObject *)another
{
    if (another == self)
        return YES;
    if (another == nil || ![another isKindOfClass:[VariableNode class]])
        return NO;
    VariableNode *anotherVarNode = (VariableNode *)another;
    if (![anotherVarNode.variable isEqual:variable])
        return NO;
    if (!compareArrays(filterNodes, anotherVarNode->filterNodes))
        return NO;
    return [self compareNextNodes:anotherVarNode];
}

/**
 * Reads the variable expression part of the node.
 * 
 * This is identifer ( DOT identifier ) *
 * 
 * @param parser
 */
- (void) parseVariableNode:(Parser *)parser error:(NSError **)error
{
    variable = parseVariable(parser, error);
    // read the next token - it should be a close or a filter starter
    Token *token = [parser peekToken:error];
    if (token.tokenType == TOKEN_FILTER_SEPERATOR)
    {
        filterNodes = parseFilterList(parser, error);
        token = [parser peekToken:error];
    }
    
    if (token == nil || token.tokenType != TOKEN_CLOSE_VARIABLE)
    {
        [parser throwError:error 
				   message:[NSString stringWithFormat:@"Expected '}}', but found '%@'", (token == nil ? @"EOF" : token)]];
    }
    else
    {
        // otherwise read and discard the '}}'
        [parser getToken:error];
    }
}

@end

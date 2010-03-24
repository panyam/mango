//
//  VariableNode.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Node.h"

@class Variable;
@class FilterNode;

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
 *              |   ident DOT var_exp
 *              ;
 *
 * filter_list  := filter_exp
 *              |   filter_exp FILTER_SEPERATOR filter_list
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
@interface VariableNode : Node
{
    Variable *      variable;
    NSMutableArray *filterNodes;
}

@property (nonatomic, retain) Variable *variable;

- (id) initWithVariable:(Variable *)var next:(Node *)next;
- (id) initWithVariableAndFilters:(Variable *)var filters:(NSArray *)filters next:(Node *)next;
- (id) initWithParser:(Parser *)parser error:(NSError **)error;
- (void) dealloc;

- (void) addFilterNode:(FilterNode *)filterNode;
- (BOOL) isEqual:(NSObject *)another;
- (void) parseVariableNode:(Parser *)parser error:(NSError **)error;

@end


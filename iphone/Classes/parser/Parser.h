//
//  Parser.h
//  DjangoParsers
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TokenTypes.h"
@class Node;
@class Tokenizer;
@class Token;
@class Stack;

/**
 * Our parser is simple.  It reads the tokens and creates a parse tree so
 * templates are not parsed multiple times and during render time the Tree
 * is ismply rendered.
 *
 * Our grammar is LL and in bnf is:
 * 
 * root := node *
 * node := FreeTextNode | VariableNode | TagNode
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
 *
 * TagNode := OPEN_TAG_NODE ident ( token * ) CLOSE_TAG_NODE
 *          ;
 */
@interface Parser : NSObject
{
    Tokenizer *tokenizer;
	Token *currToken;
    Token *peekedToken;
	Stack *endNodeStack;
}

@property    (nonatomic, retain)    Tokenizer *tokenizer;

+(id)allocWithTokenizer:(Tokenizer *)tokenizer;
-(id)initWithTokenizer:(Tokenizer *)_tokenizer;
-(void)dealloc;

- (id) throwErrorWithCode:(NSError **)error code:(int)code message:(NSString *)message;
- (id) throwError:(NSError **)error message:(NSString *)message;
- (Token *)peekToken:(NSError **)error;
- (Token *)getToken:(NSError **)error;
- (Token *)getTokenWithPeek:(BOOL)peekOnly error:(NSError **)error;

- (Token *) expectToken:(TokenType)tokenType error:(NSError **)error;
- (Token *) expectTokenWithPeek:(TokenType) tokenType peekOnly:(BOOL)peekOnly  error:(NSError **)error;
- (Token *) expectTokenInList:(TokenType [])tokens error:(NSError **)error;
- (Token *) expectTokenInListWithPeek:(TokenType [])tokens
                             peekOnly:(BOOL)peekOnly
                                error:(NSError **)error;
- (Token *) peekToken:(NSError **)error;
- (Token *) getToken:(NSError **)error;
- (void) discardTokensTill:(TokenType)lastToken error:(NSError **)error;

- (Node *)parse:(NSError **)error;
- (Node *)parseNode:(NSError **)error;
- (Node *)parseTillNodeInList:(NSString [])nameList error:(NSError **)error;

@end


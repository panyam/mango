//
//  ObjectLibrary.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef TOKEN_LISTS_H
#define TOKEN_LISTS_H

#import "TokenTypes.h"

/**
 * Expected token list for identifier or string only.
 */
extern TokenType COLON_OR_CLOSE_VARIABLE[3];

/**
 * Expected token list for identifier or string only.
 */
extern TokenType IDENT_OR_STRING[3];

/**
 * Tokens that can be expected when reading the variable name expression.
 */
extern TokenType IDENT_OR_OPEN_PAREN[3];

/**
 * Tokens that can be expected when reading the variable name expression.
 */
extern TokenType IDENT_STRING_OR_OPEN_PAREN[4];

/**
 * Tokens that can be expected when reading the variable name expression.
 */
extern TokenType COMA_OR_CLOSE_PAREN[3];

/**
 * Tokens that can be expected when reading the variable name expression.
 */
extern TokenType IDENT_TOKENS[4];

/**
 * Tokens that can be expected when reading filter lists.
 */
extern TokenType FILTER_LIST_TOKENS[3];

#endif


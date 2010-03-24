
#include "TokenLists.h"

/**
 * Expected token list for identifier or string only.
 */
TokenType COLON_OR_CLOSE_VARIABLE[3] = {
        TOKEN_COLON, 
        TOKEN_CLOSE_VARIABLE,
        TOKEN_UNKNOWN,
};

/**
 * Expected token list for identifier or string only.
 */
TokenType IDENT_OR_STRING[3] = {
        TOKEN_IDENTIFIER, 
        TOKEN_QUOTED_STRING,
		TOKEN_UNKNOWN,
};

/**
 * Tokens that can be expected when reading the variable name expression.
 */
TokenType IDENT_OR_OPEN_PAREN[3] = {
        TOKEN_IDENTIFIER, 
        TOKEN_OPEN_PAREN,
        TOKEN_UNKNOWN,
};

/**
 * Tokens that can be expected when reading the variable name expression.
 */
TokenType IDENT_STRING_OR_OPEN_PAREN[4] = {
        TOKEN_IDENTIFIER, 
        TOKEN_QUOTED_STRING,
        TOKEN_OPEN_PAREN,
        TOKEN_UNKNOWN,
};

/**
 * Tokens that can be expected when reading the variable name expression.
 */
TokenType COMA_OR_CLOSE_PAREN[3] = {
        TOKEN_COMA,
        TOKEN_CLOSE_PAREN,
        TOKEN_UNKNOWN,
};

/**
 * Tokens that can be expected when reading the variable name expression.
 */
TokenType IDENT_TOKENS[4] = {
        TOKEN_DOT, 
        TOKEN_CLOSE_VARIABLE,
        TOKEN_FILTER_SEPERATOR,
        TOKEN_UNKNOWN,
};

/**
 * Tokens that can be expected when reading filter lists.
 */
TokenType FILTER_LIST_TOKENS[3] = {
        TOKEN_CLOSE_VARIABLE,
        TOKEN_FILTER_SEPERATOR,
        TOKEN_UNKNOWN,
};


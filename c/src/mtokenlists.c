
#include "mtokenlists.h"

MangoTokenType IDENT_OR_STRING[3] = 
{
    TOKEN_QUOTED_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_UNKNOWN,
};

MangoTokenType IDENT_OR_OPEN_PAREN[3] = {
    TOKEN_IDENTIFIER,
    TOKEN_OPEN_PAREN,
    TOKEN_UNKNOWN,
};

MangoTokenType IDENT_STRING_OR_OPEN_PAREN[4] = {
    TOKEN_IDENTIFIER,
    TOKEN_QUOTED_STRING,
    TOKEN_OPEN_PAREN,
    TOKEN_UNKNOWN,
};

MangoTokenType COMA_OR_CLOSE_PAREN[3] = {
    TOKEN_COMA,
    TOKEN_CLOSE_PAREN,
    TOKEN_UNKNOWN,
};


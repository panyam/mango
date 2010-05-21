#ifndef __MANGO_TOKENIZER_H__
#define __MANGO_TOKENIZER_H__

#include "mfwddefs.h"
#include "mtoken.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE         4096
#define MAX_PUSHED_CHARS    64

/**
 * Tokenizers for a mango template.  Mango templates are very simple.
 * They do not hold much coding logic and only provide simple primitives on
 * templates.  Infact all logic is done by template tags that are either
 * provided by the library or custom tags written by the users of this
 * library.
 *
 * Here is the BNF of our templates.
 *
 * Template     := (String | Var | tag | Comment ) *
 * Var     := {{ <var_exp> }}
 * var_exp      := var |
 *                 var "|" filter_list
 *                 ;
 * var     := ID | ID "." var ;
 * filter_list  := filter |
 *                 filter "|" filter_list 
 *                 ;
 * filter       := ID | ID param_list   ;
 * ID           := [a-zA-Z_0-9]+ // (yes it can even start with a digit)
 * param_list   :=  ":" param   |
 *                  ":" param param_list
 *                  ;
 * param        := QuotedString | Number | Boolean | var ;
 *
 * Comment      := {# .* #}
 * Tag          := {% ID StringList %} {% endID %}
 * StringList   := String StringList |
 *                 String 
 *                 ;
 *
 * But for the purposes of the tokenizer we only look at the following
 * tokens:
 *
 * Filter Seperator             -   |
 * Filter Argument Seperator    -   :
 * Block Node Start              -   {%
 * Block Node End                -   %}
 * Comment Start                -   {#
 * Comment End                  -   #}
 * Var Node Start           -   {{
 * Var Node End             -   }}
 * String                       -   .+
 * QuotedString                 -   "[^"]*"
 */  
struct MangoTokenizer
{
    /**
     * current input source being read
     */
    MangoInputSource *  inputSource;

    /**
     * This is just an option to bound the size of tokens if there are
     * memory constraints.
     */
    int                 maxStringSize;

    /**
     * Array for maintaining characters that were "unget"ed.
     */
    int                 pushedChars[MAX_PUSHED_CHARS];
    int                 pushedCharsLen;

    /**
     * Current line and column information.
     */
    int                 currLine;
    int                 currColumn;

    /**
     * Tokenizer state vars.
     */
    int                 _insideNode;
    int                 _nodeEndChar;
    MangoTokenType      _nodeCloseToken;
    BOOL                _insideQuotes;
    BOOL                _insideIdentifier;
    int                 _quoteType;  // single or double
};

/**
 * Create a tokenizer from an input source.
 *
 * \param   input   Input source for the tokenizer.
 */
extern MangoTokenizer *mango_tokenizer_new(MangoInputSource *input);

/**
 * Destroy a tokenizer.
 *
 * \param   tokenizer   Tokenizer to destroy and free.
 */
extern void mango_tokenizer_free(MangoTokenizer *tokenizer);

/**
 * Resets the tokenizer with another source.
 *
 * \param   input   New input source to reset with.
 */
extern void mango_tokenizer_reset(MangoTokenizer *tokenizer, MangoInputSource *input);

/**
 * Get the next token.
 *
 * \param   tokenizer
 */
extern BOOL mango_tokenizer_next_token(MangoTokenizer *tokenizer, MangoToken *token, MangoError **error);

/**
 * Tells if there are any tokens left.
 *
 * \param   tokenizer
 */
extern BOOL mango_tokenizer_has_tokens(MangoTokenizer *tokenizer);

#ifdef __cplusplus
}
#endif

#endif

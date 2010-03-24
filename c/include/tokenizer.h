#ifndef MANGO_TOKENIZER_H
#define MANGO_TOKENIZER_H

/**
 * This Tokenizes a mango template.  Mango templates are very simple.
 * They do not hold much coding logic and only provide simple primitives on
 * templates.  Infact all logic is done by template tags that are either
 * provided by the library or custom tags written by the users of this
 * library.
 *
 * Here is the BNF of our templates.
 *
 * Template     := (String | Variable | tag | Comment ) *
 * Variable     := {{ <variable_expression> }}
 * var_exp      := variable |
 *                 variable "|" filter_list
 *                 ;
 * variable     := ID | ID "." variable ;
 * filter_list  := filter |
 *                 filter "|" filter_list 
 *                 ;
 * filter       := ID | ID param_list   ;
 * ID           := [a-zA-Z_0-9]+ // (yes it can even start with a digit)
 * param_list   :=  ":" param   |
 *                  ":" param param_list
 *                  ;
 * param        := QuotedString | Number | Boolean | variable ;
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
 * Variable Node Start           -   {{
 * Variable Node End             -   }}
 * String                       -   .+
 * QuotedString                 -   "[^"]*"
 */  
typedef struct Tokenizer_
{
	/**
     * current input stream being read
     */
	MangoInputStream *  inputStream;

    /**
     * This is just an option to bound the size of tokens if there are
     * memory constraints.
     */
    int                 maxStringSize;

    /**
     * Current input buffer read from the input stream
     */
    char                inputBuffer[BUFFER_SIZE];

    /**
     * Length of the buffer.
     */
    int                 bufferLen;

    /**
     * Position within the buffer.
     */
    int                 bufferPos;

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
     * Tokenizer state variables.
     */
    int                 _insideNode;
	int					_nodeEndChar;
	TokenType			_nodeCloseToken;
    BOOL                _insideQuotes;
    BOOL                _insideIdentifier;
    int                 _quoteType;  // single or double
} MangoTokenizer;

/**
 * Create a tokenizer from an input stream.
 *
 * \param   input   Input stream for the tokenizer.
 */
extern MangoTokenizer *mango_tokenizer_create(MangoInputStream *input);

/**
 * Destroy a tokenizer.
 *
 * \param   tokenizer   Tokenizer to destroy and free.
 */
extern void mango_tokenizer_destroy(MangoTokenizer *tokenizer);

/**
 * Resets the tokenizer with another stream.
 *
 * \param   input   New input stream to reset with.
 */
extern void mango_tokenizer_reset(MangoInputStream *input);

/**
 * Get the next token.
 *
 * \param   tokenizer
 */
extern void mango_tokenizer_next_token(MangoTokenizer *tokenizer);

/**
 * Tells if there are any tokens left.
 *
 * \param   tokenizer
 */
extern bool mango_tokenizer_has_tokens(MangoTokenizer *tokenizer);

#endif

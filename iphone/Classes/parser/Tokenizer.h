//
//  Tokenizer.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TokenTypes.h"

#define BUFFER_SIZE         16384
#define MAX_PUSHED_CHARS    64

@interface Token : NSObject
{
    TokenType           tokenType;
    NSMutableString *   tokenValue;
	int					tokenSize;
}

@property (nonatomic) TokenType tokenType;
@property (nonatomic, readonly) NSMutableString *tokenValue;
@property (nonatomic) int tokenSize;

+ (id) tokenWithTypeAndValue:(TokenType)type value:(NSString *)value;
- (id) initWithTypeAndValue:(TokenType)type value:(NSString *)value;
- (id) init;
- (void) dealloc;
- (void) appendCharacter:(unichar)character;
- (void) setTokenValue:(NSString *)value;

/*
+(id)eofToken;
+(id)errorToken:(NSString *)message;
*/

@end

/**
 * This Tokenizes a django template.  Django templates are very simple.
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
@interface Tokenizer : NSObject {
	// current input stream being read
	NSInputStream * inputStream;

    // For string tokens we return tokens that are of no more than this
    // size.  If this is -ve then we dont limit string token sizes.  This
    // only applies to strings outside Variable and Node tags.
    int                 maxStringSize;

    // Tells the tag which the tokenizer is currently reading if any.
    int                 insideNode;
	int					nodeEndChar;
	TokenType			nodeCloseToken;
    BOOL                insideQuotes;
    BOOL                insideIdentifier;
    int                 quoteType;  // single or double

    // Current input buffer read from the input stream
    char                inputBuffer[BUFFER_SIZE];
    int                 bufferLen;
    int                 bufferPos;
    int                 pushedChars[MAX_PUSHED_CHARS];
    int                 pushedCharsLen;
    int                 currLine;
    int                 currColumn;
    int                 lastLineWidth;
}

@property (nonatomic) int maxStringSize;

+(id)allocFromString:(NSString *)inputString;
+(id)allocFromFile:(NSString *)inputFile;
+(id)allocFromStream:(NSInputStream *)stream;
-(id)initWithStream:(NSInputStream *)stream;
-(void)setInputStream:(NSInputStream *)stream;
-(BOOL)nextToken:(Token *)token;
-(BOOL)hasTokensAvailable;
-(int) nextChar;
-(void) ungetChar:(int)character;

@end

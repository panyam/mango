//
//  Tokenizer.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Tokenizer.h"
#import <stdio.h>

/////////////////////////////	Token Interface

@implementation Token

@synthesize tokenType;
@synthesize tokenValue;
@synthesize tokenSize;

+ (id) tokenWithTypeAndValue:(TokenType)type value:(NSString *)value
{
	return [[Token alloc] initWithTypeAndValue:type value:value];
}

- (id) initWithTypeAndValue:(TokenType)type value:(NSString *)value
{
	if (self = [super init])
	{
		if (value == nil)
			value = @"";
		tokenType = type;
		tokenValue = [value mutableCopy];
		tokenSize = 0;
	}
	return self;
}

- (id) init
{
	return [self initWithTypeAndValue:TOKEN_UNKNOWN value:nil];
}

- (void) appendCharacter:(unichar) character
{
    // NSAssert(token.tokenValue != nil, @"Token value cannot be nil");
    // there HAS to be a better way than this!
    [tokenValue appendString:[NSString stringWithCharacters:&character length:1]];
	tokenSize++;
}	

- (void) setTokenValue:(NSString *)value
{
    if (tokenValue == nil)
    {
        tokenValue = [[NSMutableString alloc] initWithString:value];
    }
	else
	{
		[tokenValue setString:value];
	}
	if (value == nil)
	{
		tokenSize = [value length];
	}
	else 
	{
		tokenSize = 0;
	}
}

- (void) dealloc
{
	[tokenValue release];
	[super dealloc];
}

@end

/////////////////////////////	Tokenizer Interface

@implementation Tokenizer

@synthesize maxStringSize;

#define BRACE   '{'

enum
{
    NODETYPE_NONE,
    NODETYPE_COMMENT,
    NODETYPE_VARIABLE,
    NODETYPE_TAG
};


+(id)allocFromString:(NSString *)inputString
{
	NSData *data = [inputString dataUsingEncoding:NSASCIIStringEncoding];
    return [[Tokenizer alloc] initWithStream: [NSInputStream inputStreamWithData:data]];
}

+(id)allocFromFile:(NSString *)filePath
{
    return [[Tokenizer alloc] initWithStream:[[NSInputStream alloc] initWithFileAtPath:filePath]];
}

+(id)allocFromStream:(NSInputStream *)stream
{
	return [[Tokenizer alloc] initWithStream:stream];
}

-(id)initWithStream:(NSInputStream *)stream
{
    if (self = [super init])
    {
		[self setInputStream:stream];
    }
    return self;
}

/**
 * Resets the tokenizer to start tokenizing from an input stream.
 */
-(void)setInputStream:(NSInputStream *)stream
{
	inputStream				= stream;
	[inputStream open];
	maxStringSize           = -1;
	insideNode              = NODETYPE_NONE;
	insideQuotes            = NO;
	insideIdentifier        = NO;
	bufferPos               = 0;
	bufferLen               = 0;
	pushedCharsLen          = 0;
	currLine                = 0;
	currColumn              = 0;
	lastLineWidth           = 0;
}

-(BOOL)hasTokensAvailable
{
	return bufferPos < bufferLen || pushedCharsLen > 0 || [ inputStream hasBytesAvailable ];
	/*int character = self.nextChar;
	if (character >= 0)
	{
		[self ungetChar:character];
		return YES;
	}
	return NO;
	 */
}

/**
 * Gets the next character in the stream.
 * -ve if nothing exists.
 */
-(int) nextChar
{
    // is there a char we ungetted?
    int outChar = -1;
    if (pushedCharsLen > 0)
    {
        outChar = pushedChars[--pushedCharsLen];
    }
    else
    {
        if (bufferPos >= bufferLen)
        {
            // refill the buffer
            if ([inputStream hasBytesAvailable])
            {
                bufferPos   = 0;
                bufferLen   = [inputStream read:(uint8_t*)inputBuffer maxLength:BUFFER_SIZE];
                if (bufferLen < 0)
                    return -1;
            }
            else
            {
                return -1;
            }
        }
        outChar = inputBuffer[bufferPos++];
    }
    if (outChar == '\n')
    {
        currLine++;
        currColumn = 0;
    }
    currColumn++;
    return outChar;
}

/**
 * Ungets a character so the next read will return this.
 */
-(void)ungetChar:(int)character
{
    NSAssert(pushedCharsLen < MAX_PUSHED_CHARS, @"Unget character stack is full");
    pushedChars[pushedCharsLen++] = character;
}

/**
 * Gets the next token.
 * The token is set into the token parameter.
 *
 * Returns true if a token was found, false if EOF or ERROR (which will be
 * the token type as well).
 *
 * The reason we are doing this instead of creating new tokens is each
 * token creation must be followed by a destruction and this seems very
 * wasteful from a memory management standpoint as we only need one token
 * look ahead at a time.  So might as well have a single token object and
 * reuse it till the entire tokenizing (and parsing) is complete rather
 * than creating and destroying a gazzilion tokens.  Same goes with using a
 * mutable string as the token value instead of creating and destroying
 * strings.
 */
-(BOOL)nextToken:(Token *)token
{
    token.tokenType = TOKEN_UNKNOWN;
    // the buffer only gets created once in the entire parser run
	[token setTokenValue:@""];

    int char1 = self.nextChar;
    while (char1 >= 0)
    {
        if (insideNode == NODETYPE_NONE)
        {
            // we are doing free text
            if (char1 == BRACE)
            {
                // starting a node, variable or comment
                int char2 = self.nextChar;
				nodeEndChar = char2;
                if (char2 == '#')
                {
                    insideNode = NODETYPE_COMMENT;
                    token.tokenType = TOKEN_COMMENT;
                }
                else if (char2 == BRACE)
                {
					nodeEndChar = '}';
                    insideNode = NODETYPE_VARIABLE;
					nodeCloseToken = TOKEN_CLOSE_VARIABLE;
                    token.tokenType = TOKEN_OPEN_VARIABLE;
                }
                else if (char2 == '%')
                {
                    insideNode = NODETYPE_TAG;
					nodeCloseToken = TOKEN_CLOSE_TAG;
                    token.tokenType = TOKEN_OPEN_TAG;
                }

                // we have reached a node and freetext is not empty
                // then return it
                if (insideNode != NODETYPE_NONE)
                {
                    if (token.tokenSize > 0)
                    {
                        // push the two characters back 
                        // so they can be read again
                        [self ungetChar:char2];
                        [self ungetChar:char1];
                        insideNode = NODETYPE_NONE;
                        token.tokenType = TOKEN_FREETEXT;
                        return YES;
                    }
                    else if (insideNode != NODETYPE_COMMENT)
                    {
                        // return the node start token
                        return YES;
                    }
                }
                else 
                {
                    // nothing so append to buffer and continue
                    [token appendCharacter:char1];
					if (char2 >= 0)
						[token appendCharacter:char2];
                }
            }
            else
            {
                // append to freetext buffer
                [token appendCharacter:char1];
            }
        }
        else if (insideNode == NODETYPE_COMMENT)
        {
            // skip everything until the end of comment
			if (char1 == '#')
			{
				int char2 = self.nextChar;
				if (char2 == '}')
				{
					token.tokenType = TOKEN_COMMENT;
					insideNode = NODETYPE_NONE;
					return YES;
				}
			}
        }
        else 
        {
            // we are inside a node, now quoted strings, dots and all are
            // significant
            if (insideQuotes)
            {
                if (char1 == quoteType)
                {
                    // finished quotes
                    insideQuotes = NO;
                    return YES;
                }
                else
                {
                    if (char1 == '\\')
                    {
                        char1 = self.nextChar;
                        if (char1 == '\n')
                        {
                            [token appendCharacter:'\n'];
                        }
                        else if (char1 == '\r')
                        {
                            [token appendCharacter:'\r'];
                        }
                        else if (char1 == '\t')
                        {
                            [token appendCharacter:'\t'];
                        }
                        else if (char1 == '\'')
                        {
                            [token appendCharacter:'\''];
                        }
                        else if (char1 == '"')
                        {
                            [token appendCharacter:'"'];
                        }
                        else if (char1 == 'f')
                        {
                            [token appendCharacter:'\f'];
                        }
                        else if (char1 == 'u')
                        {
                            NSAssert(NO, @"Cannot yet do unicode");
                        }
                        else if (char1 == 'u')
                        {
                            NSAssert(NO, @"Cannot yet do unicode");
                        }
                        else if (char1 < 0)
                        {
                            token.tokenType = TOKEN_ERROR;
                            return NO;
                        }
                        else
                        {
                            [token appendCharacter:'\\'];
                            [token appendCharacter:char1];
                        }
                    }
                    else
                    {
                        [token appendCharacter:char1];
                    }
                }
            }
            else if (insideIdentifier)
            {
                if (isalnum(char1))
                {
                    [token appendCharacter:char1];
                }
                else
                {
                    // finished identifier
                    token.tokenType = TOKEN_IDENTIFIER;
					insideIdentifier = NO;
                    [self ungetChar:char1];
                    return YES;
                }
            }
            else if (char1 == '"' || char1 == '\'')
            {
                // inside quotes everything else is secondary
                quoteType           = char1;
                insideQuotes        = YES;
                token.tokenType    = TOKEN_QUOTED_STRING;
            }
            else if (isalnum(char1))
            {
				[self ungetChar:char1];
                insideIdentifier    = YES;
                token.tokenType    = TOKEN_IDENTIFIER;
            }
            else if (isspace(char1))
            {
                // do nothing - skip spaces
            }
            else if (char1 == '.')
            {
                token.tokenType = TOKEN_DOT;
                return YES;
            }
            else if (char1 == '|')
            {
                token.tokenType = TOKEN_FILTER_SEPERATOR;
                return YES;
            }
            else if (char1 == ',')
            {
                token.tokenType = TOKEN_COMA;
                return YES;
            }
            else if (char1 == '|')
            {
                token.tokenType = TOKEN_FILTER_SEPERATOR;
                return YES;
            }
            else if (char1 == ':')
            {
                token.tokenType = TOKEN_COLON;
                return YES;
            }
            else if (char1 == '(')
            {
                token.tokenType = TOKEN_OPEN_PAREN;
                return YES;
            }
            else if (char1 == ')')
            {
                token.tokenType = TOKEN_CLOSE_PAREN;
                return YES;
            }
			else if (char1 == nodeEndChar)
			{
				// coming out of a node
				int char2 = self.nextChar;
				if (char2 == '}')
				{
					token.tokenType = nodeCloseToken;
					insideNode = NODETYPE_NONE;
					return YES;
				}
				else
				{
					[self ungetChar:char2];
				}
			}
			else
			{
				NSAssert(NO, ([NSString stringWithFormat:@"Invalid character: '%c/%d'", char1, char1]));
			}
        }
		char1 = self.nextChar;
    }

    token.tokenType = TOKEN_EOF;
	if (insideNode == NODETYPE_NONE)
	{
		if (token.tokenSize > 0)
		{
			token.tokenType = TOKEN_FREETEXT;
			return YES;
		}
	}
	else
	{
		// return unterminated node
		token.tokenType = TOKEN_ERROR;
	    [token setTokenValue:@"Reached EOF without terminating node."];
		return YES;
	}
    return NO;
}

@end

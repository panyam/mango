//
//  Template.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Node;
@class Tokenizer;

/**
 * Our parser is simple.  It reads the tokens and creates a parse tree so
 * templates are not parsed multiple times and during render time the Tree
 * is ismply rendered.
 */
@interface Template : NSObject
{
	Tokenizer *tokenizer;
}

@property	(nonatomic, retain)	Tokenizer *tokenizer;

+(id)allocWithTokenizer:(Tokenizer *)tokenizer;
+(id)allocFromString:(NSString *)inputString;
+(id)allocFromFile:(NSString *)inputFile;
+(id)allocFromStream:(NSInputStream *)stream;

-(id)initWithTokenizer:(Tokenizer *)_tokenizer;
-(void)dealloc;

@end


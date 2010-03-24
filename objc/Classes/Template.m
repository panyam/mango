//
//  Template.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Template.h"
#import "Node.h"
#import "Tokenizer.h"

@implementation Template

@synthesize tokenizer;

+(id)allocFromString:(NSString *)inputString
{
	return [[Template alloc] initWithTokenizer:[Tokenizer allocFromString:inputString]];
}

+(id)allocFromFile:(NSString *)inputFile
{
	return [[Template alloc] initWithTokenizer:[Tokenizer allocFromFile:inputFile]];
}

+(id)allocFromStream:(NSInputStream *)stream
{
	return [[Template alloc] initWithTokenizer:[Tokenizer allocFromStream:stream]];
}

+(id)allocWithTokenizer:(Tokenizer *)tokenizer
{
	return [[Template alloc] initWithTokenizer:tokenizer];
}

-(id)initWithTokenizer:(Tokenizer *)_tokenizer
{
	if (self = [super init])
	{
		tokenizer = _tokenizer;
	}
	return self;
}

-(void)dealloc
{
	[tokenizer dealloc];
	[super dealloc];
}

@end

//
//  FreeTextNode.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 12/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "FreeTextNode.h"

@implementation FreeTextNode

@synthesize content;

-(id)initWithContent:(NSString *)value
{
	if (self = [super init])
	{
		content = [value copy];
	}
	return self;
}

-(void)dealloc
{
	[content release];
	[super dealloc];
}

-(NSString *)render:(TemplateContext *)context
{
	return content;
}

-(BOOL)isEqual:(NSObject *)another
{
    if (another == self)
        return YES;
    if (another == nil || ![another isKindOfClass:[self class]])
        return NO;
    FreeTextNode *ftNode = (FreeTextNode *)another;
    if ([content compare:ftNode.content] != NSOrderedSame)
        return NO;
    return [self compareNextNodes:ftNode];
}

@end


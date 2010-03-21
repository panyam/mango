//
//  Pair.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#include "Pair.h"

@implementation Pair

@synthesize first;
@synthesize second;

- (id) initWithValues:(id)f second:(id)s
{
    if (self = [super init])
    {
        self.first = [f retain];
        self.second = [s retain];
    }
    return self;
}

-(void) dealloc
{
    [first release];
    [second release];
	[super dealloc];
}

@end

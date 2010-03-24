//
//  ObjectLibrary.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import "ObjectLibrary.h"
#import "Pair.h"

@implementation ObjectLibrary

- (id)init
{
    if (self = [super init])
    {
        objClasses = [[NSMutableDictionary alloc] init];
    }
	return self;
}

- (void) dealloc
{
    [objClasses release];
	[super dealloc];
}

- (void) registerObjectClass:(NSString *)name objClass:(Class)objClass
{
    Pair *classObjectPair = [[Pair alloc] initWithValues:objClass second:nil];
    [objClasses setObject:classObjectPair forKey:name];
    [classObjectPair release];
}

- (Class) getObjectClass:(NSString *)name
{
    Pair *classObjectPair = [objClasses objectForKey:name];
    return classObjectPair.first;
}

- (id)getObjectInstance:(NSString *)name
{
    Pair *classObjectPair = [objClasses objectForKey:name];
    if (classObjectPair.second == nil)
    {
        classObjectPair.second = [[classObjectPair.first alloc] init];
    }
    return classObjectPair.second;
}

@end

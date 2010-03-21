//
//  FilterNode.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import "FilterNode.h"
#import "Filter.h"
#import "Variable.h"
#import "CompareUtils.h"

@implementation FilterNode

@synthesize filter;
// @synthesize arguments;

- (id)initWithFilter:(Filter *)f
{
    if (self = [super init])
    {
        filter = [f retain];
        arguments = nil;
    }
	return self;
}

- (void) dealloc
{
    [filter release];
    filter = nil;

    [arguments removeAllObjects];
    [arguments release];
    arguments = nil;

	[super dealloc];
}

/**
 * Adds a variable to the argument list.
 */
- (void) addArgument:(Variable *)v
{
    if (arguments == nil)
        arguments = [[NSMutableArray alloc] init];
    [arguments addObject:v];
}
    
/**
 * Compares two filter nodes.
 */
- (BOOL) isEqual:(NSObject *)another
{
    if (another == self)
        return YES;
    if (another == nil || ![another isKindOfClass:[FilterNode class]])
        return NO;
    FilterNode *anotherFilter = (FilterNode *)another;
    if (filter != anotherFilter.filter)
    {
        return NO;
    }
    return compareArrays(arguments, anotherFilter->arguments);
}
@end

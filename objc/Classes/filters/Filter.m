//
//  Filter.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 2/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Filter.h"


@implementation Filter

@synthesize arguments;

/**
 * INitialises the filter with a name
 */
- (id) init
{
	if (self = [super init])
	{
		arguments = nil;
	}
	return self;
}

/**
 * Returns the name of the filter.
 * To be overridden by child classes.
 */
- (NSString *)filterName
{
    return @"";
}

/**
 * Applies the filter on a string and returns the transformed value.
 */
- (NSString *)render:(NSString *)value
{
	// by default we do nothing and return the original string
	return value;
}

/**
 * Cleans up the filter
 */
- (void) dealloc
{
	[arguments removeAllObjects];
	[super dealloc];
}

/**
 * Creates a filter instance specific context.
 * @return A filter specific context object.
 */
- (id)makeInstanceContext:(NSArray *)arguments
{
    return nil;
}

/**
 * Creates an invocation specific context for the filter.
 * @return An invocation specific context object for this filter.
 */
- (id)makeInvocationContext:(NSArray *) arguments
{
    return nil;
}

/**
 * Transforms the string and returns the rendered value.
 * The value is modified using the arguments and an optional filterContext.
 * The filterContext holds "softened" version of the arguments that it can use
 * on multiple invocations for the sake of efficiency.  For instance in an "add"
 * filter that would increment the value of an input string by some amount, 
 * it makes sense to cache the value as an integer instead of converting the
 * stringified argument on each render call!
 * @throws IOException 
 */
- (BOOL) render:(NSOutputStream *)output
           input:(NSString *)input
           arguments:(NSArray *)arguments
           filterContext:(NSObject *)filterContext
           error:(NSError  **)error
{
    return YES;
}

@end

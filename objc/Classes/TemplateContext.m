//
//  TemplateContext.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import "TemplateContext.h"

/**
 * Context objects contain values for variables that get substituted in a template.
 */
@implementation TemplateContext

/**
 * Gets the object by a key.
 * This can return a nil if the context is a sequential or an iterative container.
 */
- (id) getValue:(NSString *)key
{
    return nil;
}

/**
 * Gets the object by a key.
 * This can return a nil if the context is a sequential or an iterative container.
 */
- (void) setValue:(NSString *)key value:(id)value
{
}

/**
 * Pushes the value of a key to indicate entering of a new context.
 * Returns the new depth of the stack.
 */
- (int) pushValue:(NSString *)key value:(id)value
{
    return 0;
}

/**
 * Pushes the value of a key to indicate entering of a new context.
 * Returns the old value.
 */
- (id) popValue:(NSString *)key
{
    return nil;
}

/**
 * Deletes a value completely.
 */
- (id) deleteValue:(NSString *)key
{
    return nil;
}

/**
 * Tells if a value exists in the context.
 */
- (BOOL) hasValue:(NSString *)key
{
    return NO;
}

@end

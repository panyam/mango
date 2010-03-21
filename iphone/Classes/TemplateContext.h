//
//  TemplateContext.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 11/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Context objects contain values for variables that get substituted in a template.
 */
@interface TemplateContext : NSObject

/**
 * Gets the object by a key.
 * This can return a nil if the context is a sequential or an iterative container.
 */
- (id) getValue:(NSString *)key;

/**
 * Gets the object by a key.
 * This can return a nil if the context is a sequential or an iterative container.
 */
- (void) setValue:(NSString *)key value:(id)value;

/**
 * Pushes the value of a key to indicate entering of a new context.
 * Returns the new depth of the stack.
 */
- (NSInteger) pushValue:(NSString *)key value:(id)value;

/**
 * Pushes the value of a key to indicate entering of a new context.
 * Returns the old value.
 */
- (id) popValue:(NSString *)key;

/**
 * Deletes a value completely.
 */
- (id) deleteValue:(NSString *)key;

/**
 * Tells if a value exists in the context.
 */
- (BOOL) hasValue:(NSString *)key;

@end


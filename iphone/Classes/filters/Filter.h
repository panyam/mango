//
//  Filter.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * A filter takes a value and transforms it into "something else".
 * Filters are used in variable nodes as:
 *
 * {{ some_var_expression |filter1:(args)|filter2:(args) ... }}
 *
 * Django templates allow only a single argument per filter.  
 * We extend this to provide multiple arguments.  Also it is upto
 * The Filter object to do type conversions for the argument.  The
 * arguments will be passed in as strings.
 */
@interface Filter : NSObject {
	NSMutableArray *arguments;
}

@property (nonatomic, readonly) NSArray *arguments;

- (id) init;
- (NSString *)filterName;
- (NSString *)render:(NSString *)value;
- (void) dealloc;
    
/**
 * Creates a filter instance specific context.
 * @return A filter specific context object.
 */
- (id)makeInstanceContext:(NSArray *)arguments;

/**
 * Creates an invocation specific context for the filter.
 * @return An invocation specific context object for this filter.
 */
- (id)makeInvocationContext:(NSArray *) arguments;

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
           error:(NSError  **)error;

@end

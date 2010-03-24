//
//  FilterNode.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>

@class Filter;
@class Variable;

/**
 * A filter node is a node in the parse tree indicating a call to a filter evaluation.
 * 
 * @author Sri Panyam.
 */
@interface FilterNode : NSObject
{
    /**
     * The filter that will be applied when called.
     */
    Filter *        filter;
    NSMutableArray *arguments;
} 

@property (nonatomic, retain) Filter *filter;
// @property (nonatomic, retain) NSMutableArray *arguments;

- (id)initWithFilter:(Filter *)f;
- (void) addArgument:(Variable *)v;
- (void) dealloc;

@end

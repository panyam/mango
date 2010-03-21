//
//  Node.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Node.h"
#import "Tokenizer.h"
#import "Variable.h"

@implementation Node

@synthesize nextNode;

- (id)init
{
    return [self initWithNextNode:nil];
}

/**
 * INItialises with a next node as well.
 */
- (id)initWithNextNode:(Node *)next
{
    if (self = [super init])
    {
        nextNode = [next retain];
    }
    return self;
}

- (void) dealloc
{
    [nextNode release];
    [super dealloc];
}

/**
 * Returns the name of the node.
 */
- (NSString *) nodeName
{
    return @"";
}

/**
 * Compares next node of this instance with the next node of another instance
 * to see if they are equal.
 * @param another
 * @return
 */
- (BOOL) compareNextNodes:(Node *)another
{
    if (nextNode == another.nextNode)
        return YES;
    else if (nextNode == nil)
        return NO;
    else return [nextNode isEqual:another.nextNode];
}

@end

//
//  Stack.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Stack.h"

@interface StackNode : NSObject
{
	id value;
	StackNode *next;
}

@property (nonatomic, retain) id value;
@property (nonatomic, retain) StackNode *next;

- (id) initWithValue:(id)value;

@end

@implementation StackNode

@synthesize value;
@synthesize next;

- (id) initWithValue:(id)val
{
	if (self = [super init])
	{
		value = [val retain];
		next = nil;
	}
	return self;
}

- (void) dealloc
{
	[value release];
	[super dealloc];
}

@end

@implementation Stack

@synthesize count;

- (id) top
{
	return head == nil ? nil : head.value;
}

- (BOOL) isEmpty
{
	return count == 0;
}

- (id) init
{
	if (self == [super init])
	{
		head = nil;
		count = 0;
	}
	return self;
}

- (void) dealloc
{
	head = nil;
	[super dealloc];
}

- (id) pop
{
	id out = head;
	if (head != nil)
	{
		head = head.next;
		count--;
		return out;
	}
	return out;
}

- (void) push:(id)value
{
	StackNode *newNode = [[StackNode alloc] initWithValue:value];
	newNode.next = head;
	head = newNode;
}

@end

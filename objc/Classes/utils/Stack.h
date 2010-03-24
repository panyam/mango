//
//  Stack.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class StackNode;

@interface Stack : NSObject {
	StackNode *head;
	int count;
}

@property (nonatomic, readonly) int count;
@property (nonatomic, readonly) id top;
@property (nonatomic, readonly) BOOL isEmpty;

- (id) init;
- (void) dealloc;
- (id) pop;
- (void) push:(id)value;

@end

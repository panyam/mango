//
//  ForTagNode.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TagNode.h"

@class Variable;
@class Node;

/**
 * A tag for doing for loops.
 * Loops would be as:
 *
 * {% for (item1, item2, item3...itemn) in sourceVariable %}
 * {% empty %}
 * {% endfor %}
 */
@interface ForTagNode : TagNode
{
    NSMutableArray *items;
    Variable *      sourceVariable;
    Node *          emptyNode;
}

@property (nonatomic, retain) NSMutableArray *items;
@property (nonatomic, retain) Variable *sourceVariable;
@property (nonatomic, retain) Node *emptyNode;

- (id) initWithVariable:(Variable *)source;
- (id) initWithVariableAndNext:(Variable *)source next:(Node *)next;
- (id) initWithVariableNextAndChild:(Variable *)source next:(Node *)next child:(Node *)child;
- (id) initFromParser:(Parser *)parser error:(NSError **)error;
- (void) addItem:(Variable *)var;
- (BOOL) equalsTagNode:(TagNode *)another;

@end


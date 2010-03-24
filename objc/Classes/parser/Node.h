//
//  Parser.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Parser;
@class Tokenizer;
@class TemplateContext;

/**
 * A parse tree node is responsible for rendering a bit of templated content.
 *
 * basically at the tokenizer level we know what the name of a node is.
 * But any parsing must be done by particular node factories or node
 * parsers.  So for a variable node, we use VariableNode parsers and for
 * other nodes we provide the ability to extend and inherit the node parser
 * classes to do the work.
 *
 * To answer how a node name gets associated with a node at run time, the
 * answer is that objective C allows you to use classes as first class
 * objects.  So a particular node's object is good enough for us!
 *
 * Another alternative is to simply have a NodeLibrary class where all
 * methods with a particular prefix (eg node or node_) will be treated as
 * Node parsers or creators.
 */
@interface Node : NSObject
{
    // The next node in the chain.
    Node *nextNode;
}

@property (nonatomic, retain) Node *nextNode;

- (id)init;
- (id)initWithNextNode:(Node *)next;
- (NSString *) nodeName;
- (BOOL) compareNextNodes:(Node *)another;

@end


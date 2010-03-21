//
//  TagNode.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 12/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Node.h"

/**
 * Tag nodes enable hierarchy in the nodes and do a lot more than variable nodes.
 */
@interface TagNode : Node
{
    Node *  childNode;
}

@property (nonatomic, retain) Node *childNode;

+ (id)allocWithParser:(Parser *)parser error:(NSError **)error;
- (id) initWithNextNodeAndChild:(Node *)next child:(Node *)child;
- (BOOL)equalsTagNode:(TagNode *)another;
- (void) dealloc;

@end

//
//  TagNode.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 12/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "TagNode.h"
#import "Parser.h"
#import "Tokenizer.h"
#import "TagLibrary.h"

@interface TagNode()
- (id)initWithParser:(Parser *)parser error:(NSError **)error;
@end

@implementation TagNode

@synthesize childNode;

/**
 * Parses a tag node.  This is a slightly tricky bit...
 *
 * With tag nodes we will have to transfer control to the tag parsers so
 * that they can read the contents of the the node as they wish and this
 * can include whether or not to parse until the corresponding end tag.
 */
+ (id)allocWithParser:(Parser *)parser error:(NSError **)error
{
    Token *token = [parser getToken:error];
    if (token == nil || token.tokenType != TOKEN_IDENTIFIER)
    {
        [parser throwError:error message:@"Expected identifier token but received EOF instead"];
        return nil;
    }
	
    Class nodeClass = [[TagLibrary sharedInstance] getObjectClass:token.tokenValue];
    if (nodeClass == nil)
    {
        [parser throwError:error 
				  message:[NSString stringWithFormat:@"Invalid node type: %@", token.tokenValue]];
        return nil;
    }
    TagNode *node = [[nodeClass alloc] initWithParser:parser error:error];
    return node;
}

/**
 * Only having this constructor so that the [nodeClass alloc] line above doesnt give a warning.
 */
- (id)initWithParser:(Parser *)parser error:(NSError **)error
{
	return [self initWithNextNodeAndChild:nil child:nil];
}

- (id)initWithNextNode:(Node *)next
{
	return [self initWithNextNodeAndChild:next child:nil];
}

- (id)initWithNextNodeAndChild:(Node *)next child:(Node *)child
{
	if (self = [super initWithNextNode:next])
	{
        childNode = child;
	}
	return self;
}

- (void) dealloc
{
	[super dealloc];
}

/**
 * Compares two tag nodes.
 */
- (BOOL)equalsTagNode:(TagNode *)another
{
    return NO;
}

/**
 * Compares another object with this tag node.
 */
- (BOOL)isEqual:(NSObject*)another
{
    if (another == nil)
        return NO;
    if (another == self)
        return YES;
    
    // let child classes extend and fill this in
    if ([another isKindOfClass:[TagNode class]])
    {
        return [self equalsTagNode:((TagNode *)another)];
    }
    return NO;
}

/**
 * Compares child node of this instance with the child node of another instance
 * to see if they are equal.
 * @param another
 * @return
 */
- (BOOL) compareChildNodes:(TagNode *)another
{
    if (childNode == another.childNode)
        return YES;
    else if (childNode == nil)
        return NO;
    else return [childNode isEqual:another.childNode];
}

@end

//
//  FreeTextNode.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 12/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Node.h"

/**
 * Node that renders free non-templated text.
 */
@interface FreeTextNode : Node
{
	NSString *content;
}

@property (nonatomic, readonly) NSString *content;

-(id)initWithContent:(NSString *)value;
-(void)dealloc;
-(NSString *)render:(TemplateContext *)context;
-(BOOL)isEqual:(NSObject *)another;

@end

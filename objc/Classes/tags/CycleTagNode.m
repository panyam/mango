//
//  CycleTagNode.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "CycleTagNode.h"

@implementation CycleTagNode

- (BOOL) equalsTagNode:(TagNode *)another
{
    if (![another isKindOfClass:[CycleTagNode class]])
        return NO;

    return YES;
}

@end



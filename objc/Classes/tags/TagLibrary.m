//
//  TagLibrary.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import "TagLibrary.h"

@implementation TagLibrary

+ (id) sharedInstance
{
    static TagLibrary *instance = nil;
	if (instance == nil)
	{
		instance = [[TagLibrary alloc] init];
	}
    return instance;
}

@end

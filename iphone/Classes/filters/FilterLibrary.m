//
//  FilterLibrary.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import "FilterLibrary.h"

@implementation FilterLibrary

+ (id) sharedInstance
{
    static FilterLibrary *instance = nil ; 
	if (instance == nil)
	{
		instance = [[FilterLibrary alloc] init];
	}
    return instance;
}

@end

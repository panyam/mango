//
//  FilterLibrary.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>

#import "ObjectLibrary.h"


/**
 * A generic library object which keeps track of registered classes by
 * their names and an instance of the class on demand.
 */
@interface FilterLibrary : ObjectLibrary
{
}

+ (id) sharedInstance;

@end

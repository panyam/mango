//
//  ObjectLibrary.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>

/**
 * A generic library object which keeps track of registered classes by
 * their names and an instance of the class on demand.
 */
@interface ObjectLibrary : NSObject
{
    NSMutableDictionary *objClasses;
}

- (id) init;
- (void) dealloc;
- (void) registerObjectClass:(NSString *)name objClass:(Class)objClass;
- (Class) getObjectClass:(NSString *)name;
- (id)getObjectInstance:(NSString *)name;

@end

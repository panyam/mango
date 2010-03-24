//
//  Pair.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#include <Foundation/Foundation.h>

@interface Pair : NSObject
{
    id first;
    id second;
}

@property (nonatomic, retain) id first;
@property (nonatomic, retain) id second;

- (id) initWithValues:(id)first second:(id)second;
-(void) dealloc;

@end

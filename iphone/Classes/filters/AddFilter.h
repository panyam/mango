//
//  AddFilter.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Filter.h"

@interface AddFilterContext : NSObject
{
    int addAmount;
}

@property (nonatomic) int addAmount;

@end

@interface AddFilter : Filter
{
}

@end



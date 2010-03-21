//
//  Variable.m
//  DjangoTemplates
//
//  Fully qualified variable names.
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Variable.h"

@implementation Variable

@synthesize value;
@synthesize isNumber;
@synthesize isQuoted;
@synthesize intValue;
@synthesize nextVar;

- (id) init
{
    return [self initWithValueNumAndQuoted:nil isnum:NO isquoted:NO next:nil];
}

- (id) initWithValue:(NSString *)val next:(Variable *)next
{
    return [self initWithValueQuoted:val isquoted:NO next:nil];
}

- (id) initWithValueQuoted:(NSString *)val isquoted:(BOOL)isquoted next:(Variable *)next
{
    return [self initWithValueNumAndQuoted:val
                                     isnum:(!isquoted && [Variable isInteger:val])
                                     isquoted:isquoted
                                     next:next];
}

- (id) initWithValueNumAndQuoted:(NSString *)val
                           isnum:(BOOL)isnum
                        isquoted:(BOOL)isquoted
                            next:(Variable *)next
{
    if (self = [super init])
    {
        value       = [val copy];
        isNumber    = isnum;
        isQuoted    = isquoted;
        nextVar     = [next retain];
    }
    return self;
}

- (void) dealloc
{
    [value release];
    [nextVar release];
    [super dealloc];
}

- (BOOL) isEqual:(NSObject *)another
{
    if (another == nil)
        return NO;
    if (self == another)
        return YES;
    if (![another isKindOfClass:[Variable class]])
        return NO;
    Variable *anotherVar = (Variable *)another;
	NSLog(@"Another Variable Var: '%@'", anotherVar.value);
    if ([anotherVar.value isEqual:value])
        if (anotherVar.isQuoted == self.isQuoted)
            if (anotherVar.isNumber == self.isNumber)
                if (nextVar == anotherVar.nextVar)
                    return YES;
                else if (nextVar != nil)
                    return [nextVar isEqual:anotherVar.nextVar]; 
    return NO;
}

+ (BOOL) isInteger:(NSString *)value
{
    return NO;
}

+ (BOOL) isFloat:(NSString *)value
{
    return NO;
}

@end

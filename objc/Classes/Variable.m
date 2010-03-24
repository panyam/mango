//
//  Variable.m
//  mango
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
@synthesize nextVariable;

- (id) initWithValueQuotedAndNext:(NSString *)val
                         isquoted:(BOOL)isquoted
                             next:(Variable *)next
{
    if (self = [super init])
    {
        isNumber        = YES;
        isQuoted        = isquoted;
        nextVariable    = [next retain];
        [self setValue:val];
    }
    return self;
}

- (id) initWithValueAndNext:(NSString *)val next:(Variable *)next
{
    return [self initWithValueQuotedAndNext:val isquoted:NO next:next];
}

- (id) initWithValueAndQuoted:(NSString *)val isquoted:(BOOL)isquoted
{
    return [self initWithValueQuotedAndNext:val isquoted:isquoted next:nil];
}

- (id) initWithValue:(NSString *)val
{
    return [self initWithValueQuotedAndNext:val isquoted:NO next:nil];
}

- (id) init
{
    return [self initWithValueQuotedAndNext:nil isquoted:NO next:nil];
}

- (void) dealloc
{
    [value release];
    [nextVariable release];
    [super dealloc];
}

- (void) setValue:(NSString *)another
{
    if (value != another)
    {
        [value release];
        isNumber = [Variable isInteger:another];
        intValue = [another intValue];
    }
}

- (Variable *) setNextVariable:(NSString *)val isquoted:(BOOL)isquoted
{
    nextVariable = [[Variable alloc] initWithValueAndQuoted:val
                                                   isquoted:isquoted];
    return nextVariable;
}

- (NSObject *) resolve:(TemplateContext *)context
            topContext:(NodeContext *)topContext
{
    return nil;
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
                if (nextVariable == anotherVar.nextVariable)
                    return YES;
                else if (nextVariable != nil)
                    return [nextVariable isEqual:anotherVar.nextVariable]; 
    return NO;
}

+ (BOOL) isInteger:(NSString *)value
{
    int val;
    return [[NSScanner scannerWithString:value] scanInt:&val];
}

+ (BOOL) isFloat:(NSString *)value
{
    float val;
    return [[NSScanner scannerWithString:value] scanFloat:&val];
}

@end

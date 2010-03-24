//
//  Variable.h
//  DjangoTemplates
//
//  Fully qualified variable names.
//
//  Created by Sri Panyam on 29/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DTForwardDefs.h"

@interface Variable : NSObject
{
    // the item being referred to
    NSString *  value;
    BOOL        isQuoted;
    BOOL        isNumber;
	int			intValue;
    Variable *  nextVariable;
}

@property (nonatomic, copy) NSString *value;
@property (nonatomic) BOOL isNumber;
@property (nonatomic) BOOL isQuoted;
@property (nonatomic, readonly) int intValue;
@property (nonatomic, readonly, retain) Variable *nextVariable;

- (id) initWithValueQuotedAndNext:(NSString *)value
                         isquoted:(BOOL)isquoted
                             next:(Variable *)next;
- (id) initWithValueAndNext:(NSString *)val next:(Variable *)next;
- (id) initWithValueAndQuoted:(NSString *)value isquoted:(BOOL)isquoted;
- (id) initWithValue:(NSString *)val;
- (id) init;
- (id) initWithParser:(Parser *)parser error:(NSError **)error;
- (BOOL) isEqual:(NSObject *)another;
- (Variable *) setNextVariable:(NSString *)value isquoted:(BOOL)isquoted;
- (NSObject *) resolve:(TemplateContext *)context
            topContext:(NodeContext *)topContext;
+ (BOOL) isInteger:(NSString *)value;
+ (BOOL) isFloat:(NSString *)value;

@end

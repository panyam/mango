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

@interface Variable : NSObject
{
    // the item being referred to
    NSString *  value;
    BOOL        isNumber;
    BOOL        isQuoted;
	int			intValue;
    Variable *  nextVar;
}

@property (nonatomic, copy) NSString *value;
@property (nonatomic) BOOL isNumber;
@property (nonatomic) BOOL isQuoted;
@property (nonatomic, readonly) int intValue;
@property (nonatomic, retain) Variable *nextVar;

- (id) init;
- (id) initWithValue:(NSString *)val next:(Variable *)next;
- (id) initWithValueQuoted:(NSString *)value isquoted:(BOOL)isquoted next:(Variable *)next;
- (id) initWithValueNumAndQuoted:(NSString *)value
                           isnum:(BOOL)isnum
                        isquoted:(BOOL)isquoted
                            next:(Variable *)next;
- (BOOL) isEqual:(NSObject *)another;
+ (BOOL) isInteger:(NSString *)value;
+ (BOOL) isFloat:(NSString *)value;

@end

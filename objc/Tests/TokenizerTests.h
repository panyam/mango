//
//  TokenizerTests.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 31/01/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
//  See Also: http://developer.apple.com/iphone/library/documentation/Xcode/Conceptual/iphone_development/135-Unit_Testing_Applications/unit_testing_applications.html

#import <SenTestingKit/SenTestingKit.h>
#import <UIKit/UIKit.h>
#import "Tokenizer.h"

/**
 * These are expectations that we can setup when testing
 * the tokenizer so that after giving an input string, we 
 * can simply check if the scanned tokens match this list.
 */
@interface ExpectedToken : NSObject
{
    TokenType   tokenType;
    NSString *  tokenValue;
}

@property (nonatomic, readonly) TokenType tokenType;
@property (nonatomic, copy) NSString *tokenValue;

+ (id) fromExpectation:(TokenType)type
                 value:(NSString *)value;
- (BOOL) tokenMatches:(Token *)token;
- (void) dealloc;

@end

@interface TokenizerTests : SenTestCase {
    Tokenizer *tokenizer;
    NSMutableArray *expectedTokens;
}

- (void) setUp;
- (void) tearDown;

@end

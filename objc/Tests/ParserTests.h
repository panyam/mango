//
//  ParserTests.h
//  DjangoTemplates
//
//  Created by Sri Panyam on 4/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
//  See Also: http://developer.apple.com/iphone/library/documentation/Xcode/Conceptual/iphone_development/135-Unit_Testing_Applications/unit_testing_applications.html

#import <SenTestingKit/SenTestingKit.h>

@class Tokenizer;
@class Parser;
@class FilterLibrary;
@class TagLibrary;
@class Node;

@interface ParserTests : SenTestCase {
	Tokenizer *tokenizer;
    Parser *parser;
    NSError *error;
	FilterLibrary *filterLibrary;
	TagLibrary	*tagLibrary;
}

- (void) setUp;
- (void) tearDown;
- (void) setUpWithInputString:(NSString *)input;
- (void) checkParsedNodeWith:(Node *)expectedNode;

@end

//
//  main.m
//
//  Copyright 2008 Google Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not
//  use this file except in compliance with the License.  You may obtain a copy
//  of the License at
// 
//  http://www.apache.org/licenses/LICENSE-2.0
// 
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
//  License for the specific language governing permissions and limitations under
//  the License.
//

#import <UIKit/UIKit.h>
#import <stdio.h>
#import "DTPublic.h"

#define TEST_PARSER

// Creates an application that runs all tests from classes extending
// SenTestCase, outputs results and test run time, and terminates right
// afterwards.
int main(int argc, char *argv[]) {
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
#ifdef TEST_TOKENIZER
	NSString *input = @"Hello World";
	Tokenizer *t = [Tokenizer allocFromString:input];
	Token *token = [[Token alloc] initWithTypeAndValue:TOKEN_UNKNOWN value:nil];

	while ([t hasTokensAvailable])
	{
		[t nextToken:token];
		NSLog(@"Token Type: %d, Value: '%@'", token.tokenType, token.tokenValue);
	}
	[token release];
	[t release];
#endif
	
#ifdef TEST_PARSER
	NSError *error = nil;
	NSString *input = @"{{a.b.c}}";
    Tokenizer *tokenizer = [Tokenizer allocFromString:input];
    Parser *parser    = [Parser allocWithTokenizer:tokenizer];
	////////// test data begins here - set expected nodes here
	VariableNode *expectedNode = [[VariableNode alloc] initWithVariable:
								  [[Variable alloc] initWithValue:@"a" next:
								   [[Variable alloc] initWithValue:@"b" next:
									[[Variable alloc] initWithValue:@"c" next:nil]]]
																   next:nil];	////////// test data ends here
	NSLog(@"=====================================");
    Node *node = [parser parse:&error];
	if (node == expectedNode || (node != nil && [node isEqual:expectedNode]))
	{
		NSLog(@"All good");
	}
	else
	{
		NSLog(@"Parsed and Expected nodes do not match.");
	}
	NSLog(@"=====================================");
#endif
	
	[pool release];
	return 0;
}

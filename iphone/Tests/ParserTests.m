//
//  ParserTests
//  DjangoTemplates
//
//  Created by Sri Panyam on 4/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ParserTests.h"
#import "DTPublic.h"

#import "AddFilter.h"
#import "CutFilter.h"
#import "CapFirstFilter.h"

#import "ForTagNode.h"
#import "CycleTagNode.h"

@implementation ParserTests

- (void) setUp
{
    error   = nil;
    filterLibrary = [FilterLibrary sharedInstance];
    [filterLibrary registerObjectClass:@"add" objClass:[AddFilter class]];
    [filterLibrary registerObjectClass:@"cut" objClass:[CutFilter class]];
    [filterLibrary registerObjectClass:@"capfirst" objClass:[CapFirstFilter class]];
    
    tagLibrary = [TagLibrary sharedInstance];
    [tagLibrary registerObjectClass:@"cycle" objClass:[CycleTagNode class]];
    [tagLibrary registerObjectClass:@"for" objClass:[ForTagNode class]];
}

- (void) tearDown
{
    [parser release];
    [tokenizer release];
}

- (void) setUpWithInputString:(NSString *)input
{
    tokenizer = [Tokenizer allocFromString:input];
    parser    = [Parser allocWithTokenizer:tokenizer];
}

- (void) checkParsedNodeWith:(Node *)expectedNode
{
    Node *node = [parser parse:&error];
    STAssertTrue(node != nil && [node isEqual:expectedNode], @"Parsed and expected nodes do not match");
	[node release];
	[expectedNode release];
}


/**
 * Tests the creation of a parser.
 */
- (void) testParserCreate
{
    [self setUpWithInputString:@""];
    Node *node = [parser parse:&error];
    STAssertEquals(node, (Node *)nil, @"Node should be null for empty string");
	[node release];
}

/**
 * Tests the creation of a parser.
 */
- (void) testOnlyFreeText
{
    [self setUpWithInputString:@"Hello World"];
	Node *expectedNode = [[FreeTextNode alloc] initWithContent:@"Hello World"];
    [self checkParsedNodeWith:expectedNode];;
}

- (void) testFreeTextWithComments
{
    [self setUpWithInputString:@"Hello{# A Huge Comment#}World"];
	Node *expectedNode = [[FreeTextNode alloc] initWithContent:@"Hello"];
	expectedNode.nextNode = [[FreeTextNode alloc] initWithContent:@"World"];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testSingleVariable
{
    [self setUpWithInputString:@"{{variable}}"];
	Node *expectedNode = [[VariableNode alloc] initWithVariable:
						  [[Variable alloc] initWithValueNumAndQuoted:@"variable" isnum:NO isquoted:NO next:nil] 
														   next:nil];
    [self checkParsedNodeWith:expectedNode];
}


- (void) testMultipleVariables
{
    [self setUpWithInputString:@"{{a.b.c}}"];
	VariableNode *expectedNode = [[VariableNode alloc] initWithVariable:
										[[Variable alloc] initWithValue:@"a" next:
										 [[Variable alloc] initWithValue:@"b" next:
										  [[Variable alloc] initWithValue:@"c" next:nil]]]
																   next:nil];
    [self checkParsedNodeWith:expectedNode];
}

#if 0

- (void) testMultipleQuotedVariables
{
    [self setUpWithInputString:@"{{a.'b'.'c'}}"];
    VariableNode *expectedNode = [[VariableNode alloc] initWithVariable:
								  [[Variable alloc] initWithValue:@"a" 
									next:[[Variable alloc] initWithValueQuoted:@"b" isquoted:YES 
																		  next:[[Variable alloc] initWithValueQuoted:@"b" isquoted:YES next:nil]]]];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testVariableWithNumericIndexes
{
    [self setUpWithInputString:@"{{a.0.1.d}}"];
	VariableNode *expectedNode = [[VariableNode alloc] initWithVariable:
									[[Variable alloc] initWithValue:@"a" next:
										[[Variable alloc] initWithValue:@"0" next:
										 [[Variable alloc] initWithValue:@"1" next:
										  [[Variable alloc] initWithValue:@"d" next:nil]]]]
								  next:nil];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testVariableWithQuotedIndexes
{
    [self setUpWithInputString:@"{{a.0.'1'.d}}"];
	VariableNode *expectedNode = [[VariableNode alloc] initWithVariable:
								  [[Variable alloc] initWithValue:@"a" next:
								   [[Variable alloc] initWithValue:@"0" next:
									[[Variable alloc] initWithValueQuoted:@"1" isquoted:YES next:
									 [[Variable alloc] initWithValue:@"d" next:nil]]]]
																   next:nil];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testSingleFilter
{
    [self setUpWithInputString:@"{{a|add}}"];
    VariableNode expectedNode = new VariableNode(new Variable("a", false, false, null)];
    [expectedNode addFilterNode(new FilterNode(filterLibrary.getObjectInstance("add"))];
    [self checkParsedNodeWith:expectedNode];
}


- (void) testSingleFilterWithOneArgument
{
    [self setUpWithInputString:@"{{a|add:3}}"];
    VariableNode expectedNode = new VariableNode(new Variable("a", false, false, null)];
    FilterNode addNode = new FilterNode(filterLibrary.getObjectInstance("add")];
    [addNode addArgument(new Variable("3", true, false)];
    [expectedNode addFilterNode(addNode];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testSingleFilterWithOneQuotedArgument
{
    [self setUpWithInputString:@"{{a|add:\"3\"}}"];
    VariableNode expectedNode = new VariableNode(new Variable("a", false, false, null)];
    FilterNode addNode = new FilterNode(filterLibrary.getObjectInstance("add")];
    [addNode addArgument(new Variable("3", false, true)];
    [expectedNode addFilterNode(addNode];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testSingleFilterWithMultipleArguments
{
    [self setUpWithInputString:@"{{a|add:(3,'4',five)}}"];
    VariableNode expectedNode = new VariableNode(new Variable("a", false, false, null)];
    FilterNode addNode = new FilterNode(filterLibrary.getObjectInstance("add")];
    [addNode addArgument(new Variable("3", true, false)];
    [addNode addArgument(new Variable("4", false, true)];
    [addNode addArgument(new Variable("five", false, false)];
    [expectedNode addFilterNode(addNode];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testMultipleFilters
{
    [self setUpWithInputString:@"{{a|add|add|add}}"];
    VariableNode expectedNode = new VariableNode(new Variable("a", false, false, null)];
    [expectedNode addFilterNode(new FilterNode(filterLibrary.getObjectInstance("add"))];
    [expectedNode addFilterNode(new FilterNode(filterLibrary.getObjectInstance("add"))];
    [expectedNode addFilterNode(new FilterNode(filterLibrary.getObjectInstance("add"))];
    [self checkParsedNodeWith:expectedNode];
}

- (void) testMultipleFiltersWithArguments
{
    [self setUpWithInputString:@"{{a|add|add:1|add:(2,'3')}}"];
    VariableNode expectedNode = new VariableNode(new Variable("a", false, false, null)];
    FilterNode addNode = new FilterNode(filterLibrary.getObjectInstance("add")];
    [expectedNode addFilterNode(new FilterNode(filterLibrary.getObjectInstance("add"))];

    addNode = new FilterNode(filterLibrary.getObjectInstance("add")];
    [addNode addArgument(new Variable("1", true, false)];
    [expectedNode addFilterNode(addNode];        

    addNode = new FilterNode(filterLibrary.getObjectInstance("add")];
    [addNode addArgument(new Variable("2", true, false)];
    [addNode addArgument(new Variable("3", false, true)];
    [expectedNode addFilterNode(addNode];        

    [self checkParsedNodeWith:expectedNode];
}

///////////////    Testing tags now!!!
public void testSingleUnclosedTag()
{
    setUpWithInputString("{% for a in listofas %}");
    checkParsedNodeForException(-1, "End nodes were not found");
}

public void testDiscardingTokens()
{
    setUpWithInputString("{% a b c %}Hello World");
    try {
        parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
        checkParsedNodeWith(new FreeTextNode("Hello World"));
    } catch (ParserException e) {
        e.printStackTrace();
    }
}

public void testSimpleForTag()
{
    setUpWithInputString("{% for a in listofas %}{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    checkParsedNodeWith(ftn);
}

public void testForTagWithChild()
{
    setUpWithInputString("{% for a in listofas %}Hello World{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    ftn.childNodes = new FreeTextNode("Hello World");
    checkParsedNodeWith(ftn);
}

public void testForTagWithChildAndEmpty()
{
    setUpWithInputString("{% for a in listofas %}Hello World{%empty%}Empty Content{%endfor%}");
    ForTagNode ftn = new ForTagNode(new Variable("listofas"));
    ftn.addItem(new Variable("a"));
    ftn.childNodes = new FreeTextNode("Hello World");
    ftn.emptyNodes = new FreeTextNode("Empty Content");
    checkParsedNodeWith(ftn);
}
#endif

@end

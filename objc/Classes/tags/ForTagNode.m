//
//  ForTagNode.m
//  DjangoTemplates
//
//  Created by Sri Panyam on 16/02/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ForTagNode.h"

@interface ForTagNode()
- (void) parseItemList:(Parser *)parser error:(NSError **)error;
- (void) parseSourceVariable:(Parser *)parser error:(NSError **)error;
- (void) parseTillEndTag:(Parser *)parser error:(NSError **)error;
@end

@implementation ForTagNode

@synthesize items;
@synthesize emptyNode;
@synthesize sourceVariable;

const NSString *EMPTY_OR_ENDFOR[3] = { @"empty", @"endfor", nil };
const NSString ENDFOR[2] = { @"endfor", nil };

/**
 * Creates a ForTagNode directly without parsing from the input.
 */
- (id) initWithVariable:(Variable *)variable
{
	return [self initWithVariableNextAndChild:variable next:nil child:nil];
}

/**
 * Creates a ForTagNode directly without parsing from the input.
 */
- (id) initWithVariableAndNext:(Variable *)variable next:(Node *)next
{
	return [self initWithVariableNextAndChild:variable next:next child:nil];
}


/**
 * Creates a ForTagNode directly without parsing from the input.
 */
- (id) initWithVariableNextAndChild:(Variable *)var next:(Node *)next child:(Node *)child
{
	if (self = [super initWithNextNodeAndChild:next child:child])
	{
		sourceVariable = var;
	}
	return self;
}

/**
 * Extracts the tag node from the parser.
 */
- (id) initWithParser:(Parser *)parser error:(NSError **)error
{
	if (self = [super initWithNextNodeAndChild:nil child:nil])
	{
		[self parseItemList:parser error:error];
		[self parseSourceVariable:parser error:error];
		[self parseTillEndTag:parser error:error];
	}
	return self;
}

- (void) dealloc
{
	[items removeAllObjects];
	[items release];
	[sourceVariable release];
	[emptyNode release];
	[super dealloc];
}

- (BOOL) equalsTagNode:(TagNode *)another
{
    if (![another isKindOfClass:[ForTagNode class]])
        return NO;

    return YES;
}

- (void) parseItemList:(Parser *)parser error:(NSError **)error
{
}

- (void) parseSourceVariable:(Parser *)parser error:(NSError **)error
{
}

- (void) parseTillEndTag:(Parser *)parser error:(NSError **)error
{
}

- (void) addItem:(Variable *)variable
{
}

@end

#if 0


    /**
     * Parse the list of items before the "in".
     */
    public void parseItemList(Parser parser)
    {
        // now read the tokens
        Token token = parser.expectTokenInList(TokenLists.IDENT_OR_OPEN_PAREN);
        if (token.tokenType == TokenType.TOKEN_OPEN_PAREN)
        {
            token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
            while (true)
            {
                String varValue = token.tokenValue.toString();
                Variable nextVar = new Variable(varValue, token.tokenType == TokenType.TOKEN_QUOTED_STRING, null);
                addItem(nextVar);
                token = parser.expectTokenInList(TokenLists.COMA_OR_CLOSE_PAREN);
                if (token.tokenType == TokenType.TOKEN_CLOSE_PAREN)
                    break ;
                else if (token.tokenType == TokenType.TOKEN_COMA)
                    token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
            }
        }
        else if (token.tokenType == TokenType.TOKEN_IDENTIFIER) 
        {
            String varValue = token.tokenValue.toString();
            Variable nextVar = new Variable(varValue, token.tokenType == TokenType.TOKEN_QUOTED_STRING, null);
            addItem(nextVar);
        }
        else
        {
            parser.throwError("Internal Error.  This case should have been caught by expectTokensInList");
        }
        
        // now read and discard the "in" token - we treat this just as an identifier
        token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
        if (!token.tokenValue.toString().equalsIgnoreCase("in"))
        {
            parser.throwError("Expected 'in', but found '" + token.tokenValue + "'");
        }
    }
    
    /**
     * 
     * @param parser
     */
    protected void parseSourceVariable(Parser parser)
    {
        sourceVariable = ParseUtils.parseVariable(parser);
        parser.expectToken(TokenType.TOKEN_CLOSE_TAG);
    }

    /**
     * Parses for the child nodes (and empty node) until the "endfor" is found.
     * @param parser
     */
    protected void parseTillEndTag(Parser parser)
    {
    	childNode = parser.parseTillNodeInList(EMPTY_OR_ENDFOR);
    	// see what the node name was if it was "empty" then read again
    	Token token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
    	if (token.tokenValue.toString().equals("empty"))
    	{
    		// read till end-tag variable
    		parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
    		emptyNode = parser.parseTillNodeInList(ENDFOR);
        	token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
    		parser.discardTokensTill(TokenType.TOKEN_CLOSE_TAG);
    	}
    }

    /**
     * Adds a new variable to the item list.
     * @param var
     */
    public void addItem(Variable var)
    {
        if (items == null)
            items = new Vector<Variable>();
        items.add(var);
    }

    /**
     * Compares specifically with another tag node.
     * We can safely assume that here another is neither this nor null.
     * @param another
     * @return true if objects are equal.
     */
    public boolean equalsTagNode(TagNode another)
    {
        if (!(another instanceof ForTagNode))
            return false;

        ForTagNode ftNode = (ForTagNode)another;
        
        if ((sourceVariable != null && sourceVariable.equals(ftNode.sourceVariable)) ||
            (sourceVariable == ftNode.sourceVariable))
        {
            if ((emptyNode != null && emptyNode.equals(ftNode.emptyNode)) ||
                    (emptyNode == ftNode.emptyNode))
            {
                return CompareUtils.CompareVectors(items, ftNode.items);
            }
        }
        return false;
    }
#endif

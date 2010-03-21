/**
 * 
 */
package com.panyam.mango.templates.test;

import java.io.*;
import java.util.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.filters.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.tags.*;
import com.panyam.mango.templates.variables.*;

import junit.framework.TestCase;

/**
 * TestCases to test the parser
 * 
 * @author Sri Panyam
 */
public class ParserTests extends TestCase 
{
	Tokenizer tokenizer;
	Parser parser;
	FilterLibrary filterLibrary;
	TagLibrary	tagLibrary;
	TemplateLoader loader;

	/**
	 * @param Name of the tests cases.
	 */
	public ParserTests(String name) {
		super(name);
	}

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#setUp()
	 */
	protected void setUp() throws Exception {
		super.setUp();
		filterLibrary = FilterLibrary.getSharedInstance();
		filterLibrary.registerObjectClass("add", AddFilter.class);
		filterLibrary.registerObjectClass("cut", CutFilter.class);
		filterLibrary.registerObjectClass("capfirst", CapFirstFilter.class);
		
		tagLibrary = TagLibrary.getSharedInstance();
		tagLibrary.registerObjectClass("cycle", CycleTagNode.class);
		tagLibrary.registerObjectClass("for", ForTagNode.class);
	}

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#tearDown()
	 */
	protected void tearDown() throws Exception {
		super.tearDown();
	}

    /**
     * Sets up the tokenizer with an input string.
     */
    protected void setUpWithInputString(String input)
    {
	    tokenizer = new Tokenizer(new BufferedReader(new StringReader(input)));
	    parser	= new Parser(tokenizer);
    }

    /**
     * Checkes that the parsed node matches what we are expecting.
     * @param expectedNode
     */
    protected void checkParsedNodeWith(Node ... expectedNodes) 
    {
		Node node;
		try {
			node = parser.parse(loader);
			if (node instanceof NodeList)
			{
				NodeList nodeList = (NodeList)node;
				assertEquals("Number of do not match.",expectedNodes.length, nodeList == null ? 0 : nodeList.childNodeCount());
				Iterator<Node> iterator = nodeList.iterator();
				if (iterator != null)
				{
					for (int i = 0;i < expectedNodes.length;i++)
					{
						Node expectedNode = expectedNodes[i];
						if (!iterator.hasNext())
						{
							fail("No more nodes left");
						}
						assertEquals("Node, " + i + " does not match", expectedNode, iterator.next());
					}
				}
			}
			else if (node != null)
			{
				assertEquals("More than 1 node was expected", expectedNodes.length, 1);
				assertEquals("Nodes do not match", expectedNodes[0], node);
			}
			else
			{
				assertTrue("Expected null nodes", expectedNodes == null || expectedNodes.length == 1 && expectedNodes[0] == null);
			}
		} catch (ParserException pe) {
	    	fail("Got Parser Exception: " + pe.getMessage());
			pe.printStackTrace();
		}
    }

    public void checkParsedNodeForException(int code, String message)
    {
    	try
    	{
			parser.parse(loader);
	    	fail("Didnt get expected ('" + message + "') exception");
    	}
    	catch (ParserException pe)
    	{
    		assertEquals("Error codes did not match", code, pe.getErrorCode());
    		if (message != null)
    		{
    			assertEquals("Error messages did not match", message, pe.getMessage());
    		}
    	}
    }
    /**
	 * Tests the creation of a parser.
	 */
	public void testParserCreate()
	{
		setUpWithInputString("");
		try {
			Node nodeList = parser.parse(loader);
			assertEquals("Node should be null for empty string", null, nodeList);
		} catch (ParserException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Tests the creation of a parser.
	 */
	public void testOnlyFreeText()
	{
		setUpWithInputString("Hello World");
		checkParsedNodeWith(new FreeTextNode("Hello World"));
	}

	public void testFreeTextWithComments()
	{
		setUpWithInputString("Hello{# A Huge Comment#}World");
		checkParsedNodeWith(new FreeTextNode("Hello"), 
							new FreeTextNode("World"));
	}
	
	public void testSingleVariable()
	{
		setUpWithInputString("{{variable}}");
		checkParsedNodeWith(new VariableNode(new Variable("variable", false, null)));
	}
	
	public void testMultipleVariables()
	{
		setUpWithInputString("{{a.b.c}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", 
														new Variable("b",
															new Variable("c", null))), null);
		checkParsedNodeWith(expectedNode);
	}
	
	public void testMultipleQuotedVariables()
	{
		setUpWithInputString("{{a.'b'.'c'}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", 
														new Variable("b", true,
															new Variable("c", true, null))), null);
		checkParsedNodeWith(expectedNode);
	}
	
	public void testVariableWithNumericIndexes()
	{
		setUpWithInputString("{{a.0.1.d}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", 
														new Variable("0", 
															new Variable("1", 
																new Variable("d", null)))), null);
		checkParsedNodeWith(expectedNode);
	}
	
	public void testVariableWithQuotedIndexes()
	{
		setUpWithInputString("{{a.0.'1'.d}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", 
														new Variable("0", 
															new Variable("1", true,
																new Variable("d", null)))), null);
		checkParsedNodeWith(expectedNode);
	}
	
	public void testFiltersAreSingletons()
	{
		Filter f1 = filterLibrary.makeNewInstance("add");
		Filter f2 = filterLibrary.makeNewInstance("add");
		assertEquals("Filters are not equal as should be with singletons", f1, f2);
	}

	public void testSingleFilter()
	{
		setUpWithInputString("{{a|add}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
		expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
		checkParsedNodeWith(expectedNode);
	}
	
	
	public void testSingleFilterWithOneArgument()
	{
		setUpWithInputString("{{a|add:3}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
		FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
		addNode.addArgument(new Variable("3", false));
		expectedNode.addFilterNode(addNode);
		checkParsedNodeWith(expectedNode);
	}
	
	public void testSingleFilterWithOneQuotedArgument()
	{
		setUpWithInputString("{{a|add:\"3\"}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
		FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
		addNode.addArgument(new Variable("3", true));
		expectedNode.addFilterNode(addNode);
		checkParsedNodeWith(expectedNode);
	}
	
	public void testSingleFilterWithMultipleArguments()
	{
		setUpWithInputString("{{a|add:(3,'4',five)}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
		FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
		addNode.addArgument(new Variable("3", false));
		addNode.addArgument(new Variable("4", true));
		addNode.addArgument(new Variable("five", false));
		expectedNode.addFilterNode(addNode);
		checkParsedNodeWith(expectedNode);
	}

	public void testMultipleFilters()
	{
		setUpWithInputString("{{a|add|add|add}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
		expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
		expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
		expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));
		checkParsedNodeWith(expectedNode);
	}

	public void testMultipleFiltersWithArguments()
	{
		setUpWithInputString("{{a|add|add:1|add:(2,'3')}}");
		VariableNode expectedNode = new VariableNode(new Variable("a", false, null));
		FilterNode addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
		expectedNode.addFilterNode(new FilterNode(filterLibrary.makeNewInstance("add")));

		addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
		addNode.addArgument(new Variable("1", false));
		expectedNode.addFilterNode(addNode);		

		addNode = new FilterNode(filterLibrary.makeNewInstance("add"));
		addNode.addArgument(new Variable("2", false));
		addNode.addArgument(new Variable("3", true));
		expectedNode.addFilterNode(addNode);		

		checkParsedNodeWith(expectedNode);
	}
	
	///////////////	Testing tags now!!!

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
	
	public void testParseTillNode()
	{
	}
}

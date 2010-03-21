/**
 * 
 */
package com.panyam.mango.templates.test;

import java.io.*;
import junit.framework.TestCase;

import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.utils.*;
import com.panyam.mango.templates.variables.*;

/**
 * A bunch of test cases to test out variable name/value resolutions.
 * 
 * @author Sri Panyam
 */
public class ResolverTests extends TestCase 
{
	VariableResolver resolver = null;
	Parser parser = null;
	Variable variable = null;
	TemplateContext context;

	/**
	 * @param name
	 */
	public ResolverTests(String name) 
	{
		super(name);
	}

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#setUp()
	 */
	protected void setUp() throws Exception {
		super.setUp();
		context = new TemplateContext();
		resolver = new DefaultVariableResolver();
	}

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#tearDown()
	 */
	protected void tearDown() throws Exception {
		super.tearDown();
	}

	protected void setupParserAndParseVariable(String input)
	{
	    Tokenizer tokenizer = new Tokenizer(new BufferedReader(new StringReader(input)));
	    parser	= new Parser(tokenizer);
	}

	protected void checkResolvedVariable(Object expectedValue)
	{
	    try {
	    	parser.expectToken(TokenType.TOKEN_OPEN_VARIABLE);
			variable = ParseUtils.parseVariable(parser);
	    	parser.expectToken(TokenType.TOKEN_CLOSE_VARIABLE);
		} catch (ParserException e) {
			fail("Should not have gotten a parser exception: " + e.getMessage());
			e.printStackTrace();
		}
	    Object resolvedValue = resolver.resolveVariableChain(context, variable);
		assertEquals("Expected and Resolved values do not match", expectedValue, resolvedValue);
	}

	public void testUnresolvedVariable()
	{
		setupParserAndParseVariable("{{a}}");
		checkResolvedVariable(null);
	}
	
	public void testNumericVariable()
	{
		setupParserAndParseVariable("{{a}}");
		context.setValue("a", 3);
		checkResolvedVariable(3);
	}

	public void testStringVariable()
	{
		setupParserAndParseVariable("{{a}}");
		context.setValue("a", "Hello World");
		checkResolvedVariable("Hello World");
	}

	public void testDeleteContextValue()
	{
		setupParserAndParseVariable("{{a}}");
		context.setValue("a", "Hello World");
		context.deleteValue("a");
		checkResolvedVariable(null);
	}

	public void testValueAsHashTable()
	{
		setupParserAndParseVariable("{{a.b}}");
		context.setValue("a", Utils.makeHashtable("b", 3));
		checkResolvedVariable(3);
	}

	public void testValueAsMap()
	{
		setupParserAndParseVariable("{{a.b}}");
		context.setValue("a", Utils.makeHashMap("b", 3));
		checkResolvedVariable(3);
	}

	public void testValueAsIndex()
	{
		context.setValue("a", Utils.makeHashMap("b", Utils.makeArrayList(3, 4, 5)));
		setupParserAndParseVariable("{{a.b.0}}");
		checkResolvedVariable(3);
		setupParserAndParseVariable("{{a.b.1}}");
		checkResolvedVariable(4);
		setupParserAndParseVariable("{{a.b.2}}");
		checkResolvedVariable(5);
	}

	public void testValueAsClassWithSimpleMethod()
	{
		context.setValue("a", Utils.makeHashMap("b", 
				new Object() { @SuppressWarnings("unused")
				public Object elementAtIndex(final int i) { return i; } } ));
		setupParserAndParseVariable("{{a.b.4}}");
		checkResolvedVariable(4);
	}

	public void testValueAsClassWithComplexMethod()
	{
		context.setValue("a", Utils.makeHashMap("b", 
				new Object() { 
					@SuppressWarnings("unused")
					public Object elementAtIndex(final int i) {
						return new Object() {
							public Object elementAtIndex(int j)
							{
								return i * j;
							}
						};
					} }));
		setupParserAndParseVariable("{{a.b.4.3}}");
		checkResolvedVariable(12);
	}

	public void testValueAsSimpleField()
	{
		context.setValue("a", new Object() { @SuppressWarnings("unused") public int b = 3; });
		setupParserAndParseVariable("{{a.b}}");
		checkResolvedVariable(3);
	}

	public void testValueAsSimpleMethod()
	{
		context.setValue("a", new Object() { @SuppressWarnings("unused") public int b() { return 666; } });
		setupParserAndParseVariable("{{a.b}}");
		checkResolvedVariable(666);
	}
}

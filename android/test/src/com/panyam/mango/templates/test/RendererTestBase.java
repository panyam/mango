package com.panyam.mango.templates.test;

import java.io.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.filters.*;
import com.panyam.mango.templates.tags.*;
import com.panyam.mango.templates.parser.*;

import junit.framework.TestCase;

public abstract class RendererTestBase extends TestCase 
{
	Tokenizer tokenizer;
	Parser parser;
	FilterLibrary filterLibrary;
	TagLibrary	tagLibrary;
	Node parsedNodes;
	TemplateContext context;
	Renderer renderer;
	TemplateLoader loader;
	
	public RendererTestBase(String name) 
	{
		super(name);
	}

	protected MockTemplateLoader getLoader() {
		return (MockTemplateLoader)loader;
	}

	protected void setUp() throws Exception {
		super.setUp();
		filterLibrary = FilterLibrary.getSharedInstance();
		filterLibrary.registerObjectClass("add", AddFilter.class);
		filterLibrary.registerObjectClass("cut", CutFilter.class);
		filterLibrary.registerObjectClass("capfirst", CapFirstFilter.class);
		
		tagLibrary = TagLibrary.getSharedInstance();
		tagLibrary.registerObjectClass("cycle", CycleTagNode.class);
		tagLibrary.registerObjectClass("for", ForTagNode.class);
		tagLibrary.registerObjectClass("if", IfTagNode.class);
		tagLibrary.registerObjectClass("include", IncludeTagNode.class);
		tagLibrary.registerObjectClass("block", BlockTagNode.class);
		tagLibrary.registerObjectClass("extends", ExtendsTagNode.class);

		context = new TemplateContext();
		renderer = new Renderer();
		loader = new MockTemplateLoader();
	}

	protected void tearDown() throws Exception {
		super.tearDown();
	}

	protected void setupWithInputString(String input)
	{
	    tokenizer = new Tokenizer(new BufferedReader(new StringReader(input)));
	    parser	= new Parser(tokenizer);
	    try
	    {
	    	parsedNodes = parser.parse(loader);
	    }
	    catch (ParserException pe)
	    {
	    	pe.printStackTrace();
	    	fail("Got Parser Exception: " + pe.getMessage());
	    }
	}

	/**
	 * Loads a template under a name.
	 * 
	 * @param name
	 * @param contents
	 * @return
	 */
	protected Node loadTemplate(String name, String contents)
	{
		try {
			Tokenizer tok = new Tokenizer(new BufferedReader(new StringReader(contents)));
			Parser p2 = new Parser(tok);
			Node node = p2.parse(loader);
			getLoader().SetTemplate(name, node);
			return node;
		} catch (ParserException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}

	protected void checkRenderedOutput(String output)
	{
		StringWriter writer = new StringWriter();
		if (parsedNodes != null)
		{
			try {
				renderer.renderNode(parsedNodes, writer, context);
			} catch (IOException e) {
				fail("Unexpected IO Exception: " + e.getMessage());
				e.printStackTrace();
			}
		}
		assertEquals("Expected and Rendered outputs do not match", output, writer.getBuffer().toString());
	}
}

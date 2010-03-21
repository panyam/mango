package com.panyam.mango.templates.test;

import java.io.*;
import java.util.*;
import java.net.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.*;

class MockTemplateLoader implements TemplateLoader
{
	HashMap<URI, Node> templates = new HashMap<URI, Node>();
	
	public Node loadTemplate(URI uri) throws IOException, ParserException {
		return templates.get(uri);
	}
	
	public void SetTemplate(String name, Node node)
	{
		try {
			templates.put(new URI(name), node);
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}
	}
}

public class IncludeTagTests extends RendererTestBase 
{
	public IncludeTagTests(String name) 
	{
		super(name);
	}

	protected MockTemplateLoader getLoader() {
		return (MockTemplateLoader)loader;
	}
	
	protected void setUp() throws Exception {
		loader = new MockTemplateLoader();
		super.setUp();
	}

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
	
	public void testEmptyFile()
	{
		loadTemplate("empty_template", "");
		setupWithInputString("{% include 'empty_template' %}");
		checkRenderedOutput("");
	}
	
	public void testIncludeFile()
	{
		loadTemplate("simple_template", "Hello World");
		setupWithInputString("{% include 'simple_template' %}");
		checkRenderedOutput("Hello World");
	}
	
	public void testIncludeFileFromIncludeFile()
	{
		loadTemplate("template1", "Hello World");
		loadTemplate("template2", "Hello World {% include 'template1' %} Hello World");
		setupWithInputString("{% include 'template2' %}");
		checkRenderedOutput("Hello World Hello World Hello World");
	}
	
	public void testIncludeFileAsVariable()
	{
		loadTemplate("template1", "Hello World in Template 1");
		loadTemplate("template2", "Hello World in Template 2");
		context.setValue("template", "template1");
		setupWithInputString("{% include template %}");
		checkRenderedOutput("Hello World in Template 1");
		context.setValue("template", "template2");
		checkRenderedOutput("Hello World in Template 2");
	}
	
	public void testIncludeInForLoopWithChangingVariable()
	{
		loadTemplate("template1", "Hello World 1");
		loadTemplate("template2", "Hello World 2");
		loadTemplate("template3", "Hello World 3");
		loadTemplate("template4", "Hello World 4");
		loadTemplate("template5", "Hello World 5");
		
		context.setValue("templates", Utils.makeArrayList("template1", "template2", "template3", "template4", "template5"));
		setupWithInputString("{%for template in templates%}{%include template%} {%endfor%}");
		checkRenderedOutput("Hello World 1 Hello World 2 Hello World 3 Hello World 4 Hello World 5 ");
	}
}

package com.panyam.mango.templates.test;

public class IncludeTagTests extends RendererTestBase 
{
	public IncludeTagTests(String name) 
	{
		super(name);
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

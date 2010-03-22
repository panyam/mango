package com.panyam.mango.templates.test;

import com.panyam.mango.templates.tags.ExtendsTagNode;

public class ExtendsTagTests extends RendererTestBase 
{
	public ExtendsTagTests(String name) 
	{
		super(name);
	}
	
	/**
	 * Extending an empty file.
	 * Check that only the block children are accepted and others are discarded.
	 */
	public void testParsingAndDiscardNonBlockChildren()
	{
		loadTemplate("empty", "");
		setupWithInputString("{% extends 'empty' %}{% block block1 %}{%endblock%}{%block block2 %}{%endblock%}HelloWorld{%endextends%}");
		ExtendsTagNode etn = (ExtendsTagNode)parsedNodes;
		assertEquals(2, etn.getBlockCount());
	}
	
	/**
	 * Extending an empty file.
	 * Output should be nothing as there is nothing to extend.
	 */
	public void testExtendingEmptyBlock()
	{
		loadTemplate("empty", "");
		setupWithInputString("{% extends 'empty' %}{% block block1 %}{%endblock%}{%block block2 %}{%endblock%}HelloWorld{%endextends%}");
		checkRenderedOutput("");
	}
	
	/**
	 * Extending a block that is not in the parent.
	 * Output should be same as the parent.
	 */
	public void testExtendingNonExistingBlocks()
	{
		loadTemplate("empty", "{%block block0 %}{% endblock %}");
		setupWithInputString("{% extends 'empty' %}{% block block1 %}{%endblock%}{%endextends%}");
		checkRenderedOutput("");
	}
}

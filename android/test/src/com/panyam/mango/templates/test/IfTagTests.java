package com.panyam.mango.templates.test;

public class IfTagTests extends RendererTestBase 
{
	public IfTagTests(String name) 
	{
		super(name);
	}

	public void testIfTagCreate()
	{
		setupWithInputString("{% if 1 %}True{% endif %}");
		checkRenderedOutput("True");
	}

	public void testIfEndIfTagCreate()
	{
		setupWithInputString("{% if 0 %}True{%else%}False{% endif %}");
		checkRenderedOutput("False");
	}

	public void testIfElseIfTagCreate()
	{
		setupWithInputString("{% if 0 %}True{%elseif 0%}Second{%elseif 1%}Third{%else%}Finally{% endif %}");
		checkRenderedOutput("Third");
	}

	public void testIfElseIfEndIfTagCreate()
	{
		context.setValue("a", 1);
		context.setValue("b", 2);
		setupWithInputString("{% if 0 %}True{%elseif 0%}Second{%elseif a == b %}Third{%else%}Finally{% endif %}");
		checkRenderedOutput("Finally");
	}

	public void testIfElseIfEndIfTagCreate2()
	{
		context.setValue("a", 1);
		context.setValue("b", 2);
		context.setValue("c", 3);
		setupWithInputString("{% if 0 %}True{%elseif 0%}Second{%elseif a < b and b < c%}Third{%else%}Finally{% endif %}");
		checkRenderedOutput("Third");
	}
}

/**
 * 
 */
package com.panyam.mango.templates.test;

/**
 * Test cases to test out the rendering.
 * 
 * @author Sri Panyam
 */
public class ForLoopTests extends RendererTestBase 
{
	/**
	 * @param name
	 */
	public ForLoopTests(String name) {
		super(name);
	}

	public void testForLoopNodes()
	{
		context.setValue("intlist", Utils.makeArrayList(1, 2, 3));
		setupWithInputString("{%for a in intlist%}Item {{a}},{%endfor%}");
		checkRenderedOutput("Item 1,Item 2,Item 3,");
	}

	public void testEmptyForLoop()
	{
		context.setValue("intlist", null);
		setupWithInputString("{%for a in intlist%}Item {{a}},{%empty%}No Output Found{%endfor%}");
		checkRenderedOutput("No Output Found");
	}

	public void testForLoopVariables()
	{
		context.setValue("intlist", Utils.makeArrayList(1, 2, 3));
		setupWithInputString("{%for a in intlist%}{{a}} - [{{forloop.counter0}},{{forloop.counter}},{{forloop.first}},{{forloop.last}}]\n{%endfor%}");
		checkRenderedOutput("1 - [0,1,true,false]\n" + 
						   "2 - [1,2,false,false]\n" +
						   "3 - [2,3,false,true]\n");
	}
	
	public void testLoopVariableDiesOutsideLoop()
	{
		context.setValue("i", Utils.makeArrayList(1, 2, 3));
		context.setValue("j", Utils.makeArrayList(1, 2, 3));
		setupWithInputString("{%for a in i%}{{a}}{%endfor%}{{a}}");
		checkRenderedOutput("123");
	}

	public void testLoopWithinLoop()
	{
		context.setValue("i", Utils.makeArrayList(1, 2, 3));
		context.setValue("j", Utils.makeArrayList(1, 2, 3));
		setupWithInputString("{%for a in i%}" + 
								"{%for b in j %}" +
								"|{{a}},{{b}},{{forloop.parentloop.counter0}},{{forloop.counter0}}|" +
								"{%endfor%}{%endfor%}");
								
		checkRenderedOutput("|1,1,0,0||1,2,0,1||1,3,0,2|" + 
							  "|2,1,1,0||2,2,1,1||2,3,1,2|" + 
							  "|3,1,2,0||3,2,2,1||3,3,2,2|");
	}
}

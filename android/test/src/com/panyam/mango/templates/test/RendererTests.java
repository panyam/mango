/**
 * 
 */
package com.panyam.mango.templates.test;

/**
 * Test cases to test out the rendering.
 * 
 * @author Sri Panyam
 */
public class RendererTests extends RendererTestBase 
{
	/**
	 * @param name
	 */
	public RendererTests(String name) {
		super(name);
	}

	public void testRenderBlankString()
	{
		setupWithInputString("Hello World");
		checkRenderedOutput("Hello World");
	}

	public void testUnresolvedVariable()
	{
		setupWithInputString("{{a}}");
		checkRenderedOutput("");
	}
	
	public void testNumericVariable()
	{
		context.setValue("a", 3);
		setupWithInputString("{{a}}");
		checkRenderedOutput("3");
	}

	public void testStringVariable()
	{
		setupWithInputString("{{a}}");
		context.setValue("a", "Hello World");
		checkRenderedOutput("Hello World");
	}

	public void testDeleteContextValue()
	{
		setupWithInputString("{{a}}");
		context.setValue("a", "Hello World");
		context.deleteValue("a");
		checkRenderedOutput("");
	}

	public void testValueAsHashTable()
	{
		setupWithInputString("{{a.b}}");
		context.setValue("a", Utils.makeHashtable("b", 3));
		checkRenderedOutput("3");
	}

	public void testValueAsMap()
	{
		setupWithInputString("{{a.b}}");
		context.setValue("a", Utils.makeHashMap("b", 3));
		checkRenderedOutput("3");
	}

	public void testValueAsIndex()
	{
		context.setValue("a", Utils.makeHashMap("b", Utils.makeArrayList(3, 4, 5)));
		setupWithInputString("{{a.b.0}}");
		checkRenderedOutput("3");
		setupWithInputString("{{a.b.1}}");
		checkRenderedOutput("4");
		setupWithInputString("{{a.b.2}}");
		checkRenderedOutput("5");
	}

	public void testValueAsClassWithSimpleMethod()
	{
		context.setValue("a", Utils.makeHashMap("b", 
				new Object() { @SuppressWarnings("unused")
				public Object elementAtIndex(final int i) { return i; } } ));
		setupWithInputString("{{a.b.4}}");
		checkRenderedOutput("4");
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
		setupWithInputString("{{a.b.4.3}}");
		checkRenderedOutput("12");
	}

	public void testValueAsSimpleField()
	{
		context.setValue("a", new Object() { @SuppressWarnings("unused") public int b = 3; });
		setupWithInputString("{{a.b}}");
		checkRenderedOutput("3");
	}

	public void testValueAsSimpleMethod()
	{
		context.setValue("a", new Object() { @SuppressWarnings("unused") public int b() { return 666; } });
		setupWithInputString("{{a.b}}");
		checkRenderedOutput("666");
	}


	public void testTwoNodes()
	{
		context.setValue("a", 1);
		context.setValue("b", "Cool");
		context.setValue("c", new Object() { @SuppressWarnings("unused") public String b() { return "Things"; } });
		setupWithInputString("{{a}} Hello");
		checkRenderedOutput("1 Hello");
	}

	public void testMultipeNodesWithFailure()
	{
		context.setValue("a", 1);
		context.setValue("b", "Cool");
		context.setValue("c", new Object() { @SuppressWarnings("unused") public String b() { return "Things"; } });
		setupWithInputString("{{a}} Hello {{b}} World {{c.d}}");
		checkRenderedOutput("1 Hello Cool World ");
	}

	public void testMultipeNodesWithSuccess()
	{
		context.setValue("a", 1);
		context.setValue("b", "Cool");
		context.setValue("c", new Object() { @SuppressWarnings("unused") public String d() { return "Things"; } });
		setupWithInputString("{{a}} Hello {{b}} World {{c.d}}");
		checkRenderedOutput("1 Hello Cool World Things");
	}
}

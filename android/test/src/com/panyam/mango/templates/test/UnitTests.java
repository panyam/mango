package com.panyam.mango.templates.test;

import junit.framework.Test;
import junit.framework.TestSuite;

public class UnitTests {
	public static Test suite() {
		TestSuite suite = new TestSuite(
				"Test for com.panyam.mango.templates.test");
		//$JUnit-BEGIN$
		//suite.addTestSuite(TokenizerTests.class);
		//suite.addTestSuite(ParserTests.class);
		//suite.addTestSuite(RendererTests.class);
		//$JUnit-END$
		return suite;
	}

}

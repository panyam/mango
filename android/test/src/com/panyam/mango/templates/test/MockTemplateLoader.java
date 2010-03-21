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

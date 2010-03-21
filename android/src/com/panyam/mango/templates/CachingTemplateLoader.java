package com.panyam.mango.templates;

import java.net.*;
import java.io.*;
import java.util.*;

import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.Parser;
import com.panyam.mango.templates.parser.ParserException;
import com.panyam.mango.templates.parser.Tokenizer;

public class CachingTemplateLoader implements TemplateLoader 
{
	class NodeState
	{
		Node node;
		Object state;
	}

	protected HashMap<URI, Node>	nodeMap;
	
	/**
	 * Loads a template or from the cache.
	 * @throws URISyntaxException 
	 */
	public Node loadTemplate(URI uri) throws IOException, ParserException
	{
		if ( ! nodeMap.containsKey(uri))
		{
			// URI uri = new URI(source);
			InputStream iStream = uri.toURL().openStream();
			BufferedReader reader = new BufferedReader(new InputStreamReader(iStream));
			Tokenizer tokenizer = new Tokenizer(reader);
			Parser parser = new Parser(tokenizer);
			nodeMap.put(uri, parser.parseNode(this));
			reader.close();
		}
		return nodeMap.get(uri);
	}
}

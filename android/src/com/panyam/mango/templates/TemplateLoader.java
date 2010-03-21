package com.panyam.mango.templates;

import java.io.*;
import java.net.*;

import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.ParserException;

/**
 * Loads templates given a URI.
 * 
 * @author Sri Panyam
 */
public interface TemplateLoader 
{
	/**
	 * Loads a template from a URI.
	 * 
	 * @param uri
	 * @return
	 */
	public Node loadTemplate(URI uri) throws IOException, ParserException;
}

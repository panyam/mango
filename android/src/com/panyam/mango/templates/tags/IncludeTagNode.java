package com.panyam.mango.templates.tags;

import java.io.*;
import java.net.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.utils.ParseUtils;
import com.panyam.mango.templates.variables.Variable;

public class IncludeTagNode extends TagNode 
{
	/**
	 * The template we are including.
	 */
	protected Variable sourceVar;
	protected String prevSource;	// previous value of the source in case it has changed then we do a reload
	protected TemplateLoader templateLoader;
	protected Node loadedNode;

	public IncludeTagNode() 
	{
		this(null);
	}

	public IncludeTagNode(String filename) 
	{
		setSource(filename);
	}
	
	/**
	 * Set the source as a variable that needs to be resolved at rendering time.
	 * 
	 * @param var
	 * @return
	 */
	public boolean setSource(Variable var)
	{
		sourceVar = var;
		prevSource = null;
		loadedNode = null;
		return true;
	}

	/**
	 * Set the source as a plain filename.
	 * @param filename
	 * @return
	 */
	public boolean setSource(String filename)
	{
		return setSource(new Variable(filename, true));
	}
	
    /**
     * Extracts an include node from the parser.
     *
     * The parser at this stage should have just read the "{{" and the "include"
     * tokens and will be pointing to the filename.
     * 
     * @param parser
     * @return
     * @throws ParserException
     */
    public boolean initWithParser(Parser parser, TemplateLoader loader) throws ParserException
    {
    	Token token = parser.expectTokenInList(TokenLists.IDENT_OR_STRING, true);
    	if (token.tokenType == TokenType.TOKEN_IDENTIFIER)
    	{
    		setSource(ParseUtils.parseVariable(parser));
    	}
    	else
    	{
    		parser.getToken();
    		setSource(token.tokenValue.toString());
    	}
        parser.expectToken(TokenType.TOKEN_CLOSE_TAG);
    	templateLoader = loader;
    	return true;
    }
	
	public boolean equalsTagNode(TagNode another)
	{
        if (!(another instanceof IncludeTagNode))
            return false;

        return sourceVar.equals(((IncludeTagNode)another).sourceVar);
	}

    /**
     * Renders by returning the matching child node if any.
     */
    public Node renderBitMore(Writer writer, TemplateContext context, NodeContext currContext) throws IOException
    {
    	if (loadedNode == null || !sourceVar.isQuoted)
    	{
    		String realSource = sourceVar.resolve(context, currContext).toString();
    		
    		// once resolved, only load the template again if the variable value has changed!
    		if (realSource != prevSource)
    		{
    			prevSource = realSource;
				try
				{
					URI uri = new URI(realSource);
					try {
						loadedNode = templateLoader.loadTemplate(uri);
					} catch (ParserException e) {
						e.printStackTrace();
					}
				}
				catch (URISyntaxException use)
				{
					use.printStackTrace();
					return null;
				}
    		}
    	}
    	return loadedNode;
    }
}

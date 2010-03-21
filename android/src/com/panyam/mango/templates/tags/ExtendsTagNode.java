package com.panyam.mango.templates.tags;

import java.io.*;
import java.net.*;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.utils.ParseUtils;
import com.panyam.mango.templates.variables.Variable;

/**
 * A tag that allows the inheritance and extension of another template.
 * 
 * How do exclude nodes work?
 * 
 * Essentially the source node is included and then the child block nodes 
 * are merged with the nodes in the source.  ie during a parse, we ignore 
 * all children of an exclude node that is not a block node.
 * 
 * Our exclude nodes are slightly from django's version.  In django,
 * exclude nodes can only appear at the top of a template file and no where
 * else.  This means a template only extends another template.
 * 
 * In mango, exclude is a bit more advanced without loss in peformance.  
 * We can do: 
 * 
 * {% extends another_template %}
 * {% block block1 %}
 *     Hello World
 * {% endblock %}
 * {% block block2 %}
 *     {% extends "template2" %}
 *         {% block b1 %}
 *         {% endblock %}
 *     {% endextends %}
 * {% endblock %}
 * {% endextends  %}
 * 
 * So here block1 is replaced by the new content and block2 is also replaced, but
 * allows you to an extension of template2 as the content.  This is equivalent 
 * to including another file that extends template2.
 * 
 * This is introduces one problem.  This makes templates dynamic and non cacheable.
 * For example consider the following snippet:
 *  
 *  {% for template in templates %}
 *       {% extends template %}
 *           {% block block1 %}
 *               Overwritten Content in Block 1
 *           {% endblock %}
 *       {% endextends %}
 *  {% endfor %}
 *  
 * templates = [ "template1", "template2", ]
 * And these are the 2 templates:
 * 
 * template1:
 * 
 * {% block block1 %}
 *     Template 1 Block 1
 * {% endblock %}
 * 
 * template2:
 * 
 * before block 1
 * {% block block1 %}
 *      block1 in template 2
 * {% endblock %}
 * after block 1
 * 
 * So the rendered output is clearly:
 * 
 * Overwritten Content in Block 1
 * before block 1
 * Overwritten Content in Block 1
 * after block 1
 * 
 * Normally with exclude blocks being limited to one per template 
 * (and at the top), this is a non-issue since all the templates 
 * and include files can be loaded at once.  As a result templates
 * need to only be loaded once.  We do not have this problem with
 * include nodes because only a variable resolution is required 
 * and not the reading of the entire template from file (and the 
 * template is cached anyway).
 * 
 * Problem with our templates is the block contents itself would change
 * depending on the variables we pass to templates.  So with the above 
 * snippet, the extends block within the loop will have to do a node
 * merging process each time.  Django avoids this by simply not having 
 * excludes beyond the first entry of a template.
 * 
 * How can this be made efficient?
 * 
 * Firstly a source variable resolution is required.  
 * Block merging process is only invoked if the variable value has changed
 * otherwise the node loaded by resolving the previous value is used. 
 * 
 * This still does not eliminate the need for repeated node merges.  
 * If templates was something like [ "template1", "template2", "template1" ]
 * then the excludes node will do merges on template1 twice.  One strategy
 * to avoid this could be caching.
 * 
 * How?  Maintain a list of merged results for different templates (if necessary).
 * So in the above example, a map would maintain the merged results for 
 * template1 and template2.  So the next encounter of template1 will simply
 * fetch from the cache.  
 * 
 * However this strategy means each exclude has to maintain its own cache
 * which is pretty wasteful.  Better to have a global cache that handles
 * all this.  This way, it can even do things like have a limited size 
 * cache that may remove merges that are too old or too infrequent.
 * 
 * @author Sri Panyam
 */
public class ExtendsTagNode extends TagNode 
{
	/**
	 * The template we are including.
	 */
	protected Variable sourceVar;
	protected String prevSource;	// previous value of the source in case it has changed then we do a reload
	protected TemplateLoader templateLoader;
	protected Node loadedNode;

	public ExtendsTagNode() 
	{
		this(null);
	}

	public ExtendsTagNode(String filename) 
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
        if (!(another instanceof ExtendsTagNode))
            return false;

        return sourceVar.equals(((ExtendsTagNode)another).sourceVar);
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

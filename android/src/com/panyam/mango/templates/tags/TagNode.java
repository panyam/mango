package com.panyam.mango.templates.tags;

import java.lang.reflect.*;
import java.util.*;
import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.variables.*;

/**
 * Parses a tag node.  This is a slightly tricky bit...
 *
 * With tag nodes we will have to transfer control to the tag parsers so
 * that they can read the contents of the the node as they wish and this
 * can include whether or not to parse until the corresponding end tag.
 */
public abstract class TagNode extends Node
{
    /**
     * Default constructor.
     */
    public TagNode()
    {
    }
   
    /**
     * Extracts the tag node from the parser.
     */
    public abstract boolean initWithParser(Parser parser, TemplateLoader loader) throws ParserException;

    /**
     * Creates a tag instance specific context.  For example this could be
     * a softened versions of the arguments passed in a for loop.
     * @return A tag instance specific context object.
     */
    public Object makeInstanceContext(ArrayList<Variable> arguments)
    {
        return null;
    }
    
    /**
     * Creates an invocation specific context for the tag.  eg for a "for
     * loop" node, this could be the loop counter or the state of the
     * iterator the loop is iterating.
     * @return An invocation specific context object for this tag.
     */
    public Object makeInvocationContext(ArrayList<Variable> arguments)
    {
        return null;
    }

    /**
     * Helper for handing an open-tag token and getting the right tag node
     * to handle the parsing.
     * @throws InvocationTargetException 
     * @throws ParserException 
     */
    @SuppressWarnings("unchecked")
	public static TagNode extractWithParser(Parser parser, TemplateLoader loader) throws InvocationTargetException, ParserException
    {
        Token token = parser.expectToken(TokenType.TOKEN_IDENTIFIER);
        
        Class<TagNode> nodeClass = (Class<TagNode>)TagLibrary.getSharedInstance().getObjectClass(token.tokenValue.toString());
        if (nodeClass == null)
        {
            parser.throwError("Invalid node type: <" + token.tokenValue.toString() + ">");
            return null;
        }
        TagNode newNode = null;
        try {
            Constructor<TagNode> constructor = nodeClass.getConstructor((Class[])null);
            constructor.setAccessible(true);
            Method initWithParserMethod = nodeClass.getMethod("initWithParser", Parser.class, TemplateLoader.class);
            initWithParserMethod.setAccessible(true);
            // TODO: Cache the constructor and method so that we do not have to search for it each time...
            newNode = constructor.newInstance();
            Object result = initWithParserMethod.invoke(newNode, parser, loader);
            if (!(result instanceof Boolean && ((Boolean)result).booleanValue()))
            	throw new Error("initWithParserMethod returned false");
        } catch (SecurityException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
        return newNode;
    }
    
    /**
     * Compares specifically with another tag node.
     * @param another
     * @return true if objects are equal.
     */
    public boolean equalsTagNode(TagNode another)
    {
        return false;
    }

    /**
     * Compares another object with this tag node.
     */
    public boolean equals(Object another)
    {
        if (another == null)
            return false;
        if (another == this)
            return true;
        
        // let child classes extend and fill this in
        if (another instanceof TagNode)
        {
        	TagNode anotherTagNode = (TagNode)another;
            return equalsTagNode(anotherTagNode);
        }
        return false;
    }
}

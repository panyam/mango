package com.panyam.mango.templates.tags;

import com.panyam.mango.templates.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.parser.*;

/**
 * A tag for doing for loops.
 */
public class CycleTagNode extends TagNode
{
    /**
     * Creates a CycleTagNode directly without parsing from the input.
     */
    public CycleTagNode(Object thingsWeNeed)
    {
        this(thingsWeNeed, null);
    }

    /**
     * Creates a CycleTagNode directly without parsing from the input.
     */
    public CycleTagNode(Object thingsWeNeed, Node child)
    {
    }

    /**
     * Extracts the tag node from the parser.
     */
    public boolean initWithParser(Parser parser, TemplateLoader loader) throws ParserException
    {
    	return false;
    }

    /**
     * Compares specifically with another tag node.
     * We can safely assume that here another is neither this nor null.
     * @param another
     * @return true if objects are equal.
     */
    public boolean equalsTagNode(TagNode another)
    {
        if (!(another instanceof CycleTagNode))
            return false;
        return true;
        // return CompareUtils.CompareIterables(childNodes, ((CycleTagNode)another).childNodes);
    }
}

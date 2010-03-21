package com.panyam.mango.templates.core.expressions;

import com.panyam.mango.templates.utils.*;

/**
 * Enables binary boolean expressions.
 * 
 * @author Sri Panyam
 */
public class BinaryExpression extends UnaryExpression
{
    protected Expression child2;

    public BinaryExpression(Operator bin_op, Expression l, Expression r)
    {
        super(bin_op, l);
        child2 = r;
    }

    public boolean equalsAnotherBinaryExpression(BinaryExpression bCond)
    {
        return CompareUtils.ObjectsEqual(child2, bCond.child2);
    }

    public boolean equalsAnotherUnaryExpression(UnaryExpression  uCond)
    {
        if (super.equalsAnotherUnaryExpression(uCond) &&
                uCond instanceof BinaryExpression)
        {
            BinaryExpression bCond = (BinaryExpression)uCond;
            return equalsAnotherBinaryExpression(bCond);
        }
        return false;
    }
}


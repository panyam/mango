package com.panyam.mango.templates.core.expressions;

import com.panyam.mango.templates.utils.*;

/**
 * Enables binary boolean expressions.
 * 
 * @author Sri Panyam
 */
public class UnaryExpression extends Expression
{
    protected Operator operator;
    protected Expression child1;

    public UnaryExpression(Operator unary_op, Expression ch)
    {
        operator =  unary_op;
        child1 = ch;
    }

    public boolean equalsAnotherUnaryExpression(UnaryExpression  uCond)
    {
        return operator == uCond.operator &&
                CompareUtils.ObjectsEqual(child1, uCond.child1);
    }
    
    public boolean equalsAnotherExpression(Expression another)
    {
        if (!(another instanceof UnaryExpression))
        {
            return false;
        }
        UnaryExpression uCond = (UnaryExpression)another;
        return equalsAnotherUnaryExpression(uCond);
    }
}


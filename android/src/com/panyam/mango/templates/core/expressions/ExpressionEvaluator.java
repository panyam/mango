package com.panyam.mango.templates.core.expressions;

import java.util.*;

import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.utils.*;

/**
 * Evaluates the value of an expression.
 * 
 * @author Sri Panyam
 */
public class ExpressionEvaluator 
{
	protected static ExpressionEvaluator SHARED_INSTANCE = null;
	public static ExpressionEvaluator getDefaultEvaluator()
	{
		if (SHARED_INSTANCE == null)
			SHARED_INSTANCE = new ExpressionEvaluator();
		return SHARED_INSTANCE;
	}
	
	/**
	 * Evaluates the value of an expression.
	 * 
	 * @param expr
	 * @param context
	 * @param topContext
	 * @return
	 */
	public Object evaluate(Expression expr, TemplateContext context, NodeContext topContext)
	{
		if (expr == null)
			return null;
		boolean negated = expr.isNegated();
		if (expr instanceof BinaryExpression)
		{
			BinaryExpression bexp = (BinaryExpression)expr;
			Object leftVal = evaluate(bexp.child1, context, topContext);
			if (bexp.operator == Operator.OP_AND && !CompareUtils.IsTrue(leftVal))
			{
				return !negated;
			}
			else if (bexp.operator == Operator.OP_OR && CompareUtils.IsTrue(leftVal))
			{
				return !negated;
			}
			Object rightVal = evaluate(bexp.child2, context, topContext);

			boolean result = false;
			switch (bexp.operator)
			{
			case OP_AND: result = CompareUtils.IsTrue(leftVal) && CompareUtils.IsTrue(rightVal); break;
			case OP_OR: result = CompareUtils.IsTrue(leftVal) || CompareUtils.IsTrue(rightVal); break;
			case OP_EQ: result = CompareUtils.ObjectsEqual(leftVal, rightVal); break;
			case OP_NE: result = !CompareUtils.ObjectsEqual(leftVal, rightVal); break;
			case OP_LE: result = CompareUtils.CompareObjects(leftVal, rightVal) <= 0; break;
			case OP_LT: result = CompareUtils.CompareObjects(leftVal, rightVal) < 0; break;
			case OP_GE: result = CompareUtils.CompareObjects(leftVal, rightVal) >= 0; break;
			case OP_GT: result = CompareUtils.CompareObjects(leftVal, rightVal) > 0; break;
			case OP_IN: {
				if (rightVal instanceof Collection<?>)
				{
					result = ((Collection<?>)rightVal).contains(leftVal);
				}
				else if (rightVal instanceof Map<?,?>)
				{
					result = ((Map<?,?>)rightVal).containsKey(leftVal);
				}
				else if (rightVal instanceof String && leftVal instanceof String)
				{
					result = ((String)rightVal).contains((String)leftVal);
				}
			}
			default: break;
			}
			return result == !negated; 
		}
		else if (expr instanceof VariableExpression)
		{
			Object value = ((VariableExpression)expr).variable.resolve(context, topContext);
			if (negated)
			{
				return !CompareUtils.IsTrue(value);
			}
			else
			{
				return value;
			}
		}
		return null;
	}
}

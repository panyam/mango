package com.panyam.mango.templates.test;

import java.io.*;

import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.core.*;
import com.panyam.mango.templates.core.expressions.*;
import com.panyam.mango.templates.variables.*;

import junit.framework.TestCase;

public class ExpressionTests extends TestCase
{
	class ProbedTokenizer extends Tokenizer
	{
		public ProbedTokenizer(BufferedReader reader) {
			super(reader);
			insideNode = Tokenizer.NodeType.NODETYPE_TAG;
		}
	}
	
	ProbedTokenizer tokenizer;
	Parser parser;
	TemplateContext context;
	ExpressionEvaluator evaluator;

	public ExpressionTests(String name) {
		super(name);
	}

	protected void setUp() throws Exception {
		super.setUp();
		context = new TemplateContext();
		evaluator = new ExpressionEvaluator();
	}

	protected void tearDown() throws Exception {
		super.tearDown();
	}

    /**
     * Sets up the tokenizer with an input string.
     */
    protected void setUpWithInputString(String input)
    {
	    tokenizer = new ProbedTokenizer(new BufferedReader(new StringReader(input)));
    	tokenizer.setCheckIdentifierOperators(true);
	    parser	= new Parser(tokenizer);
    }
    
    protected static Expression Negate(Expression input)
    {
    	input.negate();
    	return input;
    }
    
    protected void checkExpectedExpression(Expression expected)
    {
		try {
			Expression parsed = ExpressionParser.parseExpression(parser, 0);
	    	assertEquals(expected, parsed);
		} catch (ParserException e) {
			e.printStackTrace();
			fail("Got unexpected Parser Exception");
		}
    }
    
    protected VariableExpression makeVarCond(String ... varnames)
    {
    	Variable firstVar = null;
    	Variable lastVar = null;
    	for (int i = 0;i < varnames.length;i++)
    	{
    		Variable newVar = new Variable(varnames[i]);
    		if (firstVar == null)
    		{
    			firstVar = lastVar = newVar;
    		}
    		else 
    		{
    			Variable nextVar = lastVar.setNextVariable(varnames[i], false);
    			if (nextVar != null)
    				lastVar = nextVar;
    		}
    	}
    	return new VariableExpression(firstVar);
    }
    
    protected BinaryExpression binCond(Operator op, Expression lhs, Expression rhs)
    {
    	return new BinaryExpression(op, lhs, rhs);
    }
    
    protected UnaryExpression unaryCond(Operator op, Expression lhs)
    {
    	return new UnaryExpression(op, lhs);
    }

    public void testExpressionCreate()
    {
    	setUpWithInputString("");
    	Expression expected = null;
    	checkExpectedExpression(expected);
    }

    public void testSingleVariable()
    {
    	setUpWithInputString("xx");
    	Expression expected = makeVarCond("xx");
    	checkExpectedExpression(expected);
    }

    public void testAEqualsB()
    {
    	setUpWithInputString("a == b");
    	Expression expected = binCond(Operator.OP_EQ, makeVarCond("a"), makeVarCond("b"));
    	checkExpectedExpression(expected);
    }

    public void testBigVariableEquals()
    {
    	setUpWithInputString("a.b.c == b");
    	Expression expected = binCond(Operator.OP_EQ, makeVarCond("a", "b", "c"), makeVarCond("b"));
    	checkExpectedExpression(expected);
    }

    public void testAndWithEquals()
    {
    	setUpWithInputString("a and b == c");
    	tokenizer.setCheckIdentifierOperators(true);
    	Expression expected = binCond(Operator.OP_AND, 
    								makeVarCond("a"), 
    								binCond(Operator.OP_EQ, makeVarCond("b"), makeVarCond("c")));
    	checkExpectedExpression(expected);
    }

    public void testTwoLevels()
    {
    	setUpWithInputString("a == b and b == c");
    	tokenizer.setCheckIdentifierOperators(true);
    	Expression expected = binCond(Operator.OP_AND, 
    								binCond(Operator.OP_EQ, makeVarCond("a"), makeVarCond("b")), 
    								binCond(Operator.OP_EQ, makeVarCond("b"), makeVarCond("c")));
    	checkExpectedExpression(expected);
    }

    public void testThreeLevels1()
    {
    	setUpWithInputString("x == y or a == b and b == c");
    	tokenizer.setCheckIdentifierOperators(true);
    	Expression expected = binCond(Operator.OP_OR, 
    								binCond(Operator.OP_EQ, makeVarCond("x"), makeVarCond("y")), 
    								binCond(Operator.OP_AND, 
    	    								binCond(Operator.OP_EQ, makeVarCond("a"), makeVarCond("b")), 
    	    								binCond(Operator.OP_EQ, makeVarCond("b"), makeVarCond("c"))));

    	checkExpectedExpression(expected);
    }

    public void testThreeLevels2()
    {
    	setUpWithInputString("x == y and a == b or b != c");
    	tokenizer.setCheckIdentifierOperators(true);
    	Expression expected = binCond(Operator.OP_OR, 
									binCond(Operator.OP_AND, 
											binCond(Operator.OP_EQ, makeVarCond("x"), makeVarCond("y")), 
											binCond(Operator.OP_EQ, makeVarCond("a"), makeVarCond("b"))),
    								binCond(Operator.OP_NE, makeVarCond("b"), makeVarCond("c")) 
    	    								);

    	checkExpectedExpression(expected);
    }
    
    public void testParens()
    {
    	setUpWithInputString("(b and c)");
    	tokenizer.setCheckIdentifierOperators(true);
    	Expression expected = binCond(Operator.OP_AND, makeVarCond("b"), makeVarCond("c"));
    	checkExpectedExpression(expected);
    }
    
    public void testDeepParams()
    {
    	setUpWithInputString("b and (c or d)");
    	tokenizer.setCheckIdentifierOperators(true);
    	Expression expected = binCond(Operator.OP_AND, makeVarCond("b"), 
    							binCond(Operator.OP_OR, makeVarCond("c"), makeVarCond("d")));
    	checkExpectedExpression(expected);
    }
    
    public void testDeepParams2()
    {
    	setUpWithInputString("b in (c and (d or e))");
    	tokenizer.setCheckIdentifierOperators(true);
    	Expression expected = binCond(Operator.OP_IN, 
    							makeVarCond("b"), 
    							binCond(Operator.OP_AND, 
    								makeVarCond("c"),
    								binCond(Operator.OP_OR, makeVarCond("d"), makeVarCond("e"))));
    	checkExpectedExpression(expected);
    }
    
    public void testSimpleNot()
    {
    	setUpWithInputString("not b");
    	Expression expected = Negate(makeVarCond("b"));
    	checkExpectedExpression(expected);
    }

    public void testAndWithNot()
    {
    	setUpWithInputString("a or not b and c");
    	Expression expected = binCond(Operator.OP_OR, 
								makeVarCond("a"),
								binCond(Operator.OP_AND,
									Negate(makeVarCond("b")),
									makeVarCond("c")));

    	checkExpectedExpression(expected);
    }

    public void testAndWithNot2()
    {
    	setUpWithInputString("a or b and not c");
    	Expression expected = binCond(Operator.OP_OR, 
								makeVarCond("a"),
								binCond(Operator.OP_AND,
										makeVarCond("b"),
										Negate(makeVarCond("c"))));

    	checkExpectedExpression(expected);
    }

    public void testNotWithBinOps()
    {
    	setUpWithInputString("a or not b == c");
    	Expression expected = binCond(Operator.OP_OR, 
								makeVarCond("a"),
								Negate(binCond(Operator.OP_EQ, makeVarCond("b"), makeVarCond("c"))));

    	checkExpectedExpression(expected);
    }
    
    /////////  Now for values
    protected void checkExpressionValue(Object expectedValue)
    {
		try {
			Expression parsed = ExpressionParser.parseExpression(parser, 0);
			Object evaluatedValue = evaluator.evaluate(parsed, context, null);
	    	assertEquals(expectedValue, evaluatedValue);
		} catch (ParserException e) {
			e.printStackTrace();
			fail("Got unexpected Parser Exception");
		}
    }
    
    public void testVariableValue()
    {
    	context.setValue("a", 666);
    	setUpWithInputString("a");
    	checkExpressionValue(666);
    }
    
    public void testSimpleLTOperator()
    {
    	context.setValue("a", 666);
    	setUpWithInputString("3 < 2");
    	checkExpressionValue(false);
    }
    
    public void testSimpleEQOperator()
    {
    	context.setValue("a", 666);
    	setUpWithInputString("a == 666");
    	checkExpressionValue(true);
    }
    
    public void testVariableEQOperator()
    {
    	context.setValue("a", 666);
    	context.setValue("b", 667);
    	context.setValue("c", 666);
    	setUpWithInputString("a == b");
    	checkExpressionValue(false);
    	setUpWithInputString("a == c");
    	checkExpressionValue(true);
    }
    
    public void testSingleValueNegation()
    {
    	context.setValue("a", true);
    	context.setValue("b", false);
    	setUpWithInputString("not a");
    	checkExpressionValue(false);
    	setUpWithInputString("not b");
    	checkExpressionValue(true);
    }
    
    public void testBinExpNegation()
    {
    	context.setValue("a", 3);
    	context.setValue("b", 4);
    	setUpWithInputString("not (a == b)");
    	checkExpressionValue(true);
    }
    
    public void testAndExp()
    {
    	context.setValue("a", 3);
    	context.setValue("b", 4);
    	context.setValue("c", 5);
    	setUpWithInputString("(a < b) and (b <= c)");
    	checkExpressionValue(true);
    }
    
    public void testAndExp2()
    {
    	context.setValue("a", 3);
    	context.setValue("b", 4);
    	context.setValue("c", 5);
    	setUpWithInputString("(a < b) and (b <= c) and null");
    	checkExpressionValue(false);
    }
    
    public void testOrExpression()
    {
    	context.setValue("a", 3);
    	context.setValue("b", 4);
    	context.setValue("c", 5);
    	setUpWithInputString("(a > b) or false or (b <= c)");
    	checkExpressionValue(true);
    }
    
    public void testInExpressionWithArrayList()
    {
    	context.setValue("a", Utils.makeArrayList(1, 2, 3, 4, 5));
    	context.setValue("b", 4);
    	setUpWithInputString("b in a");
    	checkExpressionValue(true);
    }
    
    public void testInExpressionWithMap()
    {
    	context.setValue("a", Utils.makeHashMap("a", 1, "b", 2, "c", 3));
    	context.setValue("b", "c");
    	setUpWithInputString("b in a");
    	checkExpressionValue(true);
    }
    
    public void testStringEqualsInt()
    {
    	context.setValue("a", 1);
    	context.setValue("b", "1");
    	setUpWithInputString("b == a");
    	checkExpressionValue(false);
    }
}

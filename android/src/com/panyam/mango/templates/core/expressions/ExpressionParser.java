package com.panyam.mango.templates.core.expressions;

import com.panyam.mango.templates.parser.*;
import com.panyam.mango.templates.utils.*;

public class ExpressionParser 
{
	protected static Operator OPERATORS[] = null;
	protected static int PRECEDENCES[] = null;
	
    /**
     * Expected token list for identifier or string only.
     */
    public static final TokenType NOT_OR_IDENT[] = new TokenType[] {
            TokenType.TOKEN_NOT, 
            TokenType.TOKEN_IDENTIFIER,
    };
    
    /**
     * Tokens allowed in the nullDenotation
     */
    public static final TokenType NULL_DENOT_LIST[] = new TokenType[] {
            TokenType.TOKEN_NOT, 
            TokenType.TOKEN_IDENTIFIER,
            TokenType.TOKEN_OPEN_PAREN,
            TokenType.TOKEN_EOF
    };

    /**
     * Tokens allowed in the nullDenotation
     */
    public static final TokenType LEFT_DENOT_LIST[] = new TokenType[] {
    		TokenType.TOKEN_OR,
       		TokenType.TOKEN_AND,
      		TokenType.TOKEN_LT,
       		TokenType.TOKEN_LE,
       		TokenType.TOKEN_LT,
       		TokenType.TOKEN_LE,
     		TokenType.TOKEN_IN,
    };

    ////////////   Some condition stuff
    /**
     * Parse a condition expression.
     * 
     * Expression expressions are:
     * 
     * cond_exp := or_expression
     * 
     * or_expression := and_expression ( "or" and_expression ) *
     * 
     * and_expression := "not" in_expression | in_expression | bin_exp
     * 
     * in_expression := variable "in" variable 
     * 
     * bin_exp := primary_exp ( bin_op primary_exp ) *
     * 
     * primary_exp := variable | "(" cond_exp ")"
     * 
     * This grammar is not very LL (or easily LL anyway, I think).  But doing a LR 
     * parser for this is extremely messy and not to mention could be inefficient.  
     * For example to reach the "variable" it has to decend 5 times" to reach it:
     * 
     *  cond_exp -> or_exp -> and_exp -> bin_exp -> primary_exp -> variable
     * 
     * So we will use a topdown operator precedence parser which is simpler 
     * and efficient for this grammar.
     */
    public static Expression parseExpression(Parser parser) throws ParserException
    {
    	return parseExpression(parser, 0);
    }

    public static Expression parseExpression(Parser parser, int minPrec) throws ParserException
    {
    	/*
    	 * we are doing top-down operator precedence parsing.
    	 * For each token, we associate a precedence with it (using the getPrecedence method).
    	 */
    	Expression left = nullDenotation(parser);
    	if (left == null) return null;
    	Token token = parser.peekToken();
    	while (token != null && token.tokenType != TokenType.TOKEN_ERROR && minPrec < getPrecedence(token.tokenType))
    	{
    		token = parser.getToken();	// consume the token.
    		left = leftDenotation(parser, token.tokenType, left);
        	token = parser.peekToken();
    	}

    	return (Expression)left;
    }
    
    /**
     * Prefix handler
     * 
     * @param parser
     * @return
     * @throws ParserException
     */
    protected static Expression nullDenotation(Parser parser) throws ParserException
    {
    	Token token = parser.peekToken();
    	Expression out = null;
    	if (token == null || token.tokenType == TokenType.TOKEN_ERROR)
    		return null;
    	
    	if (token.tokenType == TokenType.TOKEN_IDENTIFIER)
    	{
    		out = new VariableExpression(ParseUtils.parseVariable(parser));
    	}
    	else if (token.tokenType == TokenType.TOKEN_OPEN_PAREN)
    	{
    		parser.getToken();	// consume the "("
    		out = parseExpression(parser, 0);
    		parser.expectToken(TokenType.TOKEN_CLOSE_PAREN);
    	}
    	else if (token.tokenType == TokenType.TOKEN_OPEN_PAREN)
    	{
    		parser.getToken();	// consume the "("
    		out = parseExpression(parser, 0);
    		parser.expectToken(TokenType.TOKEN_CLOSE_PAREN);
    	}
    	else if (token.tokenType == TokenType.TOKEN_NOT)
    	{
    		parser.getToken();	// consume the "!"
    		out = parseExpression(parser, getPrecedence(token.tokenType));
    		out.negate();
    	}
    	else
    	{
    		parser.throwError("Internal Error.  Should have been handled by expectToken");
    	}
    	return out;
    }

    /**
     * Infix handler
     * 
     * @param parser
     * @param tokenType
     * @param left
     * @return
     * @throws ParserException
     */
    protected static Expression leftDenotation(Parser parser, TokenType tokenType, Expression left) throws ParserException
    {
    	if (tokenType == TokenType.TOKEN_OR ||
    		tokenType == TokenType.TOKEN_AND ||
    		tokenType == TokenType.TOKEN_LT ||
    		tokenType == TokenType.TOKEN_LE ||
    		tokenType == TokenType.TOKEN_GT ||
    		tokenType == TokenType.TOKEN_GE ||
    		tokenType == TokenType.TOKEN_EQ ||
    		tokenType == TokenType.TOKEN_NE ||
    		tokenType == TokenType.TOKEN_IN)
    	{
    		int precedence = getPrecedence(tokenType);
    		Expression right = parseExpression(parser, precedence);
    		return new BinaryExpression(getOperator(tokenType), left, right);
    	}

    	return null;
    }
    
    protected static Expression NegatedExpression(Expression input)
    {
    	input.negate();
    	return input;
    }

    /**
     * Get the precedence of an operator.
     * 
     * @param operator
     * @return
     */
    public static int getPrecedence(TokenType operator)
    {
    	if (PRECEDENCES == null)
    	{
    		PRECEDENCES = new int[TokenType.TOKEN_LAST.ordinal() + 1];
    		for (int i = 0;i < TokenType.TOKEN_LAST.ordinal();i++)
    		{
    			PRECEDENCES[i] = 0;
    		}
    		PRECEDENCES[TokenType.TOKEN_OR.ordinal()] = 10;
    		PRECEDENCES[TokenType.TOKEN_AND.ordinal()] = 20;
    		PRECEDENCES[TokenType.TOKEN_NOT.ordinal()] = 30;
    		PRECEDENCES[TokenType.TOKEN_IN.ordinal()] = 40;
    		PRECEDENCES[TokenType.TOKEN_LT.ordinal()] = 50;
    		PRECEDENCES[TokenType.TOKEN_LE.ordinal()] = 50;
    		PRECEDENCES[TokenType.TOKEN_GT.ordinal()] = 50;
    		PRECEDENCES[TokenType.TOKEN_GE.ordinal()] = 50;
    		PRECEDENCES[TokenType.TOKEN_EQ.ordinal()] = 50;
    		PRECEDENCES[TokenType.TOKEN_NE.ordinal()] = 50;
    	}
    	return PRECEDENCES[operator.ordinal()];
    }

    /**
     * Get the precedence of an operator.
     * 
     * @param operator
     * @return
     */
    public static Operator getOperator(TokenType operator)
    {
    	if (OPERATORS == null)
    	{
    		OPERATORS = new Operator[TokenType.TOKEN_LAST.ordinal() + 1];
    		for (int i = 0;i < TokenType.TOKEN_LAST.ordinal();i++)
    		{
    			OPERATORS[i] = Operator.OP_NONE;
    		}
    		OPERATORS[TokenType.TOKEN_OR.ordinal()] = Operator.OP_OR;
    		OPERATORS[TokenType.TOKEN_AND.ordinal()] = Operator.OP_AND;
    		OPERATORS[TokenType.TOKEN_NOT.ordinal()] = Operator.OP_NOT;
    		OPERATORS[TokenType.TOKEN_IN.ordinal()] = Operator.OP_IN;
    		OPERATORS[TokenType.TOKEN_LT.ordinal()] = Operator.OP_LT;
    		OPERATORS[TokenType.TOKEN_LE.ordinal()] = Operator.OP_LE;
    		OPERATORS[TokenType.TOKEN_GT.ordinal()] = Operator.OP_GT;
    		OPERATORS[TokenType.TOKEN_GE.ordinal()] = Operator.OP_GE;
    		OPERATORS[TokenType.TOKEN_EQ.ordinal()] = Operator.OP_EQ;
    		OPERATORS[TokenType.TOKEN_NE.ordinal()] = Operator.OP_NE;
    	}
    	return OPERATORS[operator.ordinal()];
    }
}

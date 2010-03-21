/**
 * 
 */
package com.panyam.mango.templates.parser;

/**
 * @author root
 *
 */
public class ParserException extends Exception 
{
	/**
	 * Generated UID. 
	 */
	private static final long serialVersionUID = -5968656185067494091L;

	/**
	 * Code of the parser error.
	 */
	protected int errorCode;
	
	/**
	 * Creates a parser exception
	 */
	public ParserException(int code, String detailMessage) {
		super(detailMessage);
		errorCode = code;
	}

	/**
	 * @param detailMessage
	 */
	public ParserException(String detailMessage) 
	{
		this(-1, detailMessage);
	}

	/**
	 * @param throwable
	 */
	public ParserException(Throwable throwable) {
		super(throwable);
		errorCode = -1;
	}

	/**
	 * @param detailMessage
	 * @param throwable
	 */
	public ParserException(String detailMessage, Throwable throwable) 
	{
		super(detailMessage, throwable);
		errorCode = -1;
	}
	
	public String toString()
	{
		return ("Error (" + errorCode + "): " + getMessage());
	}
	
	public int getErrorCode()
	{
		return errorCode;
	}
}

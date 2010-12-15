package com.panyam.mango.templates.utils;

import java.util.*;

public final class CompareUtils 
{
	public static boolean ObjectsEqual(Object obj1, Object obj2)
	{
		if (obj1 == obj2)
		{
			return true;
		}
		else if (obj2 == null)
		{
			return false;
		}
		else
		{
			return obj1.equals(obj2);
		}
	}

	/**
	 * Compares two iterable objects.
	 * @param iter1
	 * @param iter2
	 * @return
	 */
	public static boolean IterablesEqual(Iterable<?> iterable1, Iterable<?> iterable2)
	{
		if (iterable1 == iterable2)
			return true;
		
		Iterator<?> iter1 = iterable1.iterator();
		Iterator<?> iter2 = iterable2.iterator();
		
		if (iter1 == iter2)
			return true;
		
		while (iter1.hasNext())
		{
			if (!iter2.hasNext())
			{
				return false;
			}
			else
			{
				if (!iter1.next().equals(iter2.next()))
				{
					return false;
				}
			}
		}
		
		return !iter2.hasNext();
	}
	
	/**
	 * Tells if an object evaluates to true.
	 * 
	 * @param value
	 * @return
	 */
	public static boolean IsTrue(Object value)
	{
		if (value == null)
			return false;
		if (value instanceof Boolean)
			return ((Boolean)value).booleanValue();
		if (value instanceof Integer)
			return ((Integer)value).intValue() != 0;
		if (value instanceof Long)
			return ((Long)value).longValue() != 0;
		if (value instanceof Double)
			return ((Double)value).doubleValue() != 0;
		if (value instanceof String)
			return ((String)value).length() > 0;
		if (value instanceof Collection<?>)
			return !((Collection<?>)value).isEmpty();
		return false;
	}
	
	public static int CompareObjects(Object obj1, Object obj2)
	{
		if (obj1 == obj2)
		{
			return 0;
		}
		else if (obj2 == null)
		{
			return 1;
		}
		else if (obj1 == null)
		{
			return -1;
		}
		else
		{
			if (obj1 instanceof Comparable<?>)
			{
				return ((Comparable)obj1).compareTo(obj2);
			}
			else if (obj1 instanceof Collection<?>)
			{
				if (obj2 instanceof Collection<?>)
				{
					return ((Collection<?>)obj1).size() - ((Collection<?>)obj2).size();
				}
				else
				{
					// collections are bigger than all non-collections
					return 1;
				}
			}
		}
		// unknown types
		throw new Error("Comparing unknown types");
	}
}

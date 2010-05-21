
#ifndef __MANGO_VARIABLE_ITERATOR__
#define __MANGO_VARIABLE_ITERATOR__

#include "mfwddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MangoVarIterator
{
};

#if 0
public class VarIterator implements Iterator<Object> 
{
	protected Object		sourceValue;
	protected Iterator<?> 	iterator;
	protected Map <?,?>		sourceMap;
	protected Method 		hasNextMethod;
	protected Method 		nextMethod;
	
	public VarIterator(Object source)
	{
		setSource(source);
	}

	/**
	 * Sets the source for the iterator.
	 * @param source
	 */
	public void setSource(Object source)
	{
		sourceValue = source;
		iterator = null;
		sourceMap = null;
		hasNextMethod = null;
		nextMethod = null;
		if (source instanceof Iterable<?>)
		{
			iterator = ((Iterable<?>)source).iterator();
		}
		else if (source instanceof Map<?,?>)
		{
			sourceMap = ((Map<?,?>)source);
			iterator = sourceMap.keySet().iterator();
		}
		else
		{
			// *REALLY* try to avoid this if you can!!!
			Class<?> sourceClass = source.getClass();
			try {
				hasNextMethod = sourceClass.getMethod("hasNext", (Class[])null);
				hasNextMethod.setAccessible(true);
				nextMethod = sourceClass.getMethod("next", (Class[])null);
				nextMethod.setAccessible(true);
			} catch (SecurityException e) {
				e.printStackTrace();
			} catch (NoSuchMethodException e) {
				e.printStackTrace();
			}
		}
	}

	public boolean hasNext() 
	{
		if (iterator != null)
		{
			return iterator.hasNext();
		}
		else if (hasNextMethod != null)
		{
			try {
				Object result = hasNextMethod.invoke(sourceValue, (Object)null);
				return result != null && result instanceof Boolean && ((Boolean)result).booleanValue();
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				e.printStackTrace();
			}
		}
		return false;
	}

	public Object next() 
	{
		if (sourceMap != null)
		{
			return sourceMap.get(iterator.next());
		}
		else if (iterator != null)
		{
			return iterator.next();
		}
		else if (nextMethod != null)
		{
			try {
				nextMethod.invoke(sourceValue, (Object)null);
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			} catch (InvocationTargetException e) {
				e.printStackTrace();
			}
		}
		return false;
	}

	public int unpackValues(int numValues, List<Object> itemValues)
	{
		if (!hasNext())
			return 0;
		
		Object obj = next();
		if (sourceMap != null)
		{
			// obj is a key so value must be indexed into the sourceMap
			Object value = sourceMap.get(obj);
			itemValues.set(0, obj);
			itemValues.set(1, value);
			return 2;
		}
		else if (obj instanceof Iterable<?>)
		{
			Iterator<?> iter = ((Iterable<?>)obj).iterator();
			int outCount = 0;
			for (;outCount < numValues && iter.hasNext();outCount++)
			{
				itemValues.set(outCount, iter.next());
			}
			return outCount;
		}
		else
		{
			itemValues.set(0, obj);
			return 1;
		}
	}

	public void remove() 
	{
	}
}

#endif

#ifdef __cplusplus
}
#endif


#endif

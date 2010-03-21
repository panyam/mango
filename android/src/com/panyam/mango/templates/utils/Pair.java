package com.panyam.mango.templates.utils;

/**
 * A generic pair object.
 * 
 * @author Sri Panyam
 *
 * @param <A>    Type of the first object.
 * @param <B>    Type of the second object.
 */
public class Pair<A, B> 
{
    public A first;
    public B second;
    
    public Pair(A a, B b)
    {
        first = a;
        second = b;
    }
}

package com.panyam.mango.templates.utils;

public final class VarUtils 
{
    /**
     * Tells if an input string is an integer.
     * @param input
     * @return
     */
    public static boolean isInteger(String input)
    {
        try
        {
            Integer.parseInt(input);
            return true;
        }
        catch (NumberFormatException nfe)
        {
            return false;
        }
    }

    
    /**
     * Tells if an input string is an integer.
     * @param input
     * @return
     */
    public static boolean isFloat(String input)
    {
        try
        {
            Float.parseFloat(input);
            return true;
        }
        catch (NumberFormatException nfe)
        {
            return false;
        }
    }
}

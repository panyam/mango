
#include "CompareUtils.h"

/**
 * Compares two arrays for equality by comparing the contents of each array.
 * 
 * This does not handle the case if there are loops with contents of one more 
 * both of the arrays pointing somewhere back/higher up in the hierarchy.
 * 
 * @param array1    First array
 * @param array2    Second    array
 * @return true if arrays and their contents are the same, false otherwise.
 */
BOOL compareArrays(NSArray *array1, NSArray *array2)
{
    if (array1 != array2)
    {
        if (array1 == nil || array2 == nil || [array1 count] != [array2 count])
        {
            return NO;
        }
        
        // otherwise compare the array contents
        // TODO: How to handle cycles?
        for (int i = 0, count = [array1 count];i < count;i++)
        {
            if (![[array1 objectAtIndex:i] isEqual:[array2 objectAtIndex:i]])
            {
                return NO;
            }
        }
    }
    return YES;
}

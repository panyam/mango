
#ifndef __MANGO_TABLE_H__
#define __MANGO_TABLE_H__

/**
 * General associate container
 */
struct MangoTable
{
    void *entries;

    /**
     * Returns the number of entries.
     */
    int (*sizeFunc)(*entries);

    /**
     * Frees the table entries.
     */
    void (*freeFrunc)(void *entries);

    /**
     * Gets a value by key.
     */
    void *(*getFunc)(void *key);

    /**
     * Tells if a value exists.
     */
    BOOL (*hasFunc)(void *key);

    /**
     * Puts a value by key, replacing and returning the old value if any.
     */
    void *(*putFunc)(void *key, void *value);
};

#endif



#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

class StringTableTestFixture
{
protected:
    MangoStringTable *mstable;

public:
    StringTableTestFixture()
    {
        mstable = mango_string_table_new();
    }

    virtual ~StringTableTestFixture()
    {
        if (mstable != NULL)
            mango_string_table_free(mstable);
    }
};

/**
 * Tests the creation of a string table.
 */
TEST_FIXTURE(StringTableTestFixture, TestStringTableCreate)
{
    CHECK(mstable != NULL);
}

/**
 * Test finding of a non-existent string.
 */
TEST_FIXTURE(StringTableTestFixture, TestStringTableFindString)
{
    int id = mango_string_table_find(mstable, "Hello World", -1, false, 0);
    CHECK(id == -1);
}

/**
 * Test finding of a string by adding it.
 */
TEST_FIXTURE(StringTableTestFixture, TestStringTableFindStringByCreating)
{
    int id = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    CHECK(id != -1);
}

/**
 * Test that two strings that are equal have the same ID.
 */
TEST_FIXTURE(StringTableTestFixture, TestStringTableEqualStringsHaveSameId)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    int id2 = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    CHECK_EQUAL(id1, id2);
}

/**
 * Test refcount incrementing works
 */
TEST_FIXTURE(StringTableTestFixture, TestStringTableIncRef)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, 1);
    const MangoStringData *msdata = mango_string_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 2);
}


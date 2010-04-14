
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
TEST_FIXTURE(StringTableTestFixture, TestCreate)
{
    CHECK(mstable != NULL);
}

/**
 * Test finding of a non-existent string.
 */
TEST_FIXTURE(StringTableTestFixture, TestFindString)
{
    int id = mango_string_table_find(mstable, "Hello World", -1, false, 0);
    CHECK(id == -1);
}

/**
 * Test finding of a string by adding it.
 */
TEST_FIXTURE(StringTableTestFixture, TestFindStringByCreating)
{
    int id = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    CHECK(id != -1);
}

/**
 * Test that two strings that are equal have the same ID.
 */
TEST_FIXTURE(StringTableTestFixture, TestEqualStringsHaveSameId)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    int id2 = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    CHECK_EQUAL(id1, id2);
}

/**
 * Test creation of an entry with an initial reference count.
 */
TEST_FIXTURE(StringTableTestFixture, TestCreateWithRefCount)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, 100);
    const MangoStringData *msdata = mango_string_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 100);
}

/**
 * Test creation of an entry with an invalid reference count - refcount
 * should be set to 1.
 */
TEST_FIXTURE(StringTableTestFixture, TestCreateWithInvalidRefCount)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, -100);
    const MangoStringData *msdata = mango_string_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
}

/**
 * Test refcount incrementing works
 */
TEST_FIXTURE(StringTableTestFixture, TestIncRef)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, 1);
    const MangoStringData *msdata = mango_string_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
}

/**
 * Test refcount decrementing works
 */
TEST_FIXTURE(StringTableTestFixture, TestDecRef)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, -1);
    const MangoStringData *msdata = mango_string_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
    mango_string_table_decref(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 0);
}

/**
 * Test refcount decrementing doesnt decrement less than 0
 */
TEST_FIXTURE(StringTableTestFixture, TestDecRefLimitAtZero)
{
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, -1);
    const MangoStringData *msdata = mango_string_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
    mango_string_table_decref(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 0);
}

/**
 * Test that creating two mango strings of the same value increments
 * reference counts
 */
TEST_FIXTURE(StringTableTestFixture, TestIncRefOnStringCopy)
{
    MangoString *mstr1 = mango_string_new("Hello World", -1, mstable);
    MangoString *mstr2 = mango_string_new("Hello World", -1, mstable);
    int id1 = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    int id2 = mango_string_table_find(mstable, "Hello World", -1, true, 0);
    CHECK_EQUAL(id1, id2);
    CHECK_EQUAL(mstr1->internId, mstr2->internId);
    CHECK_EQUAL(mstr1->mstable, mstr2->mstable);

    const MangoStringData *msdata1 = mango_string_table_get(mstable, id1);
    const MangoStringData *msdata2 = mango_string_table_get(mstable, id2);
    CHECK_EQUAL(msdata1, msdata2);
    CHECK_EQUAL(2, msdata1->refCount);
}

/**
 * Test that creating two mango strings of the same value increments
 * reference counts
 */
TEST_FIXTURE(StringTableTestFixture, TestIncRefOnStringFree)
{
    MangoString *mstr1 = mango_string_new("Hello World", -1, mstable);
    const MangoStringData *msdata = mango_string_table_get(mstable, mstr1->internId);
    CHECK_EQUAL(msdata->refCount, 2);
    mango_string_free(mstr1);
    CHECK_EQUAL(msdata->refCount, 1);
}


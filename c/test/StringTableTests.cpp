
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

class RCStringTableTestFixture
{
protected:
    MangoRCStringTable *mstable;
    MangoStringFactory *string_factory;

public:
    RCStringTableTestFixture() :
        string_factory(mango_rcstringfactory_new())
    {
        // mstable = mango_rcstring_table_new();
        mstable = mango_rcstring_table_default();
    }

    virtual ~RCStringTableTestFixture()
    {
        if (mstable != NULL)
        {
            if (mstable != mango_rcstring_table_default())
            {
                mango_rcstring_table_free(mstable);
            }
            else
            {
                mango_rcstring_table_clear(mstable);
            }
        }

        if (string_factory != NULL)
        {
            mango_stringfactory_free(string_factory);
            string_factory = NULL;
        }
    }
};

/**
 * Tests the creation of a string table.
 */
TEST_FIXTURE(RCStringTableTestFixture, TestCreate)
{
    // CHECK(mstable != NULL);
}

/**
 * Test finding of a non-existent string.
 */
TEST_FIXTURE(RCStringTableTestFixture, TestFindString)
{
    int id = mango_rcstring_table_find(mstable, "Hello World", -1, false, 0);
    CHECK(id == -1);
}

/**
 * Test finding of a string by adding it.
 */
TEST_FIXTURE(RCStringTableTestFixture, TestFindStringByCreating)
{
    int id = mango_rcstring_table_find(mstable, "Hello World", -1, true, 0);
    CHECK(id != -1);
}

/**
 * Test that two strings that are equal have the same ID.
 */
TEST_FIXTURE(RCStringTableTestFixture, TestEqualStringsHaveSameId)
{
    int id1 = mango_rcstring_table_find(mstable, "Hello World", -1, true, 0);
    int id2 = mango_rcstring_table_find(mstable, "Hello World", -1, true, 0);
    CHECK_EQUAL(id1, id2);
}

/**
 * Test creation of an entry with an initial reference count.
 */
TEST_FIXTURE(RCStringTableTestFixture, TestCreateWithRefCount)
{
    int id1 = mango_rcstring_table_find(mstable, "Hello World", -1, true, 100);
    const MangoRCStringData *msdata = mango_rcstring_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 100);
}

/**
 * Test creation of an entry with an invalid reference count - refcount
 * should be set to 1.
 */
TEST_FIXTURE(RCStringTableTestFixture, TestCreateWithInvalidRefCount)
{
    int id1 = mango_rcstring_table_find(mstable, "Hello World", -1, true, -100);
    const MangoRCStringData *msdata = mango_rcstring_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
}

/**
 * Test refcount incrementing works
 */
TEST_FIXTURE(RCStringTableTestFixture, TestIncRef)
{
    int id1 = mango_rcstring_table_find(mstable, "Hello World", -1, true, 1);
    const MangoRCStringData *msdata = mango_rcstring_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
}

/**
 * Test refcount decrementing works
 */
TEST_FIXTURE(RCStringTableTestFixture, TestDecRef)
{
    int id1 = mango_rcstring_table_find(mstable, "Hello World", -1, true, -1);
    const MangoRCStringData *msdata = mango_rcstring_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
    mango_rcstring_table_decref(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 0);
}

/**
 * Test refcount decrementing doesnt decrement less than 0
 */
TEST_FIXTURE(RCStringTableTestFixture, TestDecRefLimitAtZero)
{
    int id1 = mango_rcstring_table_find(mstable, "Hello World", -1, true, -1);
    const MangoRCStringData *msdata = mango_rcstring_table_get(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 1);
    mango_rcstring_table_decref(mstable, id1);
    CHECK_EQUAL(msdata->refCount, 0);
}

/**
 * Test that creating two mango strings of the same value increments
 * reference counts
 */
TEST_FIXTURE(RCStringTableTestFixture, TestIncRefOnStringCopy)
{
    MangoRCStringTable *mstable = (MangoRCStringTable *)string_factory->data;
    MangoString *mstr1 = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    MangoString *mstr2 = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    MangoRCString *rcstr1 = (MangoRCString *)mstr1->data;
    MangoRCString *rcstr2 = (MangoRCString *)mstr2->data;
    int id1 = mango_rcstring_table_find(mstable, "Hello World", -1, true, 0);
    int id2 = mango_rcstring_table_find(mstable, "Hello World", -1, true, 0);
    CHECK_EQUAL(id1, id2);
    CHECK_EQUAL(rcstr1->internId, rcstr2->internId);
    CHECK_EQUAL(rcstr1->mstable, rcstr2->mstable);

    const MangoRCStringData *msdata1 = mango_rcstring_table_get(mstable, id1);
    const MangoRCStringData *msdata2 = mango_rcstring_table_get(mstable, id2);
    CHECK_EQUAL(msdata1, msdata2);
    CHECK_EQUAL(2, msdata1->refCount);
    mango_string_release(mstr1);
    mango_string_release(mstr2);
}

/**
 * Test that creating two mango strings of the same value increments
 * reference counts
 */
TEST_FIXTURE(RCStringTableTestFixture, TestIncRefOnStringFree)
{
    MangoString *mstr1 = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    MangoString *mstr2 = mango_stringfactory_new_string(string_factory, "Hello World", -1);
    MangoRCString *rcstr1 = (MangoRCString *)mstr1->data;
    const MangoRCStringData *msdata = mango_rcstring_table_get(mstable, rcstr1->internId);
    CHECK_EQUAL(msdata->refCount, 2);
    mango_string_release(mstr1);
    CHECK_EQUAL(msdata->refCount, 1);
    mango_string_release(mstr2);
}


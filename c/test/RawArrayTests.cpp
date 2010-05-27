
#include <UnitTest++.h>
#include "mangopub.h"
#include <vector>
#include <sstream>
#include <string.h>

class RawArrayTestFixture
{

public:
    RawArrayTestFixture()
    {
    }

    virtual ~RawArrayTestFixture()
    {
    }
};

/**
 * Tests the creation of an array.
 */
TEST_FIXTURE(RawArrayTestFixture, TestArrayCreate)
{
    MangoRawArray *array = mango_rawarray_new();
    CHECK(array != NULL);
    CHECK(array->items == NULL);
    CHECK(array->length == 0);
    CHECK(array->capacity == 0);
    mango_rawarray_free(array, NULL);
}

/**
 * Tests an insertion
 */
TEST_FIXTURE(RawArrayTestFixture, TestArrayInsert)
{
    MangoRawArray *array = mango_rawarray_new();
    CHECK(array != NULL);
    mango_rawarray_insert(array, (void *)10, -1);
    CHECK(array->length == 1);
    CHECK((int)mango_rawarray_itemat(array, 0) == 10);
    mango_rawarray_free(array, NULL);
}


/**
 * Tests clearing and see array is empty at the end.
 */
TEST_FIXTURE(RawArrayTestFixture, TestArrayClear)
{
    MangoRawArray *array = mango_rawarray_new();
    CHECK(array != NULL);
    mango_rawarray_insert(array, (void *)10, -1);
    mango_rawarray_insert(array, (void *)11, -1);
    mango_rawarray_insert(array, (void *)12, -1);
    mango_rawarray_insert(array, (void *)13, -1);
    mango_rawarray_insert(array, (void *)14, -1);
    int capacity = array->capacity;
    CHECK_EQUAL(array->length, (unsigned)5);
    mango_rawarray_clear(array, NULL);
    CHECK_EQUAL(array->length, (unsigned)0);
    CHECK_EQUAL(array->capacity, (unsigned)capacity);
    CHECK(array->items != NULL);
    mango_rawarray_free(array, NULL);
}


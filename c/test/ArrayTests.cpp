
#include <UnitTest++.h>
#include "mangopub.h"
#include <vector>
#include <sstream>
#include <string.h>

class ArrayTestFixture
{

public:
    ArrayTestFixture()
    {
    }

    virtual ~ArrayTestFixture()
    {
    }
};

/**
 * Tests the creation of an array.
 */
TEST_FIXTURE(ArrayTestFixture, TestArrayCreate)
{
    MangoArray *array = mango_array_new();
    CHECK(array != NULL);
    CHECK(array->items == NULL);
    CHECK(array->length == 0);
    CHECK(array->capacity == 0);
    mango_array_free(array, NULL);
}

/**
 * Tests an insertion
 */
TEST_FIXTURE(ArrayTestFixture, TestArrayInsert)
{
    MangoArray *array = mango_array_new();
    CHECK(array != NULL);
    mango_array_insert(array, (void *)10, -1);
    CHECK(array->length == 1);
    CHECK((int)mango_array_itemat(array, 0) == 10);
    mango_array_free(array, NULL);
}


/**
 * Tests clearing and see array is empty at the end.
 */
TEST_FIXTURE(ArrayTestFixture, TestArrayClear)
{
    MangoArray *array = mango_array_new();
    CHECK(array != NULL);
    mango_array_insert(array, (void *)10, -1);
    mango_array_insert(array, (void *)11, -1);
    mango_array_insert(array, (void *)12, -1);
    mango_array_insert(array, (void *)13, -1);
    mango_array_insert(array, (void *)14, -1);
    int capacity = array->capacity;
    CHECK_EQUAL(array->length, 5);
    mango_array_clear(array, NULL);
    CHECK_EQUAL(array->length, 0);
    CHECK_EQUAL(array->capacity, capacity);
    CHECK(array->items != NULL);
    mango_array_free(array, NULL);
}


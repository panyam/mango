
#include <UnitTest++.h>
#include "mangopub.h"
#include "mstring2.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"

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
    mango_array_free(array);
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
    mango_array_free(array);
}



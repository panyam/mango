
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

/**
 * A suite for testing out the MangoObject related methods.
 * Test the following:
 *
 * 1. Inheritance
 * 2. Incref, Decref, Release architecture
 * 3. Prototypes
 */
class ObjectTestFixture
{
public:
    ObjectTestFixture()
    {
    }

    virtual ~ObjectTestFixture()
    {
    }
};

/**
 * Tests the creation of a string table.
 */
TEST_FIXTURE(ObjectTestFixture, TestPrototypeInit)
{
    MangoPrototype prototype;
    mango_prototype_init(&prototype, "Hello World", sizeof(MangoPrototype));
    CHECK_EQUAL(0, strcmp(prototype.name, "Hello World"));
    CHECK(prototype.deallocFunc == NULL);
}


/**
 * Tests the creation of a string table.
 */
TEST_FIXTURE(ObjectTestFixture, TestObjectCreate)
{
    // MangoObject *obj = OBJ_ALLOC(MangoObject
    // CHECK(mstable != NULL);
}

/**
 * Tests the increfs.
 */
TEST_FIXTURE(ObjectTestFixture, TestObjectIncAndDecRef)
{
    MangoNumber *number = mango_number_from_int(666);
    CHECK_EQUAL(1, OBJ(number)->__refCount__);
    CHECK_EQUAL(2, OBJ(OBJ_INCREF(number))->__refCount__);
    CHECK_EQUAL(3, OBJ(OBJ_INCREF(number))->__refCount__);
    OBJ_DECREF(number); CHECK_EQUAL(2, OBJ(number)->__refCount__);
    OBJ_DECREF(number); CHECK_EQUAL(1, OBJ(number)->__refCount__);

    // a tricky one with EQUALS
    CHECK(OBJ_EQUALS(number, number));
    CHECK(OBJ_EQUALS(OBJ_INCREF(number), number));
    CHECK_EQUAL(2, OBJ(number)->__refCount__);
}


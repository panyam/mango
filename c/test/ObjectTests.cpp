
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
    mango_prototype_init(&prototype, "Hello World");
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


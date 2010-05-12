
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

/**
 * A suite for testing out the MangoObject related methods.
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
TEST_FIXTURE(ObjectTestFixture, TestCreate)
{
    // CHECK(mstable != NULL);
}



#include <UnitTest++.h>
#include "mangopub.h"

class StringTestFixture
{
public:
    StringTestFixture() { }
    virtual ~StringTestFixture() { }
};

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(StringTestFixture, TestStringCreate)
{
    MangoString *mstr = mango_string_with_capacity(0);
    mango_string_free(mstr);
}


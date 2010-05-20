
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"

/**
 * Tests the list structure.
 */
class ListTestFixture
{
public:
    ListTestFixture()
    {
    }
};

/**
 * Tests the creation of a parser.
 */
TEST_FIXTURE(ListTestFixture, TestListCreate)
{
    MangoList * list = mango_list_new();
    CHECK(list != NULL);
    CHECK_EQUAL((unsigned)0, list->size);
    CHECK(mango_list_is_empty(list));
    // mango_list_clear(list, (DeleteFunc)mango_object_decref);
    mango_list_free(list);
}

/**
 * Tests an insertion at the back of an empty list
 */
TEST_FIXTURE(ListTestFixture, TestListPushBackOnEmpty)
{
    MangoList * list = mango_list_new();
    mango_list_push_back(list, (void *)10);
    CHECK_EQUAL((unsigned)1, list->size);
    CHECK_EQUAL(10, (int)mango_list_front(list));
    CHECK_EQUAL(10, (int)mango_list_back(list));
    mango_list_free(list);
}

/**
 * Tests an insertion at the front of an empty list
 */
TEST_FIXTURE(ListTestFixture, TestListPushFrontOnEmpty)
{
    MangoList * list = mango_list_new();
    mango_list_push_front(list, (void *)10);
    CHECK_EQUAL((unsigned)1, list->size);
    CHECK_EQUAL(10, (int)mango_list_front(list));
    CHECK_EQUAL(10, (int)mango_list_back(list));
    mango_list_free(list);
}

/**
 * Tests clearing of a non-empty list.
 */
TEST_FIXTURE(ListTestFixture, TestListClear)
{
    MangoList * list = mango_list_new();
    mango_list_push_front(list, (void *)10);
    CHECK_EQUAL((unsigned)1, list->size);
    mango_list_clear(list, NULL);
    CHECK_EQUAL(0, list->size);
    CHECK(NULL == mango_list_front(list));
    CHECK(NULL == mango_list_back(list));
    mango_list_free(list);
}



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
    MangoList * list = mango_rawlist_new();
    CHECK(list != NULL);
    CHECK_EQUAL((unsigned)0, list->size);
    CHECK(mango_rawlist_is_empty(list));
    // mango_rawlist_clear(list, (DeleteFunc)mango_object_decref);
    mango_rawlist_free(list);
}

/**
 * Tests an insertion at the back of an empty list
 */
TEST_FIXTURE(ListTestFixture, TestListPushBackOnEmpty)
{
    MangoList * list = mango_rawlist_new();
    mango_rawlist_push_back(list, (void *)10);
    CHECK_EQUAL((unsigned)1, list->size);
    CHECK_EQUAL(10, (int)mango_rawlist_front(list));
    CHECK_EQUAL(10, (int)mango_rawlist_back(list));
    mango_rawlist_free(list);
}

/**
 * Tests an insertion at the front of an empty list
 */
TEST_FIXTURE(ListTestFixture, TestListPushFrontOnEmpty)
{
    MangoList * list = mango_rawlist_new();
    mango_rawlist_push_front(list, (void *)10);
    CHECK_EQUAL((unsigned)1, list->size);
    CHECK_EQUAL(10, (int)mango_rawlist_front(list));
    CHECK_EQUAL(10, (int)mango_rawlist_back(list));
    mango_rawlist_free(list);
}

/**
 * Tests an insertion at the back of a non empty list
 */
TEST_FIXTURE(ListTestFixture, TestListPushBackOnNonEmpty)
{
    MangoList * list = mango_rawlist_new();
    mango_rawlist_push_back(list, (void *)10);
    mango_rawlist_push_back(list, (void *)11);
    CHECK_EQUAL((unsigned)2, list->size);
    CHECK_EQUAL(11, (int)mango_rawlist_back(list));
    mango_rawlist_free(list);
}

/**
 * Tests an insertion at the front of a non empty list
 */
TEST_FIXTURE(ListTestFixture, TestListPushFrontOnNonEmpty)
{
    MangoList * list = mango_rawlist_new();
    mango_rawlist_push_front(list, (void *)10);
    mango_rawlist_push_front(list, (void *)11);
    CHECK_EQUAL((unsigned)2, list->size);
    CHECK_EQUAL(11, (int)mango_rawlist_front(list));
    mango_rawlist_free(list);
}


/**
 * Tests clearing of a non-empty list.
 */
TEST_FIXTURE(ListTestFixture, TestListClear)
{
    MangoList * list = mango_rawlist_new();
    mango_rawlist_push_front(list, (void *)10);
    CHECK_EQUAL((unsigned)1, list->size);
    mango_rawlist_clear(list, NULL);
    CHECK(list->size == 0);
    CHECK(NULL == mango_rawlist_front(list));
    CHECK(NULL == mango_rawlist_back(list));
    mango_rawlist_free(list);
}


static int deletor_int = 5;
void my_deletor(void *obj) { deletor_int --; }

/**
 * Tests clearing of a non-empty list with a deletor function
 */
TEST_FIXTURE(ListTestFixture, TestListClearWithDeletor)
{
    MangoList * list = mango_rawlist_new();
    for (int i = 0;i < 5;i++)
    {
        mango_rawlist_push_back(list, (void *)(10 + i));
    }
    CHECK_EQUAL((unsigned)5, list->size);

    mango_rawlist_clear(list, my_deletor);
    CHECK(list->size == 0);
    CHECK_EQUAL(0, deletor_int);
    mango_rawlist_free(list);
}



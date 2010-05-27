
#include <UnitTest++.h>
#include "mangopub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

class TemplateContextTestFixture
{
protected:
    MangoStringFactory *    string_factory;
    MangoTemplateContext *  context;

public:
    TemplateContextTestFixture() :
        string_factory((MangoStringFactory *)mango_rcstringfactory_new()),
        context(mango_tmplctx_new())
    {
    }

    virtual ~TemplateContextTestFixture()
    {
        OBJ_DECREF(context);
    }
};

/**
 * Tests the creation of a string table.
 */
TEST_FIXTURE(TemplateContextTestFixture, TestCreate)
{
    // CHECK(mstable != NULL);
}

/**
 * Tests getting in an empty context.
 */
TEST_FIXTURE(TemplateContextTestFixture, TestGetOnEmpty)
{
    MangoString *key = mango_stringfactory_new_string(string_factory, "a", -1);
    MangoObject *obj = OBJ_GETSTRATTR(context, key);
    CHECK(NULL == obj);
    OBJ_DECREF(key);
}

/**
 * Tests setting and getting a value
 */
TEST_FIXTURE(TemplateContextTestFixture, TestContains)
{
    MangoString *key = mango_stringfactory_new_string(string_factory, "a", -1);
    CHECK_EQUAL(false, mango_tmplctx_contains(context, key));
    MangoNumber *value = mango_number_from_int(3);
    int ss = mango_tmplctx_set(context, key, (MangoObject *)value);
    CHECK_EQUAL(1, ss);
    CHECK_EQUAL(true, mango_tmplctx_contains(context, key));
    OBJ_DECREF(value);
}


/**
 * Tests setting and getting a value
 */
TEST_FIXTURE(TemplateContextTestFixture, TestSetAndGet)
{
    MangoString *key = mango_stringfactory_new_string(string_factory, "a", -1);
    MangoNumber *value = mango_number_from_int(3);

    int ss = mango_tmplctx_set(context, key, (MangoObject *)value);
    CHECK_EQUAL(1, ss);
    MangoNumber *number = (MangoNumber *)OBJ_GETSTRATTR(context, key);
    CHECK_EQUAL(value, number);
}

/**
 * Tests pushing values and ensuring that current value is update to the
 * latest pushed value.
 */
TEST_FIXTURE(TemplateContextTestFixture, TestPush)
{
    MangoString *key = mango_stringfactory_new_string(string_factory, "a", -1);
    MangoNumber *v1 = mango_number_from_int(1);
    MangoNumber *v2 = mango_number_from_int(2);
    MangoNumber *v3 = mango_number_from_int(3);

    mango_tmplctx_push(context, key, OBJ(v1));
    mango_tmplctx_push(context, key, OBJ(v2));
    mango_tmplctx_push(context, key, OBJ(v3));

    MangoList *values = mango_tmplctx_get_values(context, key, false);
    CHECK_EQUAL(3, COLLECTION_SIZE(values));

    // ensure refcount is 2 - one for creation and one for using as a key
    // in the context (even though there have been 3 pushes)
    CHECK_EQUAL(2, OBJ_REFCOUNT(key));
    CHECK_EQUAL(2, OBJ_REFCOUNT(v1));
    CHECK_EQUAL(2, OBJ_REFCOUNT(v2));
    CHECK_EQUAL(2, OBJ_REFCOUNT(v3));
}

/**
 * Set and then delete a value.
 */
TEST_FIXTURE(TemplateContextTestFixture, TestDelete)
{
    // context.deleteValue("a");
    // CheckResolvedVar(NULL);

    MangoString *key = mango_stringfactory_new_string(string_factory, "a", -1);
    MangoNumber *v1 = mango_number_from_int(1);
    MangoNumber *v2 = mango_number_from_int(2);
    MangoNumber *v3 = mango_number_from_int(3);

    mango_tmplctx_push(context, key, OBJ(v1));
    mango_tmplctx_push(context, key, OBJ(v2));
    mango_tmplctx_push(context, key, OBJ(v3));

    MangoList *values = mango_tmplctx_get_values(context, key, false);
    CHECK_EQUAL(3, COLLECTION_SIZE(values));

    // erase it now
    mango_tmplctx_delete(context, key);
    // ensure refcount is 2 - one for creation and one for using as a key
    // in the context (even though there have been 3 pushes)
    CHECK_EQUAL(1, OBJ_REFCOUNT(key));
    CHECK_EQUAL(1, OBJ_REFCOUNT(v1));
    CHECK_EQUAL(1, OBJ_REFCOUNT(v2));
    CHECK_EQUAL(1, OBJ_REFCOUNT(v3));

    // delete the object now
}


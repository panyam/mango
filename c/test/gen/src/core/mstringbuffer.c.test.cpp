
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"


TEST(TestStringBufferCreateWithCapacity)
{
    #line 8 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_with_capacity(32);
    CHECK_EQUAL(32, mstr->capacity);
    CHECK_EQUAL(0, mstr->length);
    mango_stringbuffer_free(mstr);
    
}

TEST(TestStringBufferCreateFromBuffer)
{
    #line 32 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_free(mstr);
    
}

TEST(TestStringBufferClear)
{
    #line 82 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_clear(mstr)
    CHECK_EQUAL(0, mstr->length);
    mango_stringbuffer_free(mstr);
    
}

TEST(TestStringBufferSet)
{
    #line 104 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_set(mstr, "Hello Magnificient World", -1)
    CHECK_EQUAL(strlen("Hello Magnificient World"), mstr->length);
    CHECK_EQUAL(1 + strlen("Hello Magnificient World"), mstr->capacity);
    CHECK(strcmp("Hello Magnificient World", mstr->buffer) == 0);
    mango_stringbuffer_free(mstr);
    
}

TEST(TestStringBufferAppend)
{
    #line 130 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_append(mstr, ", I Love You", -1);
    CHECK_EQUAL(strlen("Hello Magnificient World, I Love You"), mstr->length);
    CHECK(strcmp("Hello Magnificient World, I Love You", mstr->buffer) == 0);
    mango_stringbuffer_free(mstr);
    
}

TEST(TestStringBufferAppend)
{
    #line 243 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_ensure_capacity(mstr, 128);
    CHECK_EQUAL((128 * 3) / 2, mstr->capacity);
    mango_stringbuffer_free(mstr);
    
}



#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"


#line 9 "../src/core/mstringbuffer.c"
TEST(TestStringBufferCreateWithCapacity)
{
    #line 10 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_with_capacity(32);
    CHECK(32 == mstr->capacity);
    CHECK(0 == mstr->length);
    mango_stringbuffer_free(mstr);
    
}

#line 33 "../src/core/mstringbuffer.c"
TEST(TestStringBufferCreateFromBuffer)
{
    #line 34 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_free(mstr);
    
}

#line 83 "../src/core/mstringbuffer.c"
TEST(TestStringBufferClear)
{
    #line 84 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_clear(mstr);
    CHECK_EQUAL(unsigned(0), mstr->length);
    mango_stringbuffer_free(mstr);
    
}

#line 105 "../src/core/mstringbuffer.c"
TEST(TestStringBufferSet)
{
    #line 106 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_set(mstr, "Hello Magnificient World", -1);
    CHECK_EQUAL(strlen("Hello Magnificient World"), mstr->length);
    CHECK_EQUAL(1 + strlen("Hello Magnificient World"), mstr->capacity);
    CHECK(strcmp("Hello Magnificient World", mstr->buffer) == 0);
    mango_stringbuffer_free(mstr);
    
}

#line 131 "../src/core/mstringbuffer.c"
TEST(TestStringBufferAppend)
{
    #line 131 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_append(mstr, ", I Love You", -1);
    CHECK_EQUAL(strlen("Hello Magnificient World, I Love You"), mstr->length);
    CHECK(strcmp("Hello Magnificient World, I Love You", mstr->buffer) == 0);
    mango_stringbuffer_free(mstr);
    
}

#line 244 "../src/core/mstringbuffer.c"
TEST(TestStringEnsureCapacity)
{
    #line 245 "../src/core/mstringbuffer.c"
    MangoStringBuffer *mstr = mango_stringbuffer_from_buffer("Hello World", -1);
    CHECK_EQUAL(1 + strlen("Hello World"), mstr->capacity);
    CHECK_EQUAL(strlen("Hello World"), mstr->length);
    CHECK(strcmp(mstr->buffer, "Hello World") == 0);
    mango_stringbuffer_ensure_capacity(mstr, 128);
    CHECK_EQUAL(unsigned((128 * 3) / 2), mstr->capacity);
    mango_stringbuffer_free(mstr);
    
}


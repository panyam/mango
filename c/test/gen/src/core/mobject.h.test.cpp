
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"


#line 159 "../src/core/mobject.h"
TEST(TestPrototypeInit)
{
    #line 159 "../src/core/mobject.h"
    MangoPrototype proto;
    mango_prototype_init(&proto, "Hello", sizeof(proto));
    CHECK_EQUAL(sizeof(proto), proto.size);
    CHECK(strcmp(proto.name, "Hello") == 0);
    free(proto.name);
    
}

SUITE(ObjectTests)
{
    #line 196 "../src/core/mobject.h"
    TEST(TestObjectIncDecRef)
    {
        #line 197 "../src/core/mobject.h"
         MangoObject *obj = OBJ_ALLOC(MangoObject, mango_prototype_default());
         CHECK_EQUAL(1, OBJ_REFCOUNT(obj));
         CHECK_EQUAL(2, OBJ_REFCOUNT(OBJ_INCREF(obj)));
         CHECK_EQUAL(3, OBJ_REFCOUNT(OBJ_INCREF(obj)));
         CHECK_EQUAL(true, OBJ_DECREF(obj)); 
         CHECK_EQUAL(2, OBJ_REFCOUNT(obj));
        
         CHECK_EQUAL(true, OBJ_DECREF(obj)); 
         CHECK_EQUAL(1, OBJ_REFCOUNT(obj));
         CHECK_EQUAL(false, OBJ_DECREF(obj));
         
    }
}


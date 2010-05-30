
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>
#include "maddfilter.h"


#line 24 "../src/nodes/mfilternode.h"
TEST(TestFilterNodeInit)
{
    #line 25 "../src/nodes/mfilternode.h"
    MangoFilter *filter = ZNEW(MangoFilter);
    OBJ_INIT(filter, mango_filter_prototype());
    MangoFilterNode *filternode = mango_filternode_new(filter);
    CHECK_EQUAL(1, OBJ_REFCOUNT(filternode));
    CHECK_EQUAL(2, OBJ_REFCOUNT(filter));
    CHECK(NULL == filternode->arguments);
    CHECK_EQUAL(false, OBJ_DECREF(filternode));
    CHECK_EQUAL(false, OBJ_DECREF(filter));
    
}

#line 59 "../src/nodes/mfilternode.h"
TEST(TestFilterNodeAddArg)
{
    #line 60 "../src/nodes/mfilternode.h"
     MangoFilter *filter = ZNEW(MangoFilter);
     OBJ_INIT(filter, mango_filter_prototype());
     MangoFilterNode *filternode = mango_filternode_new(filter);
     CHECK_EQUAL(1, OBJ_REFCOUNT(filternode));
     CHECK_EQUAL(2, OBJ_REFCOUNT(filter));
     CHECK(NULL == filternode->arguments);
     MangoString *varname = mango_rcstring_new("a", -1, NULL);
     MangoVar *var = mango_var_new(varname, false, NULL);
     mango_filternode_add_arg(filternode, var);
     CHECK_EQUAL(2, OBJ_REFCOUNT(var));
     CHECK_EQUAL(2, OBJ_REFCOUNT(varname));
    
     CHECK_EQUAL(false, OBJ_DECREF(filternode));
     CHECK_EQUAL(false, OBJ_DECREF(filter));
     
}


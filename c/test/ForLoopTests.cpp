
#include "RendererTests.h"

/**
 * Superclass of all renderer based test suites.
 */
class ForLoopTestFixture : public RendererTestFixture
{
public:
    ForLoopTestFixture()
    {
    }

    virtual ~ForLoopTestFixture()
    {
    }
};

TEST_FIXTURE(ForLoopTestFixture, TestForLoopNodes)
{
    objptr<MangoString> key(MRCSTR("intlist"));
    objptr<MangoArrayList> array(mango_arraylist_new());
    LIST_ADD_VALUES(array.get<MangoList>(), 3,
                        mango_number_from_int(1),
                        mango_number_from_int(2),
                        mango_number_from_int(3));
    mango_tmplctx_set(context, key.get(), array.obj());
    SetUpWithInputString("{%for a in intlist%}Item {{a}},{%endfor%}");
    CheckRenderedOutput("Item 1,Item 2,Item 3,");
}

#if 0

TEST_FIXTURE(ForLoopTestFixture, TestEmptyForLoop)
{
    context.setValue("intlist", null);
    SetUpWithInputString("{%for a in intlist%}Item {{a}},{%empty%}No Output Found{%endfor%}");
    checkRenderedOutput("No Output Found");
}

TEST_FIXTURE(ForLoopTestFixture, TestForLoopVariables)
{
    context.setValue("intlist", Utils.makeArrayList(1, 2, 3));
    SetUpWithInputString("{%for a in intlist%}{{a}} - [{{forloop.counter0}},{{forloop.counter}},{{forloop.first}},{{forloop.last}}]\n{%endfor%}");
    checkRenderedOutput("1 - [0,1,true,false]\n" + 
                       "2 - [1,2,false,false]\n" +
                       "3 - [2,3,false,true]\n");
}

TEST_FIXTURE(ForLoopTestFixture, TestLoopVariableDiesOutsideLoop)
{
    context.setValue("i", Utils.makeArrayList(1, 2, 3));
    context.setValue("j", Utils.makeArrayList(1, 2, 3));
    SetUpWithInputString("{%for a in i%}{{a}}{%endfor%}{{a}}");
    checkRenderedOutput("123");
}

TEST_FIXTURE(ForLoopTestFixture, TestLoopWithinLoop)
{
    context.setValue("i", Utils.makeArrayList(1, 2, 3));
    context.setValue("j", Utils.makeArrayList(1, 2, 3));
    SetUpWithInputString("{%for a in i%}" + 
                            "{%for b in j %}" +
                            "|{{a}},{{b}},{{forloop.parentloop.counter0}},{{forloop.counter0}}|" +
                            "{%endfor%}{%endfor%}");
                            
    checkRenderedOutput("|1,1,0,0||1,2,0,1||1,3,0,2|" + 
                          "|2,1,1,0||2,2,1,1||2,3,1,2|" + 
                          "|3,1,2,0||3,2,2,1||3,3,2,2|");
}

#endif

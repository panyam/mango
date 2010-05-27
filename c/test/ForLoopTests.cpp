
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

#if 0

TEST_FIXTURE(ForLoopTestFixture, TestForLoopNodes)
{
    context.setValue("intlist", Utils.makeArrayList(1, 2, 3));
    setupWithInputString("{%for a in intlist%}Item {{a}},{%endfor%}");
    checkRenderedOutput("Item 1,Item 2,Item 3,");
}

TEST_FIXTURE(ForLoopTestFixture, TestEmptyForLoop)
{
    context.setValue("intlist", null);
    setupWithInputString("{%for a in intlist%}Item {{a}},{%empty%}No Output Found{%endfor%}");
    checkRenderedOutput("No Output Found");
}

TEST_FIXTURE(ForLoopTestFixture, TestForLoopVariables)
{
    context.setValue("intlist", Utils.makeArrayList(1, 2, 3));
    setupWithInputString("{%for a in intlist%}{{a}} - [{{forloop.counter0}},{{forloop.counter}},{{forloop.first}},{{forloop.last}}]\n{%endfor%}");
    checkRenderedOutput("1 - [0,1,true,false]\n" + 
                       "2 - [1,2,false,false]\n" +
                       "3 - [2,3,false,true]\n");
}

TEST_FIXTURE(ForLoopTestFixture, TestLoopVariableDiesOutsideLoop)
{
    context.setValue("i", Utils.makeArrayList(1, 2, 3));
    context.setValue("j", Utils.makeArrayList(1, 2, 3));
    setupWithInputString("{%for a in i%}{{a}}{%endfor%}{{a}}");
    checkRenderedOutput("123");
}

TEST_FIXTURE(ForLoopTestFixture, TestLoopWithinLoop)
{
    context.setValue("i", Utils.makeArrayList(1, 2, 3));
    context.setValue("j", Utils.makeArrayList(1, 2, 3));
    setupWithInputString("{%for a in i%}" + 
                            "{%for b in j %}" +
                            "|{{a}},{{b}},{{forloop.parentloop.counter0}},{{forloop.counter0}}|" +
                            "{%endfor%}{%endfor%}");
                            
    checkRenderedOutput("|1,1,0,0||1,2,0,1||1,3,0,2|" + 
                          "|2,1,1,0||2,2,1,1||2,3,1,2|" + 
                          "|3,1,2,0||3,2,2,1||3,3,2,2|");
}

#endif

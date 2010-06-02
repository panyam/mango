
#include <UnitTest++.h>
#include "mangopub.h"
#include "mangoextpub.h"
#include "stlinputsource.h"
#include "objptr.h"
#include <vector>
#include <sstream>
#include <string.h>
#include <stdarg.h>

/**
 * Superclass of all renderer based test suites.
 */
class RendererTestFixture
{
public:
    MangoContext *          context;
    MangoTokenizer *        tokenizer;
    MangoParser *           parser;
    StlInputSource *        input_source;
    std::string             input_string;
    MangoTemplateContext *  tmplctx;
    MangoVarResolver *      resolver;

public:
    RendererTestFixture();

    virtual ~RendererTestFixture();

    /**
     * Check that the given string matches against the rendered output.
     */
	virtual void CheckRenderedOutput(const char *output);

protected:
    virtual void SetUpWithInputString(const std::string &input);
};


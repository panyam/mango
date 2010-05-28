# 
# Licensed under the Apache License, Version 2.0 (the "License"); 
# you may not use this file except in compliance with the License.  
# You may obtain a copy of the License at 
#
#       http://www.apache.org/licenses/LICENSE-2.0 
#
# Unless required by applicable law or agreed to in writing, software 
# distributed under the License is distributed on an "AS IS" BASIS, 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
#
# See the License for the specific language governing permissions and 
# limitations under the License.
#

###############  Changeable  Parameters  ##############

include ../Makefile.common

OUTPUT_DIR = ../bld

ifeq ($(MAIN_EXE_NAME),)
    MAIN_EXE_NAME     =   mangoctest
endif

####    Installation Directories    ####
BIN_INSTALL_DIR         = /usr/local/bin

###############  DO NOT MODIFY BELOW THIS   ##############

UNITTEST_PP_DIR     = ../../UnitTest++

TEST_SOURCE_FOLDERS = .
INCLUDE_FOLDERS     = ../src ../ext
TEST_SOURCES        := $(foreach dir,$(TEST_SOURCE_FOLDERS),$(wildcard $(dir)/*.cpp))
TEST_OBJS           = $(foreach obj, $(patsubst %.cpp,%.o,$(TEST_SOURCES)), $(OUTPUT_DIR)/$(obj))
TEST_OUTPUT         = $(OUTPUT_DIR)/$(MAIN_EXE_NAME)
ARCHIVES            = $(UNITTEST_PP_DIR)/libUnitTest++.a

LIBS                = 


###################     Begin Targets       ######################

LINK_STATICALLY = yes

# Implicit rule to build .o into the build directory from .cpp
$(OUTPUT_DIR)/%.o : %.cpp
	@echo Building $@
	@$(GPP) -I$(UNITTEST_PP_DIR)/src -c $(CFLAGS) $< -o $@

.PHONY: clean cleanall distclean test

ifeq ($(LINK_STATICALLY),yes)

test: base $(TEST_OBJS)
	@echo Building Test with Static Libraries...
	$(GPP) $(CFLAGS) $(TEST_OBJS) $(OUTPUT_DIR)/libmango.a $(ARCHIVES) -o $(TEST_OUTPUT) $(LIBS)
	$(TEST_OUTPUT)

else

test: base $(TEST_OBJS)
	@echo Building Test with Shared Libraries...
	$(GPP) $(CFLAGS) $(TEST_OBJS) -o $(TEST_OUTPUT) $(LIBS)

endif

install: 
	@echo "Nothing for install.  Run the test executable from here itself."

base:
	@mkdir -p "$(OUTPUT_DIR)"

clean:
	@rm -f $(TEST_OBJS)

cleanall: clean
	@rm -f "$(TEST_OUTPUT)"

distclean: cleanall
	@rm -f Makefile

dep:
	makedepend -Y -p"$(OUTPUT_DIR)/" $(INCLUDE_FLAGS)  -- $(TEST_SOURCES)
# DO NOT DELETE

../bld/./BinTreeTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./BinTreeTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./BinTreeTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./BinTreeTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./BinTreeTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./BinTreeTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./BinTreeTests.o: ../src/core/mrcstringfactory.h
../bld/./BinTreeTests.o: ../src/core/mstringfactory.h
../bld/./BinTreeTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./BinTreeTests.o: ../src/core/mstringbuffer.h
../bld/./BinTreeTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./BinTreeTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./BinTreeTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./BinTreeTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./BinTreeTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./BinTreeTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./BinTreeTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./BinTreeTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./BinTreeTests.o: ../src/parser/mtoken.h
../bld/./BinTreeTests.o: ../src/parser/mparsercontext.h
../bld/./BinTreeTests.o: ../src/parser/mtagparser.h
../bld/./BinTreeTests.o: ../src/parser/mtagparserlibrary.h
../bld/./BinTreeTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./BinTreeTests.o: ../src/parser/mtokenlists.h
../bld/./BinTreeTests.o: ../src/renderer/mrenderer.h
../bld/./BinTreeTests.o: ../src/resolver/mtemplateloader.h
../bld/./BinTreeTests.o: ../src/resolver/mtmplctx.h
../bld/./BinTreeTests.o: ../src/resolver/mvarresolver.h
../bld/./BinTreeTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./BinTreeTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./BinTreeTests.o: ../src/utils/mcollection.h
../bld/./BinTreeTests.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./BinTreeTests.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./BinTreeTests.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./BinTreeTests.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./BinTreeTests.o: ../src/utils/mtable.h
../bld/./ExprTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./ExprTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./ExprTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./ExprTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./ExprTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./ExprTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./ExprTests.o: ../src/core/mrcstringfactory.h
../bld/./ExprTests.o: ../src/core/mstringfactory.h
../bld/./ExprTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./ExprTests.o: ../src/core/mstringbuffer.h
../bld/./ExprTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./ExprTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./ExprTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./ExprTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./ExprTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./ExprTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./ExprTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./ExprTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./ExprTests.o: ../src/parser/mtoken.h ../src/parser/mparsercontext.h
../bld/./ExprTests.o: ../src/parser/mtagparser.h
../bld/./ExprTests.o: ../src/parser/mtagparserlibrary.h
../bld/./ExprTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./ExprTests.o: ../src/parser/mtokenlists.h ../src/renderer/mrenderer.h
../bld/./ExprTests.o: ../src/resolver/mtemplateloader.h
../bld/./ExprTests.o: ../src/resolver/mtmplctx.h
../bld/./ExprTests.o: ../src/resolver/mvarresolver.h
../bld/./ExprTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./ExprTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./ExprTests.o: ../src/utils/mcollection.h ../src/utils/mlinkedlist.h
../bld/./ExprTests.o: ../src/utils/mlist.h ../src/utils/mmemutils.h
../bld/./ExprTests.o: ../src/utils/mrawarray.h ../src/utils/mrawlist.h
../bld/./ExprTests.o: ../src/utils/msingletons.h ../src/utils/mtable.h
../bld/./ExprTests.o: ../src/utils/mtreetable.h ../src/utils/mtable.h
../bld/./ExprTests.o: ../ext/mangoextpub.h ../ext/mfortag.h stlinputsource.h
../bld/./ExprTests.o: ../ext/maddfilter.h
../bld/./ForLoopTests.o: RendererTests.h ../src/mangopub.h ../src/mfwddefs.h
../bld/./ForLoopTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./ForLoopTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./ForLoopTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./ForLoopTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./ForLoopTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./ForLoopTests.o: ../src/core/mrcstringfactory.h
../bld/./ForLoopTests.o: ../src/core/mstringfactory.h
../bld/./ForLoopTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./ForLoopTests.o: ../src/core/mstringbuffer.h
../bld/./ForLoopTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./ForLoopTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./ForLoopTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./ForLoopTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./ForLoopTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./ForLoopTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./ForLoopTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./ForLoopTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./ForLoopTests.o: ../src/parser/mtoken.h
../bld/./ForLoopTests.o: ../src/parser/mparsercontext.h
../bld/./ForLoopTests.o: ../src/parser/mtagparser.h
../bld/./ForLoopTests.o: ../src/parser/mtagparserlibrary.h
../bld/./ForLoopTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./ForLoopTests.o: ../src/parser/mtokenlists.h
../bld/./ForLoopTests.o: ../src/renderer/mrenderer.h
../bld/./ForLoopTests.o: ../src/resolver/mtemplateloader.h
../bld/./ForLoopTests.o: ../src/resolver/mtmplctx.h
../bld/./ForLoopTests.o: ../src/resolver/mvarresolver.h
../bld/./ForLoopTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./ForLoopTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./ForLoopTests.o: ../src/utils/mcollection.h
../bld/./ForLoopTests.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./ForLoopTests.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./ForLoopTests.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./ForLoopTests.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./ForLoopTests.o: ../src/utils/mtable.h ../ext/mangoextpub.h
../bld/./ForLoopTests.o: ../ext/mfortag.h stlinputsource.h
../bld/./ForLoopTests.o: ../ext/maddfilter.h
../bld/./ObjectTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./ObjectTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./ObjectTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./ObjectTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./ObjectTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./ObjectTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./ObjectTests.o: ../src/core/mrcstringfactory.h
../bld/./ObjectTests.o: ../src/core/mstringfactory.h
../bld/./ObjectTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./ObjectTests.o: ../src/core/mstringbuffer.h
../bld/./ObjectTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./ObjectTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./ObjectTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./ObjectTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./ObjectTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./ObjectTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./ObjectTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./ObjectTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./ObjectTests.o: ../src/parser/mtoken.h ../src/parser/mparsercontext.h
../bld/./ObjectTests.o: ../src/parser/mtagparser.h
../bld/./ObjectTests.o: ../src/parser/mtagparserlibrary.h
../bld/./ObjectTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./ObjectTests.o: ../src/parser/mtokenlists.h
../bld/./ObjectTests.o: ../src/renderer/mrenderer.h
../bld/./ObjectTests.o: ../src/resolver/mtemplateloader.h
../bld/./ObjectTests.o: ../src/resolver/mtmplctx.h
../bld/./ObjectTests.o: ../src/resolver/mvarresolver.h
../bld/./ObjectTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./ObjectTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./ObjectTests.o: ../src/utils/mcollection.h ../src/utils/mlinkedlist.h
../bld/./ObjectTests.o: ../src/utils/mlist.h ../src/utils/mmemutils.h
../bld/./ObjectTests.o: ../src/utils/mrawarray.h ../src/utils/mrawlist.h
../bld/./ObjectTests.o: ../src/utils/msingletons.h ../src/utils/mtable.h
../bld/./ObjectTests.o: ../src/utils/mtreetable.h ../src/utils/mtable.h
../bld/./ObjectTests.o: stlinputsource.h
../bld/./ParserTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./ParserTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./ParserTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./ParserTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./ParserTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./ParserTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./ParserTests.o: ../src/core/mrcstringfactory.h
../bld/./ParserTests.o: ../src/core/mstringfactory.h
../bld/./ParserTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./ParserTests.o: ../src/core/mstringbuffer.h
../bld/./ParserTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./ParserTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./ParserTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./ParserTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./ParserTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./ParserTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./ParserTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./ParserTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./ParserTests.o: ../src/parser/mtoken.h ../src/parser/mparsercontext.h
../bld/./ParserTests.o: ../src/parser/mtagparser.h
../bld/./ParserTests.o: ../src/parser/mtagparserlibrary.h
../bld/./ParserTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./ParserTests.o: ../src/parser/mtokenlists.h
../bld/./ParserTests.o: ../src/renderer/mrenderer.h
../bld/./ParserTests.o: ../src/resolver/mtemplateloader.h
../bld/./ParserTests.o: ../src/resolver/mtmplctx.h
../bld/./ParserTests.o: ../src/resolver/mvarresolver.h
../bld/./ParserTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./ParserTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./ParserTests.o: ../src/utils/mcollection.h ../src/utils/mlinkedlist.h
../bld/./ParserTests.o: ../src/utils/mlist.h ../src/utils/mmemutils.h
../bld/./ParserTests.o: ../src/utils/mrawarray.h ../src/utils/mrawlist.h
../bld/./ParserTests.o: ../src/utils/msingletons.h ../src/utils/mtable.h
../bld/./ParserTests.o: ../src/utils/mtreetable.h ../src/utils/mtable.h
../bld/./ParserTests.o: ../ext/mangoextpub.h ../ext/mfortag.h
../bld/./ParserTests.o: stlinputsource.h ../ext/maddfilter.h
../bld/./RawArrayTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./RawArrayTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./RawArrayTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./RawArrayTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./RawArrayTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./RawArrayTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./RawArrayTests.o: ../src/core/mrcstringfactory.h
../bld/./RawArrayTests.o: ../src/core/mstringfactory.h
../bld/./RawArrayTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./RawArrayTests.o: ../src/core/mstringbuffer.h
../bld/./RawArrayTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./RawArrayTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./RawArrayTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./RawArrayTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./RawArrayTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./RawArrayTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./RawArrayTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./RawArrayTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./RawArrayTests.o: ../src/parser/mtoken.h
../bld/./RawArrayTests.o: ../src/parser/mparsercontext.h
../bld/./RawArrayTests.o: ../src/parser/mtagparser.h
../bld/./RawArrayTests.o: ../src/parser/mtagparserlibrary.h
../bld/./RawArrayTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./RawArrayTests.o: ../src/parser/mtokenlists.h
../bld/./RawArrayTests.o: ../src/renderer/mrenderer.h
../bld/./RawArrayTests.o: ../src/resolver/mtemplateloader.h
../bld/./RawArrayTests.o: ../src/resolver/mtmplctx.h
../bld/./RawArrayTests.o: ../src/resolver/mvarresolver.h
../bld/./RawArrayTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./RawArrayTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./RawArrayTests.o: ../src/utils/mcollection.h
../bld/./RawArrayTests.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./RawArrayTests.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./RawArrayTests.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./RawArrayTests.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./RawArrayTests.o: ../src/utils/mtable.h
../bld/./RawListTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./RawListTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./RawListTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./RawListTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./RawListTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./RawListTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./RawListTests.o: ../src/core/mrcstringfactory.h
../bld/./RawListTests.o: ../src/core/mstringfactory.h
../bld/./RawListTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./RawListTests.o: ../src/core/mstringbuffer.h
../bld/./RawListTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./RawListTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./RawListTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./RawListTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./RawListTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./RawListTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./RawListTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./RawListTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./RawListTests.o: ../src/parser/mtoken.h
../bld/./RawListTests.o: ../src/parser/mparsercontext.h
../bld/./RawListTests.o: ../src/parser/mtagparser.h
../bld/./RawListTests.o: ../src/parser/mtagparserlibrary.h
../bld/./RawListTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./RawListTests.o: ../src/parser/mtokenlists.h
../bld/./RawListTests.o: ../src/renderer/mrenderer.h
../bld/./RawListTests.o: ../src/resolver/mtemplateloader.h
../bld/./RawListTests.o: ../src/resolver/mtmplctx.h
../bld/./RawListTests.o: ../src/resolver/mvarresolver.h
../bld/./RawListTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./RawListTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./RawListTests.o: ../src/utils/mcollection.h
../bld/./RawListTests.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./RawListTests.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./RawListTests.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./RawListTests.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./RawListTests.o: ../src/utils/mtable.h ../ext/mangoextpub.h
../bld/./RawListTests.o: ../ext/mfortag.h stlinputsource.h
../bld/./RawListTests.o: ../ext/maddfilter.h
../bld/./ResolverTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./ResolverTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./ResolverTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./ResolverTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./ResolverTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./ResolverTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./ResolverTests.o: ../src/core/mrcstringfactory.h
../bld/./ResolverTests.o: ../src/core/mstringfactory.h
../bld/./ResolverTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./ResolverTests.o: ../src/core/mstringbuffer.h
../bld/./ResolverTests.o: ../src/core/mstringfactory.h ../src/nodes/mfilter.h
../bld/./ResolverTests.o: ../src/nodes/mvar.h ../src/nodes/mfilterlibrary.h
../bld/./ResolverTests.o: ../src/nodes/mfilternode.h ../src/nodes/mfreetext.h
../bld/./ResolverTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./ResolverTests.o: ../src/nodes/mnodelist.h ../src/nodes/mtagnode.h
../bld/./ResolverTests.o: ../src/nodes/mvar.h ../src/nodes/mvariterator.h
../bld/./ResolverTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./ResolverTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./ResolverTests.o: ../src/parser/mtoken.h
../bld/./ResolverTests.o: ../src/parser/mparsercontext.h
../bld/./ResolverTests.o: ../src/parser/mtagparser.h
../bld/./ResolverTests.o: ../src/parser/mtagparserlibrary.h
../bld/./ResolverTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./ResolverTests.o: ../src/parser/mtokenlists.h
../bld/./ResolverTests.o: ../src/renderer/mrenderer.h
../bld/./ResolverTests.o: ../src/resolver/mtemplateloader.h
../bld/./ResolverTests.o: ../src/resolver/mtmplctx.h
../bld/./ResolverTests.o: ../src/resolver/mvarresolver.h
../bld/./ResolverTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./ResolverTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./ResolverTests.o: ../src/utils/mcollection.h
../bld/./ResolverTests.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./ResolverTests.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./ResolverTests.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./ResolverTests.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./ResolverTests.o: ../src/utils/mtable.h stlinputsource.h
../bld/./stlinputsource.o: stlinputsource.h ../src/mangopub.h
../bld/./stlinputsource.o: ../src/mfwddefs.h ../src/core/mclasses.h
../bld/./stlinputsource.o: ../src/core/merror.h ../src/core/minputsource.h
../bld/./stlinputsource.o: ../src/core/miterator.h ../src/core/mobject.h
../bld/./stlinputsource.o: ../src/utils/mutils.h ../src/core/mnumber.h
../bld/./stlinputsource.o: ../src/core/mobject.h ../src/core/mrcstring.h
../bld/./stlinputsource.o: ../src/core/mstring.h
../bld/./stlinputsource.o: ../src/core/mrcstringfactory.h
../bld/./stlinputsource.o: ../src/core/mstringfactory.h
../bld/./stlinputsource.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./stlinputsource.o: ../src/core/mstringbuffer.h
../bld/./stlinputsource.o: ../src/core/mstringfactory.h
../bld/./stlinputsource.o: ../src/nodes/mfilter.h ../src/nodes/mvar.h
../bld/./stlinputsource.o: ../src/nodes/mfilterlibrary.h
../bld/./stlinputsource.o: ../src/nodes/mfilternode.h
../bld/./stlinputsource.o: ../src/nodes/mfreetext.h ../src/nodes/mnode.h
../bld/./stlinputsource.o: ../src/nodes/mnode.h ../src/nodes/mnodelist.h
../bld/./stlinputsource.o: ../src/nodes/mtagnode.h ../src/nodes/mvar.h
../bld/./stlinputsource.o: ../src/nodes/mvariterator.h
../bld/./stlinputsource.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./stlinputsource.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./stlinputsource.o: ../src/parser/mtoken.h
../bld/./stlinputsource.o: ../src/parser/mparsercontext.h
../bld/./stlinputsource.o: ../src/parser/mtagparser.h
../bld/./stlinputsource.o: ../src/parser/mtagparserlibrary.h
../bld/./stlinputsource.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./stlinputsource.o: ../src/parser/mtokenlists.h
../bld/./stlinputsource.o: ../src/renderer/mrenderer.h
../bld/./stlinputsource.o: ../src/resolver/mtemplateloader.h
../bld/./stlinputsource.o: ../src/resolver/mtmplctx.h
../bld/./stlinputsource.o: ../src/resolver/mvarresolver.h
../bld/./stlinputsource.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./stlinputsource.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./stlinputsource.o: ../src/utils/mcollection.h
../bld/./stlinputsource.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./stlinputsource.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./stlinputsource.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./stlinputsource.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./stlinputsource.o: ../src/utils/mtable.h
../bld/./StringTableTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./StringTableTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./StringTableTests.o: ../src/core/minputsource.h
../bld/./StringTableTests.o: ../src/core/miterator.h ../src/core/mobject.h
../bld/./StringTableTests.o: ../src/utils/mutils.h ../src/core/mnumber.h
../bld/./StringTableTests.o: ../src/core/mobject.h ../src/core/mrcstring.h
../bld/./StringTableTests.o: ../src/core/mstring.h
../bld/./StringTableTests.o: ../src/core/mrcstringfactory.h
../bld/./StringTableTests.o: ../src/core/mstringfactory.h
../bld/./StringTableTests.o: ../src/core/mrcstringtable.h
../bld/./StringTableTests.o: ../src/core/mstring.h
../bld/./StringTableTests.o: ../src/core/mstringbuffer.h
../bld/./StringTableTests.o: ../src/core/mstringfactory.h
../bld/./StringTableTests.o: ../src/nodes/mfilter.h ../src/nodes/mvar.h
../bld/./StringTableTests.o: ../src/nodes/mfilterlibrary.h
../bld/./StringTableTests.o: ../src/nodes/mfilternode.h
../bld/./StringTableTests.o: ../src/nodes/mfreetext.h ../src/nodes/mnode.h
../bld/./StringTableTests.o: ../src/nodes/mnode.h ../src/nodes/mnodelist.h
../bld/./StringTableTests.o: ../src/nodes/mtagnode.h ../src/nodes/mvar.h
../bld/./StringTableTests.o: ../src/nodes/mvariterator.h
../bld/./StringTableTests.o: ../src/nodes/mvarlibrary.h
../bld/./StringTableTests.o: ../src/nodes/mvarnode.h ../src/parser/mparser.h
../bld/./StringTableTests.o: ../src/parser/mtokenizer.h
../bld/./StringTableTests.o: ../src/parser/mtoken.h
../bld/./StringTableTests.o: ../src/parser/mparsercontext.h
../bld/./StringTableTests.o: ../src/parser/mtagparser.h
../bld/./StringTableTests.o: ../src/parser/mtagparserlibrary.h
../bld/./StringTableTests.o: ../src/parser/mtoken.h
../bld/./StringTableTests.o: ../src/parser/mtokenizer.h
../bld/./StringTableTests.o: ../src/parser/mtokenlists.h
../bld/./StringTableTests.o: ../src/renderer/mrenderer.h
../bld/./StringTableTests.o: ../src/resolver/mtemplateloader.h
../bld/./StringTableTests.o: ../src/resolver/mtmplctx.h
../bld/./StringTableTests.o: ../src/resolver/mvarresolver.h
../bld/./StringTableTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./StringTableTests.o: ../src/utils/mcollection.h
../bld/./StringTableTests.o: ../src/utils/mbintree.h
../bld/./StringTableTests.o: ../src/utils/mcollection.h
../bld/./StringTableTests.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./StringTableTests.o: ../src/utils/mmemutils.h
../bld/./StringTableTests.o: ../src/utils/mrawarray.h ../src/utils/mrawlist.h
../bld/./StringTableTests.o: ../src/utils/msingletons.h ../src/utils/mtable.h
../bld/./StringTableTests.o: ../src/utils/mtreetable.h ../src/utils/mtable.h
../bld/./StringTableTests.o: stlinputsource.h
../bld/./TemplateContextTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./TemplateContextTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./TemplateContextTests.o: ../src/core/minputsource.h
../bld/./TemplateContextTests.o: ../src/core/miterator.h
../bld/./TemplateContextTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./TemplateContextTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./TemplateContextTests.o: ../src/core/mrcstring.h
../bld/./TemplateContextTests.o: ../src/core/mstring.h
../bld/./TemplateContextTests.o: ../src/core/mrcstringfactory.h
../bld/./TemplateContextTests.o: ../src/core/mstringfactory.h
../bld/./TemplateContextTests.o: ../src/core/mrcstringtable.h
../bld/./TemplateContextTests.o: ../src/core/mstring.h
../bld/./TemplateContextTests.o: ../src/core/mstringbuffer.h
../bld/./TemplateContextTests.o: ../src/core/mstringfactory.h
../bld/./TemplateContextTests.o: ../src/nodes/mfilter.h ../src/nodes/mvar.h
../bld/./TemplateContextTests.o: ../src/nodes/mfilterlibrary.h
../bld/./TemplateContextTests.o: ../src/nodes/mfilternode.h
../bld/./TemplateContextTests.o: ../src/nodes/mfreetext.h
../bld/./TemplateContextTests.o: ../src/nodes/mnode.h ../src/nodes/mnode.h
../bld/./TemplateContextTests.o: ../src/nodes/mnodelist.h
../bld/./TemplateContextTests.o: ../src/nodes/mtagnode.h ../src/nodes/mvar.h
../bld/./TemplateContextTests.o: ../src/nodes/mvariterator.h
../bld/./TemplateContextTests.o: ../src/nodes/mvarlibrary.h
../bld/./TemplateContextTests.o: ../src/nodes/mvarnode.h
../bld/./TemplateContextTests.o: ../src/parser/mparser.h
../bld/./TemplateContextTests.o: ../src/parser/mtokenizer.h
../bld/./TemplateContextTests.o: ../src/parser/mtoken.h
../bld/./TemplateContextTests.o: ../src/parser/mparsercontext.h
../bld/./TemplateContextTests.o: ../src/parser/mtagparser.h
../bld/./TemplateContextTests.o: ../src/parser/mtagparserlibrary.h
../bld/./TemplateContextTests.o: ../src/parser/mtoken.h
../bld/./TemplateContextTests.o: ../src/parser/mtokenizer.h
../bld/./TemplateContextTests.o: ../src/parser/mtokenlists.h
../bld/./TemplateContextTests.o: ../src/renderer/mrenderer.h
../bld/./TemplateContextTests.o: ../src/resolver/mtemplateloader.h
../bld/./TemplateContextTests.o: ../src/resolver/mtmplctx.h
../bld/./TemplateContextTests.o: ../src/resolver/mvarresolver.h
../bld/./TemplateContextTests.o: ../src/utils/marraylist.h
../bld/./TemplateContextTests.o: ../src/utils/mlist.h
../bld/./TemplateContextTests.o: ../src/utils/mcollection.h
../bld/./TemplateContextTests.o: ../src/utils/mbintree.h
../bld/./TemplateContextTests.o: ../src/utils/mcollection.h
../bld/./TemplateContextTests.o: ../src/utils/mlinkedlist.h
../bld/./TemplateContextTests.o: ../src/utils/mlist.h
../bld/./TemplateContextTests.o: ../src/utils/mmemutils.h
../bld/./TemplateContextTests.o: ../src/utils/mrawarray.h
../bld/./TemplateContextTests.o: ../src/utils/mrawlist.h
../bld/./TemplateContextTests.o: ../src/utils/msingletons.h
../bld/./TemplateContextTests.o: ../src/utils/mtable.h
../bld/./TemplateContextTests.o: ../src/utils/mtreetable.h
../bld/./TemplateContextTests.o: ../src/utils/mtable.h stlinputsource.h
../bld/./TokenizerTests.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./TokenizerTests.o: ../src/core/mclasses.h ../src/core/merror.h
../bld/./TokenizerTests.o: ../src/core/minputsource.h ../src/core/miterator.h
../bld/./TokenizerTests.o: ../src/core/mobject.h ../src/utils/mutils.h
../bld/./TokenizerTests.o: ../src/core/mnumber.h ../src/core/mobject.h
../bld/./TokenizerTests.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./TokenizerTests.o: ../src/core/mrcstringfactory.h
../bld/./TokenizerTests.o: ../src/core/mstringfactory.h
../bld/./TokenizerTests.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./TokenizerTests.o: ../src/core/mstringbuffer.h
../bld/./TokenizerTests.o: ../src/core/mstringfactory.h
../bld/./TokenizerTests.o: ../src/nodes/mfilter.h ../src/nodes/mvar.h
../bld/./TokenizerTests.o: ../src/nodes/mfilterlibrary.h
../bld/./TokenizerTests.o: ../src/nodes/mfilternode.h
../bld/./TokenizerTests.o: ../src/nodes/mfreetext.h ../src/nodes/mnode.h
../bld/./TokenizerTests.o: ../src/nodes/mnode.h ../src/nodes/mnodelist.h
../bld/./TokenizerTests.o: ../src/nodes/mtagnode.h ../src/nodes/mvar.h
../bld/./TokenizerTests.o: ../src/nodes/mvariterator.h
../bld/./TokenizerTests.o: ../src/nodes/mvarlibrary.h ../src/nodes/mvarnode.h
../bld/./TokenizerTests.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./TokenizerTests.o: ../src/parser/mtoken.h
../bld/./TokenizerTests.o: ../src/parser/mparsercontext.h
../bld/./TokenizerTests.o: ../src/parser/mtagparser.h
../bld/./TokenizerTests.o: ../src/parser/mtagparserlibrary.h
../bld/./TokenizerTests.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./TokenizerTests.o: ../src/parser/mtokenlists.h
../bld/./TokenizerTests.o: ../src/renderer/mrenderer.h
../bld/./TokenizerTests.o: ../src/resolver/mtemplateloader.h
../bld/./TokenizerTests.o: ../src/resolver/mtmplctx.h
../bld/./TokenizerTests.o: ../src/resolver/mvarresolver.h
../bld/./TokenizerTests.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./TokenizerTests.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./TokenizerTests.o: ../src/utils/mcollection.h
../bld/./TokenizerTests.o: ../src/utils/mlinkedlist.h ../src/utils/mlist.h
../bld/./TokenizerTests.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./TokenizerTests.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./TokenizerTests.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./TokenizerTests.o: ../src/utils/mtable.h stlinputsource.h

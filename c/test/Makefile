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
INCLUDE_FOLDERS     = ../include ../include/ext
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

../bld/./BinTreeTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./BinTreeTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./BinTreeTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./BinTreeTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./BinTreeTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./BinTreeTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./BinTreeTests.o: ../include/merror.h ../include/mfilter.h
../bld/./BinTreeTests.o: ../include/mvar.h ../include/mstring.h
../bld/./BinTreeTests.o: ../include/mfilterlibrary.h ../include/mfilternode.h
../bld/./BinTreeTests.o: ../include/mfreetext.h ../include/mnode.h
../bld/./BinTreeTests.o: ../include/minputsource.h ../include/mlinkedlist.h
../bld/./BinTreeTests.o: ../include/mnodelist.h ../include/mnumber.h
../bld/./BinTreeTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./BinTreeTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./BinTreeTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./BinTreeTests.o: ../include/mstringfactory.h
../bld/./BinTreeTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./BinTreeTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./BinTreeTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./BinTreeTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./BinTreeTests.o: ../include/mtagparserlibrary.h
../bld/./BinTreeTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./BinTreeTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./BinTreeTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./ExprTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./ExprTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ExprTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./ExprTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./ExprTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ExprTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./ExprTests.o: ../include/merror.h ../include/mfilter.h
../bld/./ExprTests.o: ../include/mvar.h ../include/mstring.h
../bld/./ExprTests.o: ../include/mfilterlibrary.h ../include/mfilternode.h
../bld/./ExprTests.o: ../include/mfreetext.h ../include/mnode.h
../bld/./ExprTests.o: ../include/minputsource.h ../include/mlinkedlist.h
../bld/./ExprTests.o: ../include/mnodelist.h ../include/mnumber.h
../bld/./ExprTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ExprTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ExprTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./ExprTests.o: ../include/mstringfactory.h ../include/mrcstringtable.h
../bld/./ExprTests.o: ../include/mrenderer.h ../include/msingletons.h
../bld/./ExprTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ExprTests.o: ../include/mtreetable.h ../include/mtagnode.h
../bld/./ExprTests.o: ../include/mtagparser.h ../include/mtagparserlibrary.h
../bld/./ExprTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ExprTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./ExprTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./ExprTests.o: ../include/ext/mangoextpub.h ../include/ext/mfortag.h
../bld/./ExprTests.o: stlinputsource.h ../include/ext/maddfilter.h
../bld/./ForLoopTests.o: RendererTests.h ../include/mangopub.h
../bld/./ForLoopTests.o: ../include/mrawarray.h ../include/mobject.h
../bld/./ForLoopTests.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./ForLoopTests.o: ../include/mutils.h ../include/mrawlist.h
../bld/./ForLoopTests.o: ../include/marraylist.h ../include/mlist.h
../bld/./ForLoopTests.o: ../include/mcollection.h ../include/mbintree.h
../bld/./ForLoopTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ForLoopTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ForLoopTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ForLoopTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ForLoopTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ForLoopTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./ForLoopTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./ForLoopTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./ForLoopTests.o: ../include/mparsercontext.h ../include/mrcstring.h
../bld/./ForLoopTests.o: ../include/mrcstringfactory.h
../bld/./ForLoopTests.o: ../include/mstringfactory.h
../bld/./ForLoopTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./ForLoopTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./ForLoopTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./ForLoopTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ForLoopTests.o: ../include/mtagparserlibrary.h
../bld/./ForLoopTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ForLoopTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./ForLoopTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./ForLoopTests.o: ../include/ext/mangoextpub.h
../bld/./ForLoopTests.o: ../include/ext/mfortag.h stlinputsource.h
../bld/./ForLoopTests.o: ../include/ext/maddfilter.h
../bld/./ObjectTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./ObjectTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ObjectTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./ObjectTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./ObjectTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ObjectTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./ObjectTests.o: ../include/merror.h ../include/mfilter.h
../bld/./ObjectTests.o: ../include/mvar.h ../include/mstring.h
../bld/./ObjectTests.o: ../include/mfilterlibrary.h ../include/mfilternode.h
../bld/./ObjectTests.o: ../include/mfreetext.h ../include/mnode.h
../bld/./ObjectTests.o: ../include/minputsource.h ../include/mlinkedlist.h
../bld/./ObjectTests.o: ../include/mnodelist.h ../include/mnumber.h
../bld/./ObjectTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ObjectTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ObjectTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./ObjectTests.o: ../include/mstringfactory.h
../bld/./ObjectTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./ObjectTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./ObjectTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./ObjectTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ObjectTests.o: ../include/mtagparserlibrary.h
../bld/./ObjectTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ObjectTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./ObjectTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./ObjectTests.o: stlinputsource.h
../bld/./ParserTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./ParserTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ParserTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./ParserTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./ParserTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ParserTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./ParserTests.o: ../include/merror.h ../include/mfilter.h
../bld/./ParserTests.o: ../include/mvar.h ../include/mstring.h
../bld/./ParserTests.o: ../include/mfilterlibrary.h ../include/mfilternode.h
../bld/./ParserTests.o: ../include/mfreetext.h ../include/mnode.h
../bld/./ParserTests.o: ../include/minputsource.h ../include/mlinkedlist.h
../bld/./ParserTests.o: ../include/mnodelist.h ../include/mnumber.h
../bld/./ParserTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ParserTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ParserTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./ParserTests.o: ../include/mstringfactory.h
../bld/./ParserTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./ParserTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./ParserTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./ParserTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ParserTests.o: ../include/mtagparserlibrary.h
../bld/./ParserTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ParserTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./ParserTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./ParserTests.o: ../include/ext/mangoextpub.h ../include/ext/mfortag.h
../bld/./ParserTests.o: stlinputsource.h ../include/ext/maddfilter.h
../bld/./RawArrayTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./RawArrayTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./RawArrayTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./RawArrayTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./RawArrayTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./RawArrayTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./RawArrayTests.o: ../include/merror.h ../include/mfilter.h
../bld/./RawArrayTests.o: ../include/mvar.h ../include/mstring.h
../bld/./RawArrayTests.o: ../include/mfilterlibrary.h
../bld/./RawArrayTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./RawArrayTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./RawArrayTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./RawArrayTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./RawArrayTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./RawArrayTests.o: ../include/mparsercontext.h ../include/mrcstring.h
../bld/./RawArrayTests.o: ../include/mrcstringfactory.h
../bld/./RawArrayTests.o: ../include/mstringfactory.h
../bld/./RawArrayTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./RawArrayTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./RawArrayTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./RawArrayTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./RawArrayTests.o: ../include/mtagparserlibrary.h
../bld/./RawArrayTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./RawArrayTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./RawArrayTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./RawListTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./RawListTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./RawListTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./RawListTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./RawListTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./RawListTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./RawListTests.o: ../include/merror.h ../include/mfilter.h
../bld/./RawListTests.o: ../include/mvar.h ../include/mstring.h
../bld/./RawListTests.o: ../include/mfilterlibrary.h ../include/mfilternode.h
../bld/./RawListTests.o: ../include/mfreetext.h ../include/mnode.h
../bld/./RawListTests.o: ../include/minputsource.h ../include/mlinkedlist.h
../bld/./RawListTests.o: ../include/mnodelist.h ../include/mnumber.h
../bld/./RawListTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./RawListTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./RawListTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./RawListTests.o: ../include/mstringfactory.h
../bld/./RawListTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./RawListTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./RawListTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./RawListTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./RawListTests.o: ../include/mtagparserlibrary.h
../bld/./RawListTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./RawListTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./RawListTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./RawListTests.o: ../include/ext/mangoextpub.h
../bld/./RawListTests.o: ../include/ext/mfortag.h stlinputsource.h
../bld/./RawListTests.o: ../include/ext/maddfilter.h
../bld/./ResolverTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./ResolverTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ResolverTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./ResolverTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./ResolverTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ResolverTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./ResolverTests.o: ../include/merror.h ../include/mfilter.h
../bld/./ResolverTests.o: ../include/mvar.h ../include/mstring.h
../bld/./ResolverTests.o: ../include/mfilterlibrary.h
../bld/./ResolverTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ResolverTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ResolverTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./ResolverTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./ResolverTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./ResolverTests.o: ../include/mparsercontext.h ../include/mrcstring.h
../bld/./ResolverTests.o: ../include/mrcstringfactory.h
../bld/./ResolverTests.o: ../include/mstringfactory.h
../bld/./ResolverTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./ResolverTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./ResolverTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./ResolverTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ResolverTests.o: ../include/mtagparserlibrary.h
../bld/./ResolverTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ResolverTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./ResolverTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./ResolverTests.o: stlinputsource.h
../bld/./stlinputsource.o: stlinputsource.h ../include/mangopub.h
../bld/./stlinputsource.o: ../include/mrawarray.h ../include/mobject.h
../bld/./stlinputsource.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./stlinputsource.o: ../include/mutils.h ../include/mrawlist.h
../bld/./stlinputsource.o: ../include/marraylist.h ../include/mlist.h
../bld/./stlinputsource.o: ../include/mcollection.h ../include/mbintree.h
../bld/./stlinputsource.o: ../include/mclasses.h ../include/merror.h
../bld/./stlinputsource.o: ../include/mfilter.h ../include/mvar.h
../bld/./stlinputsource.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./stlinputsource.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./stlinputsource.o: ../include/mnode.h ../include/minputsource.h
../bld/./stlinputsource.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./stlinputsource.o: ../include/mnumber.h ../include/mparser.h
../bld/./stlinputsource.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./stlinputsource.o: ../include/mparsercontext.h ../include/mrcstring.h
../bld/./stlinputsource.o: ../include/mrcstringfactory.h
../bld/./stlinputsource.o: ../include/mstringfactory.h
../bld/./stlinputsource.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./stlinputsource.o: ../include/msingletons.h
../bld/./stlinputsource.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./stlinputsource.o: ../include/mtreetable.h ../include/mtagnode.h
../bld/./stlinputsource.o: ../include/mtagparser.h
../bld/./stlinputsource.o: ../include/mtagparserlibrary.h
../bld/./stlinputsource.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./stlinputsource.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./stlinputsource.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./StringTableTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./StringTableTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./StringTableTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./StringTableTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./StringTableTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./StringTableTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./StringTableTests.o: ../include/merror.h ../include/mfilter.h
../bld/./StringTableTests.o: ../include/mvar.h ../include/mstring.h
../bld/./StringTableTests.o: ../include/mfilterlibrary.h
../bld/./StringTableTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./StringTableTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./StringTableTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./StringTableTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./StringTableTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./StringTableTests.o: ../include/mparsercontext.h
../bld/./StringTableTests.o: ../include/mrcstring.h
../bld/./StringTableTests.o: ../include/mrcstringfactory.h
../bld/./StringTableTests.o: ../include/mstringfactory.h
../bld/./StringTableTests.o: ../include/mrcstringtable.h
../bld/./StringTableTests.o: ../include/mrenderer.h ../include/msingletons.h
../bld/./StringTableTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./StringTableTests.o: ../include/mtreetable.h ../include/mtagnode.h
../bld/./StringTableTests.o: ../include/mtagparser.h
../bld/./StringTableTests.o: ../include/mtagparserlibrary.h
../bld/./StringTableTests.o: ../include/mtemplateloader.h
../bld/./StringTableTests.o: ../include/mtmplctx.h ../include/mtokenlists.h
../bld/./StringTableTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./StringTableTests.o: ../include/mvarresolver.h stlinputsource.h
../bld/./TemplateContextTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./TemplateContextTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./TemplateContextTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./TemplateContextTests.o: ../include/mrawlist.h
../bld/./TemplateContextTests.o: ../include/marraylist.h ../include/mlist.h
../bld/./TemplateContextTests.o: ../include/mcollection.h
../bld/./TemplateContextTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./TemplateContextTests.o: ../include/merror.h ../include/mfilter.h
../bld/./TemplateContextTests.o: ../include/mvar.h ../include/mstring.h
../bld/./TemplateContextTests.o: ../include/mfilterlibrary.h
../bld/./TemplateContextTests.o: ../include/mfilternode.h
../bld/./TemplateContextTests.o: ../include/mfreetext.h ../include/mnode.h
../bld/./TemplateContextTests.o: ../include/minputsource.h
../bld/./TemplateContextTests.o: ../include/mlinkedlist.h
../bld/./TemplateContextTests.o: ../include/mnodelist.h ../include/mnumber.h
../bld/./TemplateContextTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./TemplateContextTests.o: ../include/mtoken.h
../bld/./TemplateContextTests.o: ../include/mparsercontext.h
../bld/./TemplateContextTests.o: ../include/mrcstring.h
../bld/./TemplateContextTests.o: ../include/mrcstringfactory.h
../bld/./TemplateContextTests.o: ../include/mstringfactory.h
../bld/./TemplateContextTests.o: ../include/mrcstringtable.h
../bld/./TemplateContextTests.o: ../include/mrenderer.h
../bld/./TemplateContextTests.o: ../include/msingletons.h
../bld/./TemplateContextTests.o: ../include/mstringbuffer.h
../bld/./TemplateContextTests.o: ../include/mtable.h ../include/mtreetable.h
../bld/./TemplateContextTests.o: ../include/mtagnode.h
../bld/./TemplateContextTests.o: ../include/mtagparser.h
../bld/./TemplateContextTests.o: ../include/mtagparserlibrary.h
../bld/./TemplateContextTests.o: ../include/mtemplateloader.h
../bld/./TemplateContextTests.o: ../include/mtmplctx.h
../bld/./TemplateContextTests.o: ../include/mtokenlists.h
../bld/./TemplateContextTests.o: ../include/mvarlibrary.h
../bld/./TemplateContextTests.o: ../include/mvarnode.h
../bld/./TemplateContextTests.o: ../include/mvarresolver.h stlinputsource.h
../bld/./TokenizerTests.o: ../include/mangopub.h ../include/mrawarray.h
../bld/./TokenizerTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./TokenizerTests.o: ../include/mmemutils.h ../include/mutils.h
../bld/./TokenizerTests.o: ../include/mrawlist.h ../include/marraylist.h
../bld/./TokenizerTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./TokenizerTests.o: ../include/mbintree.h ../include/mclasses.h
../bld/./TokenizerTests.o: ../include/merror.h ../include/mfilter.h
../bld/./TokenizerTests.o: ../include/mvar.h ../include/mstring.h
../bld/./TokenizerTests.o: ../include/mfilterlibrary.h
../bld/./TokenizerTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./TokenizerTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./TokenizerTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./TokenizerTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./TokenizerTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./TokenizerTests.o: ../include/mparsercontext.h ../include/mrcstring.h
../bld/./TokenizerTests.o: ../include/mrcstringfactory.h
../bld/./TokenizerTests.o: ../include/mstringfactory.h
../bld/./TokenizerTests.o: ../include/mrcstringtable.h ../include/mrenderer.h
../bld/./TokenizerTests.o: ../include/msingletons.h
../bld/./TokenizerTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./TokenizerTests.o: ../include/mtreetable.h ../include/mtagnode.h
../bld/./TokenizerTests.o: ../include/mtagparser.h
../bld/./TokenizerTests.o: ../include/mtagparserlibrary.h
../bld/./TokenizerTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./TokenizerTests.o: ../include/mtokenlists.h ../include/mvarlibrary.h
../bld/./TokenizerTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./TokenizerTests.o: stlinputsource.h

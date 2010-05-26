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

../bld/./ArrayTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./ArrayTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ArrayTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ArrayTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ArrayTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ArrayTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ArrayTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ArrayTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ArrayTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ArrayTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./ArrayTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./ArrayTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ArrayTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ArrayTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./ArrayTests.o: ../include/mstringfactory.h
../bld/./ArrayTests.o: ../include/mrcstringtable.h ../include/msingletons.h
../bld/./ArrayTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ArrayTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ArrayTests.o: ../include/mtagparserlibrary.h
../bld/./ArrayTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ArrayTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ArrayTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ArrayTests.o: ../include/mvarresolver.h
../bld/./BinTreeTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./BinTreeTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./BinTreeTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./BinTreeTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./BinTreeTests.o: ../include/mclasses.h ../include/merror.h
../bld/./BinTreeTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./BinTreeTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./BinTreeTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./BinTreeTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./BinTreeTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./BinTreeTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./BinTreeTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./BinTreeTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./BinTreeTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./BinTreeTests.o: ../include/mstringfactory.h
../bld/./BinTreeTests.o: ../include/mrcstringtable.h ../include/msingletons.h
../bld/./BinTreeTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./BinTreeTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./BinTreeTests.o: ../include/mtagparserlibrary.h
../bld/./BinTreeTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./BinTreeTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./BinTreeTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./BinTreeTests.o: ../include/mvarresolver.h
../bld/./ListTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./ListTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ListTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ListTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ListTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ListTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ListTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ListTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ListTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ListTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./ListTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./ListTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ListTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ListTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./ListTests.o: ../include/mstringfactory.h ../include/mrcstringtable.h
../bld/./ListTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./ListTests.o: ../include/mtable.h ../include/mtagnode.h
../bld/./ListTests.o: ../include/mtagparser.h ../include/mtagparserlibrary.h
../bld/./ListTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ListTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ListTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ListTests.o: ../include/mvarresolver.h ../include/ext/mangoextpub.h
../bld/./ListTests.o: ../include/ext/mfortag.h stlinputsource.h
../bld/./ListTests.o: ../include/maddfilter.h
../bld/./ObjectTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./ObjectTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ObjectTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ObjectTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ObjectTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ObjectTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ObjectTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ObjectTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ObjectTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ObjectTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./ObjectTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./ObjectTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ObjectTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ObjectTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./ObjectTests.o: ../include/mstringfactory.h
../bld/./ObjectTests.o: ../include/mrcstringtable.h ../include/msingletons.h
../bld/./ObjectTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ObjectTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ObjectTests.o: ../include/mtagparserlibrary.h
../bld/./ObjectTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ObjectTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ObjectTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ObjectTests.o: ../include/mvarresolver.h stlinputsource.h
../bld/./ParserTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./ParserTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ParserTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ParserTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ParserTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ParserTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ParserTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ParserTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ParserTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ParserTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./ParserTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./ParserTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ParserTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ParserTests.o: ../include/mrcstring.h ../include/mrcstringfactory.h
../bld/./ParserTests.o: ../include/mstringfactory.h
../bld/./ParserTests.o: ../include/mrcstringtable.h ../include/msingletons.h
../bld/./ParserTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ParserTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ParserTests.o: ../include/mtagparserlibrary.h
../bld/./ParserTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ParserTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ParserTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ParserTests.o: ../include/mvarresolver.h
../bld/./ParserTests.o: ../include/ext/mangoextpub.h ../include/ext/mfortag.h
../bld/./ParserTests.o: stlinputsource.h ../include/maddfilter.h
../bld/./ResolverTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./ResolverTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./ResolverTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ResolverTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ResolverTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ResolverTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ResolverTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ResolverTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ResolverTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ResolverTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./ResolverTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./ResolverTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ResolverTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ResolverTests.o: ../include/mrcstring.h
../bld/./ResolverTests.o: ../include/mrcstringfactory.h
../bld/./ResolverTests.o: ../include/mstringfactory.h
../bld/./ResolverTests.o: ../include/mrcstringtable.h
../bld/./ResolverTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./ResolverTests.o: ../include/mtable.h ../include/mtagnode.h
../bld/./ResolverTests.o: ../include/mtagparser.h
../bld/./ResolverTests.o: ../include/mtagparserlibrary.h
../bld/./ResolverTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ResolverTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ResolverTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ResolverTests.o: ../include/mvarresolver.h stlinputsource.h
../bld/./stlinputsource.o: stlinputsource.h ../include/mangopub.h
../bld/./stlinputsource.o: ../include/marraylist.h ../include/mlist.h
../bld/./stlinputsource.o: ../include/mcollection.h ../include/mobject.h
../bld/./stlinputsource.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./stlinputsource.o: ../include/mbintree.h ../include/mclasses.h
../bld/./stlinputsource.o: ../include/merror.h ../include/mfilter.h
../bld/./stlinputsource.o: ../include/mvar.h ../include/mstring.h
../bld/./stlinputsource.o: ../include/mfilterlibrary.h
../bld/./stlinputsource.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./stlinputsource.o: ../include/mnode.h ../include/minputsource.h
../bld/./stlinputsource.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./stlinputsource.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./stlinputsource.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./stlinputsource.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./stlinputsource.o: ../include/mrcstring.h
../bld/./stlinputsource.o: ../include/mrcstringfactory.h
../bld/./stlinputsource.o: ../include/mstringfactory.h
../bld/./stlinputsource.o: ../include/mrcstringtable.h
../bld/./stlinputsource.o: ../include/msingletons.h
../bld/./stlinputsource.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./stlinputsource.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./stlinputsource.o: ../include/mtagparserlibrary.h
../bld/./stlinputsource.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./stlinputsource.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./stlinputsource.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./stlinputsource.o: ../include/mvarresolver.h
../bld/./StringTableTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./StringTableTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./StringTableTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./StringTableTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./StringTableTests.o: ../include/mclasses.h ../include/merror.h
../bld/./StringTableTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./StringTableTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./StringTableTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./StringTableTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./StringTableTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./StringTableTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./StringTableTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./StringTableTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./StringTableTests.o: ../include/mrcstring.h
../bld/./StringTableTests.o: ../include/mrcstringfactory.h
../bld/./StringTableTests.o: ../include/mstringfactory.h
../bld/./StringTableTests.o: ../include/mrcstringtable.h
../bld/./StringTableTests.o: ../include/msingletons.h
../bld/./StringTableTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./StringTableTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./StringTableTests.o: ../include/mtagparserlibrary.h
../bld/./StringTableTests.o: ../include/mtemplateloader.h
../bld/./StringTableTests.o: ../include/mtmplctx.h ../include/mtokenlists.h
../bld/./StringTableTests.o: ../include/mutils.h ../include/mvarlibrary.h
../bld/./StringTableTests.o: ../include/mvarnode.h ../include/mvarresolver.h
../bld/./StringTableTests.o: stlinputsource.h
../bld/./TokenizerTests.o: ../include/mangopub.h ../include/marraylist.h
../bld/./TokenizerTests.o: ../include/mlist.h ../include/mcollection.h
../bld/./TokenizerTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./TokenizerTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./TokenizerTests.o: ../include/mclasses.h ../include/merror.h
../bld/./TokenizerTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./TokenizerTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./TokenizerTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./TokenizerTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./TokenizerTests.o: ../include/mlinkedlist.h ../include/mnodelist.h
../bld/./TokenizerTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./TokenizerTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./TokenizerTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./TokenizerTests.o: ../include/mrcstring.h
../bld/./TokenizerTests.o: ../include/mrcstringfactory.h
../bld/./TokenizerTests.o: ../include/mstringfactory.h
../bld/./TokenizerTests.o: ../include/mrcstringtable.h
../bld/./TokenizerTests.o: ../include/msingletons.h
../bld/./TokenizerTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./TokenizerTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./TokenizerTests.o: ../include/mtagparserlibrary.h
../bld/./TokenizerTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./TokenizerTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./TokenizerTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./TokenizerTests.o: ../include/mvarresolver.h stlinputsource.h

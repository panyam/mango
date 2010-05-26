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

../bld/./ArrayTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./ArrayTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./ArrayTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./ArrayTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./ArrayTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ArrayTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ArrayTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ArrayTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ArrayTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ArrayTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./ArrayTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./ArrayTests.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./ArrayTests.o: ../include/mrawlist.h ../include/mrcstring.h
../bld/./ArrayTests.o: ../include/mrcstringfactory.h
../bld/./ArrayTests.o: ../include/mstringfactory.h
../bld/./ArrayTests.o: ../include/mrcstringtable.h ../include/msingletons.h
../bld/./ArrayTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ArrayTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ArrayTests.o: ../include/mtagparserlibrary.h
../bld/./ArrayTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ArrayTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ArrayTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ArrayTests.o: ../include/mvarresolver.h
../bld/./BinTreeTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./BinTreeTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./BinTreeTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./BinTreeTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./BinTreeTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./BinTreeTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./BinTreeTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./BinTreeTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./BinTreeTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./BinTreeTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./BinTreeTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./BinTreeTests.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./BinTreeTests.o: ../include/mrawlist.h ../include/mrcstring.h
../bld/./BinTreeTests.o: ../include/mrcstringfactory.h
../bld/./BinTreeTests.o: ../include/mstringfactory.h
../bld/./BinTreeTests.o: ../include/mrcstringtable.h ../include/msingletons.h
../bld/./BinTreeTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./BinTreeTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./BinTreeTests.o: ../include/mtagparserlibrary.h
../bld/./BinTreeTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./BinTreeTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./BinTreeTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./BinTreeTests.o: ../include/mvarresolver.h
../bld/./ListTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./ListTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./ListTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./ListTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./ListTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ListTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ListTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ListTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ListTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ListTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./ListTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./ListTests.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./ListTests.o: ../include/mrawlist.h ../include/mrcstring.h
../bld/./ListTests.o: ../include/mrcstringfactory.h
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
../bld/./ObjectTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./ObjectTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./ObjectTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./ObjectTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./ObjectTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ObjectTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ObjectTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ObjectTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ObjectTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ObjectTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./ObjectTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./ObjectTests.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./ObjectTests.o: ../include/mrawlist.h ../include/mrcstring.h
../bld/./ObjectTests.o: ../include/mrcstringfactory.h
../bld/./ObjectTests.o: ../include/mstringfactory.h
../bld/./ObjectTests.o: ../include/mrcstringtable.h ../include/msingletons.h
../bld/./ObjectTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ObjectTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ObjectTests.o: ../include/mtagparserlibrary.h
../bld/./ObjectTests.o: ../include/mtemplateloader.h ../include/mtmplctx.h
../bld/./ObjectTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ObjectTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ObjectTests.o: ../include/mvarresolver.h stlinputsource.h
../bld/./ParserTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./ParserTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./ParserTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./ParserTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./ParserTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ParserTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ParserTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ParserTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ParserTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ParserTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./ParserTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./ParserTests.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./ParserTests.o: ../include/mrawlist.h ../include/mrcstring.h
../bld/./ParserTests.o: ../include/mrcstringfactory.h
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
../bld/./ResolverTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./ResolverTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./ResolverTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./ResolverTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./ResolverTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ResolverTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ResolverTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ResolverTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ResolverTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ResolverTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./ResolverTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./ResolverTests.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./ResolverTests.o: ../include/mrawlist.h ../include/mrcstring.h
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
../bld/./stlinputsource.o: ../include/mbintree.h ../include/mfwddefs.h
../bld/./stlinputsource.o: ../include/mclasses.h ../include/mcollection.h
../bld/./stlinputsource.o: ../include/mobject.h ../include/mmemutils.h
../bld/./stlinputsource.o: ../include/merror.h ../include/mfilter.h
../bld/./stlinputsource.o: ../include/mvar.h ../include/mstring.h
../bld/./stlinputsource.o: ../include/mfilterlibrary.h
../bld/./stlinputsource.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./stlinputsource.o: ../include/mnode.h ../include/minputsource.h
../bld/./stlinputsource.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./stlinputsource.o: ../include/mnumber.h ../include/mparser.h
../bld/./stlinputsource.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./stlinputsource.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./stlinputsource.o: ../include/mrawlist.h ../include/mrcstring.h
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
../bld/./StringTableTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./StringTableTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./StringTableTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./StringTableTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./StringTableTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./StringTableTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./StringTableTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./StringTableTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./StringTableTests.o: ../include/mnodelist.h
../bld/./StringTableTests.o: ../include/mnoderenderer.h ../include/mnumber.h
../bld/./StringTableTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./StringTableTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./StringTableTests.o: ../include/mrawarray.h ../include/mrawlist.h
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
../bld/./TokenizerTests.o: ../include/mangopub.h ../include/mbintree.h
../bld/./TokenizerTests.o: ../include/mfwddefs.h ../include/mclasses.h
../bld/./TokenizerTests.o: ../include/mcollection.h ../include/mobject.h
../bld/./TokenizerTests.o: ../include/mmemutils.h ../include/merror.h
../bld/./TokenizerTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./TokenizerTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./TokenizerTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./TokenizerTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./TokenizerTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./TokenizerTests.o: ../include/mnumber.h ../include/mparser.h
../bld/./TokenizerTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./TokenizerTests.o: ../include/mparsercontext.h ../include/mrawarray.h
../bld/./TokenizerTests.o: ../include/mrawlist.h ../include/mrcstring.h
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

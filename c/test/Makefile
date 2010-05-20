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
	$(GPP) -I$(UNITTEST_PP_DIR)/src -c $(CFLAGS) $< -o $@

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

../bld/./ArrayTests.o: ../include/mangopub.h ../include/marray.h
../bld/./ArrayTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ArrayTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ArrayTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ArrayTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ArrayTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ArrayTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ArrayTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ArrayTests.o: ../include/mlibrary.h ../include/mlist.h
../bld/./ArrayTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ArrayTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ArrayTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ArrayTests.o: ../include/mrcstring.h ../include/mrcstringtable.h
../bld/./ArrayTests.o: ../include/mrcstringfactory.h
../bld/./ArrayTests.o: ../include/mstringfactory.h ../include/msingletons.h
../bld/./ArrayTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ArrayTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ArrayTests.o: ../include/mtagparserlibrary.h
../bld/./ArrayTests.o: ../include/mtemplatecontext.h
../bld/./ArrayTests.o: ../include/mtemplateloader.h ../include/mtokenlists.h
../bld/./ArrayTests.o: ../include/mutils.h ../include/mvalue.h
../bld/./ArrayTests.o: ../include/mvarresolver.h ../include/mvarlibrary.h
../bld/./ArrayTests.o: ../include/mvarnode.h
../bld/./BinTreeTests.o: ../include/mangopub.h ../include/marray.h
../bld/./BinTreeTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./BinTreeTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./BinTreeTests.o: ../include/mclasses.h ../include/merror.h
../bld/./BinTreeTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./BinTreeTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./BinTreeTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./BinTreeTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./BinTreeTests.o: ../include/mlibrary.h ../include/mlist.h
../bld/./BinTreeTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./BinTreeTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./BinTreeTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./BinTreeTests.o: ../include/mrcstring.h ../include/mrcstringtable.h
../bld/./BinTreeTests.o: ../include/mrcstringfactory.h
../bld/./BinTreeTests.o: ../include/mstringfactory.h ../include/msingletons.h
../bld/./BinTreeTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./BinTreeTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./BinTreeTests.o: ../include/mtagparserlibrary.h
../bld/./BinTreeTests.o: ../include/mtemplatecontext.h
../bld/./BinTreeTests.o: ../include/mtemplateloader.h
../bld/./BinTreeTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./BinTreeTests.o: ../include/mvalue.h ../include/mvarresolver.h
../bld/./BinTreeTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ObjectTests.o: ../include/mangopub.h ../include/marray.h
../bld/./ObjectTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ObjectTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ObjectTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ObjectTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ObjectTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ObjectTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ObjectTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ObjectTests.o: ../include/mlibrary.h ../include/mlist.h
../bld/./ObjectTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ObjectTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ObjectTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ObjectTests.o: ../include/mrcstring.h ../include/mrcstringtable.h
../bld/./ObjectTests.o: ../include/mrcstringfactory.h
../bld/./ObjectTests.o: ../include/mstringfactory.h ../include/msingletons.h
../bld/./ObjectTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ObjectTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ObjectTests.o: ../include/mtagparserlibrary.h
../bld/./ObjectTests.o: ../include/mtemplatecontext.h
../bld/./ObjectTests.o: ../include/mtemplateloader.h ../include/mtokenlists.h
../bld/./ObjectTests.o: ../include/mutils.h ../include/mvalue.h
../bld/./ObjectTests.o: ../include/mvarresolver.h ../include/mvarlibrary.h
../bld/./ObjectTests.o: ../include/mvarnode.h stlinputsource.h
../bld/./ParserTests.o: ../include/mangopub.h ../include/marray.h
../bld/./ParserTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ParserTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ParserTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ParserTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ParserTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ParserTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ParserTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ParserTests.o: ../include/mlibrary.h ../include/mlist.h
../bld/./ParserTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ParserTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ParserTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ParserTests.o: ../include/mrcstring.h ../include/mrcstringtable.h
../bld/./ParserTests.o: ../include/mrcstringfactory.h
../bld/./ParserTests.o: ../include/mstringfactory.h ../include/msingletons.h
../bld/./ParserTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./ParserTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./ParserTests.o: ../include/mtagparserlibrary.h
../bld/./ParserTests.o: ../include/mtemplatecontext.h
../bld/./ParserTests.o: ../include/mtemplateloader.h ../include/mtokenlists.h
../bld/./ParserTests.o: ../include/mutils.h ../include/mvalue.h
../bld/./ParserTests.o: ../include/mvarresolver.h ../include/mvarlibrary.h
../bld/./ParserTests.o: ../include/mvarnode.h stlinputsource.h
../bld/./ParserTests.o: ../include/maddfilter.h
../bld/./ResolverTests.o: ../include/mangopub.h ../include/marray.h
../bld/./ResolverTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./ResolverTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./ResolverTests.o: ../include/mclasses.h ../include/merror.h
../bld/./ResolverTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./ResolverTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./ResolverTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./ResolverTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./ResolverTests.o: ../include/mlibrary.h ../include/mlist.h
../bld/./ResolverTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./ResolverTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./ResolverTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./ResolverTests.o: ../include/mrcstring.h ../include/mrcstringtable.h
../bld/./ResolverTests.o: ../include/mrcstringfactory.h
../bld/./ResolverTests.o: ../include/mstringfactory.h
../bld/./ResolverTests.o: ../include/msingletons.h ../include/mstringbuffer.h
../bld/./ResolverTests.o: ../include/mtable.h ../include/mtagnode.h
../bld/./ResolverTests.o: ../include/mtagparser.h
../bld/./ResolverTests.o: ../include/mtagparserlibrary.h
../bld/./ResolverTests.o: ../include/mtemplatecontext.h
../bld/./ResolverTests.o: ../include/mtemplateloader.h
../bld/./ResolverTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./ResolverTests.o: ../include/mvalue.h ../include/mvarresolver.h
../bld/./ResolverTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./ResolverTests.o: stlinputsource.h
../bld/./stlinputsource.o: stlinputsource.h ../include/mangopub.h
../bld/./stlinputsource.o: ../include/marray.h ../include/mobject.h
../bld/./stlinputsource.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./stlinputsource.o: ../include/mbintree.h ../include/mclasses.h
../bld/./stlinputsource.o: ../include/merror.h ../include/mfilter.h
../bld/./stlinputsource.o: ../include/mvar.h ../include/mstring.h
../bld/./stlinputsource.o: ../include/mfilterlibrary.h
../bld/./stlinputsource.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./stlinputsource.o: ../include/mnode.h ../include/minputsource.h
../bld/./stlinputsource.o: ../include/mlibrary.h ../include/mlist.h
../bld/./stlinputsource.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./stlinputsource.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./stlinputsource.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./stlinputsource.o: ../include/mrcstring.h ../include/mrcstringtable.h
../bld/./stlinputsource.o: ../include/mrcstringfactory.h
../bld/./stlinputsource.o: ../include/mstringfactory.h
../bld/./stlinputsource.o: ../include/msingletons.h
../bld/./stlinputsource.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./stlinputsource.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./stlinputsource.o: ../include/mtagparserlibrary.h
../bld/./stlinputsource.o: ../include/mtemplatecontext.h
../bld/./stlinputsource.o: ../include/mtemplateloader.h
../bld/./stlinputsource.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./stlinputsource.o: ../include/mvalue.h ../include/mvarresolver.h
../bld/./stlinputsource.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./StringTableTests.o: ../include/mangopub.h ../include/marray.h
../bld/./StringTableTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./StringTableTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./StringTableTests.o: ../include/mclasses.h ../include/merror.h
../bld/./StringTableTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./StringTableTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./StringTableTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./StringTableTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./StringTableTests.o: ../include/mlibrary.h ../include/mlist.h
../bld/./StringTableTests.o: ../include/mnodelist.h
../bld/./StringTableTests.o: ../include/mnoderenderer.h ../include/mparser.h
../bld/./StringTableTests.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./StringTableTests.o: ../include/mparsercontext.h
../bld/./StringTableTests.o: ../include/mrcstring.h
../bld/./StringTableTests.o: ../include/mrcstringtable.h
../bld/./StringTableTests.o: ../include/mrcstringfactory.h
../bld/./StringTableTests.o: ../include/mstringfactory.h
../bld/./StringTableTests.o: ../include/msingletons.h
../bld/./StringTableTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./StringTableTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./StringTableTests.o: ../include/mtagparserlibrary.h
../bld/./StringTableTests.o: ../include/mtemplatecontext.h
../bld/./StringTableTests.o: ../include/mtemplateloader.h
../bld/./StringTableTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./StringTableTests.o: ../include/mvalue.h ../include/mvarresolver.h
../bld/./StringTableTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./StringTableTests.o: stlinputsource.h
../bld/./TokenizerTests.o: ../include/mangopub.h ../include/marray.h
../bld/./TokenizerTests.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./TokenizerTests.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./TokenizerTests.o: ../include/mclasses.h ../include/merror.h
../bld/./TokenizerTests.o: ../include/mfilter.h ../include/mvar.h
../bld/./TokenizerTests.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./TokenizerTests.o: ../include/mfilternode.h ../include/mfreetext.h
../bld/./TokenizerTests.o: ../include/mnode.h ../include/minputsource.h
../bld/./TokenizerTests.o: ../include/mlibrary.h ../include/mlist.h
../bld/./TokenizerTests.o: ../include/mnodelist.h ../include/mnoderenderer.h
../bld/./TokenizerTests.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./TokenizerTests.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./TokenizerTests.o: ../include/mrcstring.h ../include/mrcstringtable.h
../bld/./TokenizerTests.o: ../include/mrcstringfactory.h
../bld/./TokenizerTests.o: ../include/mstringfactory.h
../bld/./TokenizerTests.o: ../include/msingletons.h
../bld/./TokenizerTests.o: ../include/mstringbuffer.h ../include/mtable.h
../bld/./TokenizerTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./TokenizerTests.o: ../include/mtagparserlibrary.h
../bld/./TokenizerTests.o: ../include/mtemplatecontext.h
../bld/./TokenizerTests.o: ../include/mtemplateloader.h
../bld/./TokenizerTests.o: ../include/mtokenlists.h ../include/mutils.h
../bld/./TokenizerTests.o: ../include/mvalue.h ../include/mvarresolver.h
../bld/./TokenizerTests.o: ../include/mvarlibrary.h ../include/mvarnode.h
../bld/./TokenizerTests.o: stlinputsource.h

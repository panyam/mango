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
	makedepend -Y -p"$(OUTPUT_DIR)/" -I../include   -- $(TEST_SOURCES)
# DO NOT DELETE

../bld/./ArrayTests.o: ../include/mangopub.h ../include/mfwddefs.h
../bld/./ArrayTests.o: ../include/mobject.h ../include/mprototype.h
../bld/./ArrayTests.o: ../include/mmemutils.h ../include/mclasses.h
../bld/./ArrayTests.o: ../include/mtoken.h ../include/mtokenlists.h
../bld/./ArrayTests.o: ../include/mtokenizer.h ../include/mparser.h
../bld/./ArrayTests.o: ../include/merror.h ../include/mlist.h
../bld/./ArrayTests.o: ../include/marray.h ../include/mbintree.h
../bld/./ArrayTests.o: ../include/mfilterlibrary.h ../include/mvarlibrary.h
../bld/./ArrayTests.o: ../include/mtagparserlibrary.h ../include/mtagnode.h
../bld/./ArrayTests.o: ../include/mtagparser.h ../include/mlibrary.h
../bld/./ArrayTests.o: ../include/minputsource.h ../include/mstring.h
../bld/./ArrayTests.o: ../include/mstringbuffer.h ../include/mstringtable.h
../bld/./ArrayTests.o: ../include/mfreetext.h ../include/mtemplateloader.h
../bld/./ArrayTests.o: ../include/mtemplatecontext.h ../include/mnode.h
../bld/./ArrayTests.o: ../include/mnodelist.h ../include/mvariable.h
../bld/./ArrayTests.o: ../include/mvarnode.h ../include/mfilter.h
../bld/./ArrayTests.o: ../include/mfilternode.h ../include/msingletons.h
../bld/./ArrayTests.o: ../include/mutils.h ../include/mstring2.h
../bld/./ArrayTests.o: stlinputsource.h ../include/maddfilter.h
../bld/./ParserTests.o: ../include/mangopub.h ../include/mfwddefs.h
../bld/./ParserTests.o: ../include/mobject.h ../include/mprototype.h
../bld/./ParserTests.o: ../include/mmemutils.h ../include/mclasses.h
../bld/./ParserTests.o: ../include/mtoken.h ../include/mtokenlists.h
../bld/./ParserTests.o: ../include/mtokenizer.h ../include/mparser.h
../bld/./ParserTests.o: ../include/merror.h ../include/mlist.h
../bld/./ParserTests.o: ../include/marray.h ../include/mbintree.h
../bld/./ParserTests.o: ../include/mfilterlibrary.h ../include/mvarlibrary.h
../bld/./ParserTests.o: ../include/mtagparserlibrary.h ../include/mtagnode.h
../bld/./ParserTests.o: ../include/mtagparser.h ../include/mlibrary.h
../bld/./ParserTests.o: ../include/minputsource.h ../include/mstring.h
../bld/./ParserTests.o: ../include/mstringbuffer.h ../include/mstringtable.h
../bld/./ParserTests.o: ../include/mfreetext.h ../include/mtemplateloader.h
../bld/./ParserTests.o: ../include/mtemplatecontext.h ../include/mnode.h
../bld/./ParserTests.o: ../include/mnodelist.h ../include/mvariable.h
../bld/./ParserTests.o: ../include/mvarnode.h ../include/mfilter.h
../bld/./ParserTests.o: ../include/mfilternode.h ../include/msingletons.h
../bld/./ParserTests.o: ../include/mutils.h ../include/mstring2.h
../bld/./ParserTests.o: stlinputsource.h ../include/maddfilter.h
../bld/./stlinputsource.o: stlinputsource.h ../include/mangopub.h
../bld/./stlinputsource.o: ../include/mfwddefs.h ../include/mobject.h
../bld/./stlinputsource.o: ../include/mprototype.h ../include/mmemutils.h
../bld/./stlinputsource.o: ../include/mclasses.h ../include/mtoken.h
../bld/./stlinputsource.o: ../include/mtokenlists.h ../include/mtokenizer.h
../bld/./stlinputsource.o: ../include/mparser.h ../include/merror.h
../bld/./stlinputsource.o: ../include/mlist.h ../include/marray.h
../bld/./stlinputsource.o: ../include/mbintree.h ../include/mfilterlibrary.h
../bld/./stlinputsource.o: ../include/mvarlibrary.h
../bld/./stlinputsource.o: ../include/mtagparserlibrary.h
../bld/./stlinputsource.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./stlinputsource.o: ../include/mlibrary.h ../include/minputsource.h
../bld/./stlinputsource.o: ../include/mstring.h ../include/mstringbuffer.h
../bld/./stlinputsource.o: ../include/mstringtable.h ../include/mfreetext.h
../bld/./stlinputsource.o: ../include/mtemplateloader.h
../bld/./stlinputsource.o: ../include/mtemplatecontext.h ../include/mnode.h
../bld/./stlinputsource.o: ../include/mnodelist.h ../include/mvariable.h
../bld/./stlinputsource.o: ../include/mvarnode.h ../include/mfilter.h
../bld/./stlinputsource.o: ../include/mfilternode.h ../include/msingletons.h
../bld/./stlinputsource.o: ../include/mutils.h
../bld/./StringTableTests.o: ../include/mangopub.h ../include/mfwddefs.h
../bld/./StringTableTests.o: ../include/mobject.h ../include/mprototype.h
../bld/./StringTableTests.o: ../include/mmemutils.h ../include/mclasses.h
../bld/./StringTableTests.o: ../include/mtoken.h ../include/mtokenlists.h
../bld/./StringTableTests.o: ../include/mtokenizer.h ../include/mparser.h
../bld/./StringTableTests.o: ../include/merror.h ../include/mlist.h
../bld/./StringTableTests.o: ../include/marray.h ../include/mbintree.h
../bld/./StringTableTests.o: ../include/mfilterlibrary.h
../bld/./StringTableTests.o: ../include/mvarlibrary.h
../bld/./StringTableTests.o: ../include/mtagparserlibrary.h
../bld/./StringTableTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./StringTableTests.o: ../include/mlibrary.h ../include/minputsource.h
../bld/./StringTableTests.o: ../include/mstring.h ../include/mstringbuffer.h
../bld/./StringTableTests.o: ../include/mstringtable.h ../include/mfreetext.h
../bld/./StringTableTests.o: ../include/mtemplateloader.h
../bld/./StringTableTests.o: ../include/mtemplatecontext.h ../include/mnode.h
../bld/./StringTableTests.o: ../include/mnodelist.h ../include/mvariable.h
../bld/./StringTableTests.o: ../include/mvarnode.h ../include/mfilter.h
../bld/./StringTableTests.o: ../include/mfilternode.h
../bld/./StringTableTests.o: ../include/msingletons.h ../include/mutils.h
../bld/./StringTableTests.o: stlinputsource.h
../bld/./StringTests.o: ../include/mangopub.h ../include/mfwddefs.h
../bld/./StringTests.o: ../include/mobject.h ../include/mprototype.h
../bld/./StringTests.o: ../include/mmemutils.h ../include/mclasses.h
../bld/./StringTests.o: ../include/mtoken.h ../include/mtokenlists.h
../bld/./StringTests.o: ../include/mtokenizer.h ../include/mparser.h
../bld/./StringTests.o: ../include/merror.h ../include/mlist.h
../bld/./StringTests.o: ../include/marray.h ../include/mbintree.h
../bld/./StringTests.o: ../include/mfilterlibrary.h ../include/mvarlibrary.h
../bld/./StringTests.o: ../include/mtagparserlibrary.h ../include/mtagnode.h
../bld/./StringTests.o: ../include/mtagparser.h ../include/mlibrary.h
../bld/./StringTests.o: ../include/minputsource.h ../include/mstring.h
../bld/./StringTests.o: ../include/mstringbuffer.h ../include/mstringtable.h
../bld/./StringTests.o: ../include/mfreetext.h ../include/mtemplateloader.h
../bld/./StringTests.o: ../include/mtemplatecontext.h ../include/mnode.h
../bld/./StringTests.o: ../include/mnodelist.h ../include/mvariable.h
../bld/./StringTests.o: ../include/mvarnode.h ../include/mfilter.h
../bld/./StringTests.o: ../include/mfilternode.h ../include/msingletons.h
../bld/./StringTests.o: ../include/mutils.h
../bld/./TokenizerTests.o: ../include/mangopub.h ../include/mfwddefs.h
../bld/./TokenizerTests.o: ../include/mobject.h ../include/mprototype.h
../bld/./TokenizerTests.o: ../include/mmemutils.h ../include/mclasses.h
../bld/./TokenizerTests.o: ../include/mtoken.h ../include/mtokenlists.h
../bld/./TokenizerTests.o: ../include/mtokenizer.h ../include/mparser.h
../bld/./TokenizerTests.o: ../include/merror.h ../include/mlist.h
../bld/./TokenizerTests.o: ../include/marray.h ../include/mbintree.h
../bld/./TokenizerTests.o: ../include/mfilterlibrary.h
../bld/./TokenizerTests.o: ../include/mvarlibrary.h
../bld/./TokenizerTests.o: ../include/mtagparserlibrary.h
../bld/./TokenizerTests.o: ../include/mtagnode.h ../include/mtagparser.h
../bld/./TokenizerTests.o: ../include/mlibrary.h ../include/minputsource.h
../bld/./TokenizerTests.o: ../include/mstring.h ../include/mstringbuffer.h
../bld/./TokenizerTests.o: ../include/mstringtable.h ../include/mfreetext.h
../bld/./TokenizerTests.o: ../include/mtemplateloader.h
../bld/./TokenizerTests.o: ../include/mtemplatecontext.h ../include/mnode.h
../bld/./TokenizerTests.o: ../include/mnodelist.h ../include/mvariable.h
../bld/./TokenizerTests.o: ../include/mvarnode.h ../include/mfilter.h
../bld/./TokenizerTests.o: ../include/mfilternode.h ../include/msingletons.h
../bld/./TokenizerTests.o: ../include/mutils.h stlinputsource.h

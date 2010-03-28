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

../bld/./ParserTests.o: ../include/mangopub.h ../include/mfwddefs.h
../bld/./ParserTests.o: ../include/mtoken.h ../include/mtokenizer.h
../bld/./ParserTests.o: ../include/mparser.h ../include/mlibrary.h
../bld/./ParserTests.o: ../include/minputsource.h ../include/mstring.h
../bld/./ParserTests.o: ../include/mtemplateloader.h stlstringtoken.h
../bld/./ParserTests.o: stlinputsource.h
../bld/./stlinputsource.o: stlinputsource.h ../include/minputsource.h
../bld/./stlinputsource.o: ../include/mfwddefs.h
../bld/./stlstringtoken.o: ../include/mtoken.h ../include/mfwddefs.h
../bld/./stlstringtoken.o: stlstringtoken.h
../bld/./TokenizerTests.o: ../include/mangopub.h ../include/mfwddefs.h
../bld/./TokenizerTests.o: ../include/mtoken.h ../include/mtokenizer.h
../bld/./TokenizerTests.o: ../include/mparser.h ../include/mlibrary.h
../bld/./TokenizerTests.o: ../include/minputsource.h ../include/mstring.h
../bld/./TokenizerTests.o: ../include/mtemplateloader.h stlstringtoken.h
../bld/./TokenizerTests.o: stlinputsource.h

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

###############  DO NOT MODIFY BELOW THIS   ##############

SHARED_LIB_NAME         = lib$(PRODUCT_NAME).so.$(VERSION)
STATIC_LIB_NAME         = lib$(PRODUCT_NAME).a.$(VERSION)

ifeq ($(BUILD_MODE), debug)
    SHARED_LIB_NAME     = lib$(PRODUCT_NAME)_debug.so.$(VERSION)
    STATIC_LIB_NAME     = lib$(PRODUCT_NAME)_debug.a.$(VERSION)
endif

SHARED_LIB_OUTPUT       =   "$(OUTPUT_DIR)/$(SHARED_LIB_NAME)"
STATIC_LIB_OUTPUT       =   "$(OUTPUT_DIR)/$(STATIC_LIB_NAME)"

SOURCE_FOLDERS  =   .
MANGO_SOURCES   := $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.c))
MANGO_OBJS      = $(foreach obj, $(patsubst %.c,%.o,$(MANGO_SOURCES)), $(OUTPUT_DIR)/$(obj))
LIBS            = 

###################     Begin Targets       ######################

# Implicit rule to build .o into the build directory from .c
$(OUTPUT_DIR)/%.o : %.c
	@echo Building $@
	@$(GCC)  -std=c99 -c $(CFLAGS) $< -o $@

all: base static shared
	@echo LIB_INSTALL_DIR     = $(LIB_INSTALL_DIR)
	@echo INCLUDE_INSTALL_DIR = $(INCLUDE_INSTALL_DIR)

shared: base $(MANGO_OBJS)
	@echo Creating Shared Library ...
	@$(GPP) -shared $(CFLAGS) $(MANGO_OBJS) -o "$(SHARED_LIB_OUTPUT)" $(LIBS) -lstdc++
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).so"
	@ln -s "$(SHARED_LIB_NAME)" "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).so"

static: base $(MANGO_OBJS)
	@echo Creating Static Library ...
	@ar rcs "$(STATIC_LIB_OUTPUT)" $(MANGO_OBJS)
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).a"
	@ln -s "$(STATIC_LIB_NAME)" "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).a"

install: shared static
	@echo "Copying library files..."
	@mkdir -p "$(LIB_INSTALL_DIR)"
	@mkdir -p "$(INCLUDE_INSTALL_DIR)/lunarprobe"
	@cp -f "$(SHARED_LIB_OUTPUT)" "$(LIB_INSTALL_DIR)"
	@cp -f "$(STATIC_LIB_OUTPUT)" "$(LIB_INSTALL_DIR)"
	@rm -f "$(LIB_INSTALL_DIR)/lib$(PRODUCT_NAME).so"
	@ln -s "$(LIB_INSTALL_DIR)/$(SHARED_LIB_NAME)" "$(LIB_INSTALL_DIR)/lib$(PRODUCT_NAME).so"
	@echo "Copying header files..."
	@cp -f *.h $(INCLUDE_INSTALL_DIR)/lunarprobe

base:
	@echo Building output directories...
	@mkdir -p "$(OUTPUT_DIR)"
	@cd $(OUTPUT_DIR) ; mkdir -p $(SOURCE_FOLDERS)

.PHONY: clean cleanall distclean
clean:
	@rm -f $(MANGO_OBJS) $(ENTRY_OBJS)

cleanall: clean
	@rm -f "$(SHARED_LIB_OUTPUT)" "$(STATIC_LIB_OUTPUT)"
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).so"
	@rm -f "$(OUTPUT_DIR)/lib$(PRODUCT_NAME).a"

distclean: cleanall
	@rm -f Makefile

dep:
	makedepend -Y -p"$(OUTPUT_DIR)/" -I../include -- $(MANGO_SOURCES)

# DO NOT DELETE

../bld/./maddfilter.o: ../include/mfilter.h ../include/mfwddefs.h
../bld/./maddfilter.o: ../include/mvariable.h ../include/maddfilter.h
../bld/./marray.o: ../include/marray.h ../include/mfwddefs.h
../bld/./marray.o: ../include/mmemutils.h
../bld/./mbintree.o: ../include/mbintree.h ../include/mfwddefs.h
../bld/./mbintree.o: ../include/mmemutils.h
../bld/./mclasses.o: ../include/mclasses.h ../include/mfwddefs.h
../bld/./mclasses.o: ../include/mbintree.h ../include/mmemutils.h
../bld/./merror.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mfilter.o: ../include/mmemutils.h ../include/mfwddefs.h
../bld/./mfilter.o: ../include/mfilter.h ../include/mvariable.h
../bld/./mfilterlibrary.o: ../include/mfilterlibrary.h ../include/mfwddefs.h
../bld/./mfilterlibrary.o: ../include/mbintree.h ../include/mmemutils.h
../bld/./mfilterlibrary.o: ../include/mfilter.h ../include/mvariable.h
../bld/./mfilterlibrary.o: ../include/mstring.h ../include/mobject.h
../bld/./mfilterlibrary.o: ../include/mprototype.h
../bld/./mfilternode.o: ../include/mmemutils.h ../include/mfwddefs.h
../bld/./mfilternode.o: ../include/mfilternode.h ../include/mfilter.h
../bld/./mfilternode.o: ../include/mvariable.h ../include/mfilterlibrary.h
../bld/./mfilternode.o: ../include/merror.h ../include/msingletons.h
../bld/./mfilternode.o: ../include/mlibrary.h ../include/mlist.h
../bld/./mfilternode.o: ../include/mtokenlists.h ../include/mtoken.h
../bld/./mfilternode.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./mfilternode.o: ../include/mstringbuffer.h ../include/mstring.h
../bld/./mfilternode.o: ../include/mobject.h ../include/mprototype.h
../bld/./mfilternode.o: ../include/mtemplatecontext.h
../bld/./mfreetext.o: ../include/mnode.h ../include/mobject.h
../bld/./mfreetext.o: ../include/mprototype.h ../include/mfwddefs.h
../bld/./mfreetext.o: ../include/mclasses.h ../include/mstring.h
../bld/./mfreetext.o: ../include/mfreetext.h
../bld/./miterator.o: ../include/miterator.h ../include/mfwddefs.h
../bld/./mlibrary.o: ../include/mlibrary.h ../include/mfwddefs.h
../bld/./mlibrary.o: ../include/mlist.h ../include/mstring.h
../bld/./mlibrary.o: ../include/mobject.h ../include/mprototype.h
../bld/./mlist.o: ../include/mlist.h ../include/mfwddefs.h
../bld/./mnode.o: ../include/mnode.h ../include/mobject.h
../bld/./mnode.o: ../include/mprototype.h ../include/mfwddefs.h
../bld/./mnode.o: ../include/mclasses.h
../bld/./mnodelist.o: ../include/mnodelist.h ../include/mfwddefs.h
../bld/./mnodelist.o: ../include/mnode.h ../include/mobject.h
../bld/./mnodelist.o: ../include/mprototype.h ../include/mclasses.h
../bld/./mnodelist.o: ../include/mlist.h
../bld/./mobject.o: ../include/mobject.h ../include/mprototype.h
../bld/./mobject.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mobject.o: ../include/mclasses.h
../bld/./mparser.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mparser.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./mparser.o: ../include/mtemplateloader.h ../include/mparser.h
../bld/./mparser.o: ../include/mlist.h ../include/mstringbuffer.h
../bld/./mparser.o: ../include/mstring.h ../include/mobject.h
../bld/./mparser.o: ../include/mprototype.h ../include/mfreetext.h
../bld/./mparser.o: ../include/mvarnode.h ../include/mtagnode.h
../bld/./mparser.o: ../include/mnodelist.h
../bld/./mprototype.o: ../include/mprototype.h ../include/mfwddefs.h
../bld/./mprototype.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./msingletons.o: ../include/msingletons.h ../include/mfwddefs.h
../bld/./msingletons.o: ../include/mlibrary.h ../include/mfilterlibrary.h
../bld/./msingletons.o: ../include/mstring.h ../include/mobject.h
../bld/./msingletons.o: ../include/mprototype.h
../bld/./mstringbuffer.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mstringbuffer.o: ../include/mstringbuffer.h ../include/mstring.h
../bld/./mstringbuffer.o: ../include/mobject.h ../include/mprototype.h
../bld/./mstringbuffer.o: ../include/mmemutils.h
../bld/./mstring.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mstring.o: ../include/mstring.h ../include/mobject.h
../bld/./mstring.o: ../include/mprototype.h ../include/mstringtable.h
../bld/./mstring.o: ../include/mmemutils.h
../bld/./mstringtable.o: ../include/mstringtable.h ../include/mfwddefs.h
../bld/./mstringtable.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./mstringtable.o: ../include/marray.h
../bld/./mtagnode.o: ../include/mnode.h ../include/mobject.h
../bld/./mtagnode.o: ../include/mprototype.h ../include/mfwddefs.h
../bld/./mtagnode.o: ../include/mclasses.h ../include/merror.h
../bld/./mtagnode.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./mtagnode.o: ../include/mtoken.h ../include/mtemplateloader.h
../bld/./mtagnode.o: ../include/mtagnode.h
../bld/./mtoken.o: ../include/mtoken.h ../include/mfwddefs.h
../bld/./mtoken.o: ../include/mmemutils.h ../include/mstringbuffer.h
../bld/./mtoken.o: ../include/mstring.h ../include/mobject.h
../bld/./mtoken.o: ../include/mprototype.h
../bld/./mtokenizer.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mtokenizer.o: ../include/minputsource.h ../include/mstringbuffer.h
../bld/./mtokenizer.o: ../include/mstring.h ../include/mobject.h
../bld/./mtokenizer.o: ../include/mprototype.h ../include/mtokenizer.h
../bld/./mtokenizer.o: ../include/mtoken.h ../include/mmemutils.h
../bld/./mtokenlists.o: ../include/mtokenlists.h ../include/mfwddefs.h
../bld/./mtokenlists.o: ../include/mtoken.h
../bld/./mutils.o: ../include/mutils.h ../include/mfwddefs.h
../bld/./mvariable.o: ../include/mvariable.h ../include/mfwddefs.h
../bld/./mvariable.o: ../include/mlibrary.h ../include/mparser.h
../bld/./mvariable.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./mvariable.o: ../include/mstring.h ../include/mobject.h
../bld/./mvariable.o: ../include/mprototype.h ../include/mtemplatecontext.h
../bld/./mvariable.o: ../include/mnode.h ../include/mclasses.h
../bld/./mvariable.o: ../include/mmemutils.h ../include/mtokenlists.h
../bld/./mvariable.o: ../include/mutils.h ../include/msingletons.h
../bld/./mvariable.o: ../include/mfilterlibrary.h
../bld/./mvarnode.o: ../include/mnode.h ../include/mobject.h
../bld/./mvarnode.o: ../include/mprototype.h ../include/mfwddefs.h
../bld/./mvarnode.o: ../include/mclasses.h ../include/merror.h
../bld/./mvarnode.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./mvarnode.o: ../include/mtoken.h ../include/mvariable.h
../bld/./mvarnode.o: ../include/mfilternode.h ../include/mlist.h
../bld/./mvarnode.o: ../include/mmemutils.h

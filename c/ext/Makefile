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
PRODUCT_NAME            = mangoext

SHARED_LIB_NAME         = lib$(PRODUCT_NAME).so.$(VERSION)
STATIC_LIB_NAME         = lib$(PRODUCT_NAME).a.$(VERSION)

ifeq ($(BUILD_MODE), debug)
    SHARED_LIB_NAME     = lib$(PRODUCT_NAME)_debug.so.$(VERSION)
    STATIC_LIB_NAME     = lib$(PRODUCT_NAME)_debug.a.$(VERSION)
endif

SHARED_LIB_OUTPUT       =   "$(OUTPUT_DIR)/$(SHARED_LIB_NAME)"
STATIC_LIB_OUTPUT       =   "$(OUTPUT_DIR)/$(STATIC_LIB_NAME)"

SOURCE_FOLDERS  =   . 
INCLUDE_FOLDERS :=  ../src $(foreach dir,$(SOURCE_FOLDERS),$(dir))
EXT_SOURCES   := $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.c))
MANGO_OBJS      = $(foreach obj, $(patsubst %.c,%.o,$(EXT_SOURCES)), $(OUTPUT_DIR)/ext/$(obj))
LIBS            = 

###################     Begin Targets       ######################

# Implicit rule to build .o into the build directory from .c
$(OUTPUT_DIR)/ext/%.o : %.c
	@echo Building ext/$<  \-\>  $@ 
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
	@mkdir -p "$(OUTPUT_DIR)/ext"
	@cd $(OUTPUT_DIR)/ext ; mkdir -p $(SOURCE_FOLDERS)

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
	makedepend -Y -p"$(OUTPUT_DIR)/" $(INCLUDE_FLAGS) -- $(EXT_SOURCES)

# DO NOT DELETE

../bld/./maddfilter.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./maddfilter.o: ../src/core/mclasses.h ../src/core/mcontext.h
../bld/./maddfilter.o: ../src/core/merror.h ../src/core/miterator.h
../bld/./maddfilter.o: ../src/core/mobject.h ../src/core/mprototype.h
../bld/./maddfilter.o: ../src/utils/mutils.h ../src/core/mnumber.h
../bld/./maddfilter.o: ../src/core/mobject.h ../src/core/mprototype.h
../bld/./maddfilter.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./maddfilter.o: ../src/core/mrcstringfactory.h
../bld/./maddfilter.o: ../src/core/mstringfactory.h
../bld/./maddfilter.o: ../src/core/mrcstringtable.h ../src/core/mstring.h
../bld/./maddfilter.o: ../src/core/mstringbuffer.h
../bld/./maddfilter.o: ../src/core/mstringfactory.h ../src/io/minputsource.h
../bld/./maddfilter.o: ../src/io/moutstream.h ../src/io/mstroutstream.h
../bld/./maddfilter.o: ../src/io/moutstream.h ../src/nodes/mfilter.h
../bld/./maddfilter.o: ../src/nodes/mvar.h ../src/nodes/mfilternode.h
../bld/./maddfilter.o: ../src/nodes/mfreetext.h ../src/nodes/mnode.h
../bld/./maddfilter.o: ../src/nodes/mnode.h ../src/nodes/mnodelist.h
../bld/./maddfilter.o: ../src/nodes/mtagnode.h ../src/nodes/mvar.h
../bld/./maddfilter.o: ../src/nodes/mvariterator.h ../src/nodes/mvarnode.h
../bld/./maddfilter.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./maddfilter.o: ../src/parser/mtoken.h ../src/parser/mtagparser.h
../bld/./maddfilter.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./maddfilter.o: ../src/parser/mtokenlists.h
../bld/./maddfilter.o: ../src/renderer/mrenderer.h
../bld/./maddfilter.o: ../src/resolver/mtemplateloader.h
../bld/./maddfilter.o: ../src/resolver/mtmplctx.h
../bld/./maddfilter.o: ../src/resolver/mvarresolver.h
../bld/./maddfilter.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./maddfilter.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./maddfilter.o: ../src/utils/mcollection.h ../src/utils/mlinkedlist.h
../bld/./maddfilter.o: ../src/utils/mlist.h ../src/utils/mlibrary.h
../bld/./maddfilter.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./maddfilter.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./maddfilter.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./maddfilter.o: ../src/utils/mtable.h maddfilter.h
../bld/./mfortag.o: ../src/mangopub.h ../src/mfwddefs.h
../bld/./mfortag.o: ../src/core/mclasses.h ../src/core/mcontext.h
../bld/./mfortag.o: ../src/core/merror.h ../src/core/miterator.h
../bld/./mfortag.o: ../src/core/mobject.h ../src/core/mprototype.h
../bld/./mfortag.o: ../src/utils/mutils.h ../src/core/mnumber.h
../bld/./mfortag.o: ../src/core/mobject.h ../src/core/mprototype.h
../bld/./mfortag.o: ../src/core/mrcstring.h ../src/core/mstring.h
../bld/./mfortag.o: ../src/core/mrcstringfactory.h
../bld/./mfortag.o: ../src/core/mstringfactory.h ../src/core/mrcstringtable.h
../bld/./mfortag.o: ../src/core/mstring.h ../src/core/mstringbuffer.h
../bld/./mfortag.o: ../src/core/mstringfactory.h ../src/io/minputsource.h
../bld/./mfortag.o: ../src/io/moutstream.h ../src/io/mstroutstream.h
../bld/./mfortag.o: ../src/io/moutstream.h ../src/nodes/mfilter.h
../bld/./mfortag.o: ../src/nodes/mvar.h ../src/nodes/mfilternode.h
../bld/./mfortag.o: ../src/nodes/mfreetext.h ../src/nodes/mnode.h
../bld/./mfortag.o: ../src/nodes/mnode.h ../src/nodes/mnodelist.h
../bld/./mfortag.o: ../src/nodes/mtagnode.h ../src/nodes/mvar.h
../bld/./mfortag.o: ../src/nodes/mvariterator.h ../src/nodes/mvarnode.h
../bld/./mfortag.o: ../src/parser/mparser.h ../src/parser/mtokenizer.h
../bld/./mfortag.o: ../src/parser/mtoken.h ../src/parser/mtagparser.h
../bld/./mfortag.o: ../src/parser/mtoken.h ../src/parser/mtokenizer.h
../bld/./mfortag.o: ../src/parser/mtokenlists.h ../src/renderer/mrenderer.h
../bld/./mfortag.o: ../src/resolver/mtemplateloader.h
../bld/./mfortag.o: ../src/resolver/mtmplctx.h ../src/resolver/mvarresolver.h
../bld/./mfortag.o: ../src/utils/marraylist.h ../src/utils/mlist.h
../bld/./mfortag.o: ../src/utils/mcollection.h ../src/utils/mbintree.h
../bld/./mfortag.o: ../src/utils/mcollection.h ../src/utils/mlinkedlist.h
../bld/./mfortag.o: ../src/utils/mlist.h ../src/utils/mlibrary.h
../bld/./mfortag.o: ../src/utils/mmemutils.h ../src/utils/mrawarray.h
../bld/./mfortag.o: ../src/utils/mrawlist.h ../src/utils/msingletons.h
../bld/./mfortag.o: ../src/utils/mtable.h ../src/utils/mtreetable.h
../bld/./mfortag.o: ../src/utils/mtable.h mfortag.h

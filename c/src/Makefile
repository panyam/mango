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

SOURCE_FOLDERS  =   . ext
INCLUDE_FOLDERS := $(foreach dir,$(SOURCE_FOLDERS),../include/$(dir))
MANGO_SOURCES   := $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.c))
MANGO_OBJS      = $(foreach obj, $(patsubst %.c,%.o,$(MANGO_SOURCES)), $(OUTPUT_DIR)/$(obj))
LIBS            = 

###################     Begin Targets       ######################

# Implicit rule to build .o into the build directory from .c
$(OUTPUT_DIR)/%.o : %.c
	@echo Building $@
	$(GCC)  -std=c99 -c $(CFLAGS) $< -o $@

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
	makedepend -Y -p"$(OUTPUT_DIR)/" $(INCLUDE_FLAGS) -- $(MANGO_SOURCES)

# DO NOT DELETE

../bld/./maddfilter.o: ../include/mfilter.h ../include/mobject.h
../bld/./maddfilter.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./maddfilter.o: ../include/mvar.h ../include/mstring.h
../bld/./maddfilter.o: ../include/maddfilter.h
../bld/./marray.o: ../include/marray.h ../include/mobject.h
../bld/./marray.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mbintree.o: ../include/mbintree.h ../include/mfwddefs.h
../bld/./mbintree.o: ../include/mmemutils.h
../bld/./mbtreetable.o: ../include/mbtreetable.h ../include/mtable.h
../bld/./mbtreetable.o: ../include/mfwddefs.h ../include/mbintree.h
../bld/./mbtreetable.o: ../include/mmemutils.h
../bld/./mclasses.o: ../include/mclasses.h ../include/mfwddefs.h
../bld/./mclasses.o: ../include/mbintree.h ../include/mmemutils.h
../bld/./merror.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mfilter.o: ../include/mmemutils.h ../include/mfwddefs.h
../bld/./mfilter.o: ../include/mfilter.h ../include/mobject.h
../bld/./mfilter.o: ../include/mvar.h ../include/mstring.h
../bld/./mfilterlibrary.o: ../include/mfilterlibrary.h ../include/mfwddefs.h
../bld/./mfilterlibrary.o: ../include/msingletons.h ../include/mlibrary.h
../bld/./mfilterlibrary.o: ../include/mbintree.h
../bld/./mfilternode.o: ../include/mmemutils.h ../include/mfwddefs.h
../bld/./mfilternode.o: ../include/mfilternode.h ../include/mfilter.h
../bld/./mfilternode.o: ../include/mobject.h ../include/mvar.h
../bld/./mfilternode.o: ../include/mstring.h ../include/mfilterlibrary.h
../bld/./mfilternode.o: ../include/merror.h ../include/msingletons.h
../bld/./mfilternode.o: ../include/mlibrary.h ../include/mlist.h
../bld/./mfilternode.o: ../include/mtokenlists.h ../include/mtoken.h
../bld/./mfilternode.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./mfilternode.o: ../include/mparsercontext.h
../bld/./mfilternode.o: ../include/mstringbuffer.h
../bld/./mfilternode.o: ../include/mstringfactory.h
../bld/./mfilternode.o: ../include/mtemplatecontext.h
../bld/./mfreetext.o: ../include/mstring.h ../include/mobject.h
../bld/./mfreetext.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mfreetext.o: ../include/mfreetext.h ../include/mnode.h
../bld/./mfreetext.o: ../include/mclasses.h
../bld/./miterator.o: ../include/miterator.h ../include/mfwddefs.h
../bld/./mlibrary.o: ../include/mlibrary.h ../include/mfwddefs.h
../bld/./mlibrary.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./mlibrary.o: ../include/mstring.h ../include/mobject.h
../bld/./mlist.o: ../include/mlist.h ../include/mfwddefs.h
../bld/./mnode.o: ../include/mnode.h ../include/mobject.h
../bld/./mnode.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mnode.o: ../include/mclasses.h
../bld/./mnodelist.o: ../include/mmemutils.h ../include/mfwddefs.h
../bld/./mnodelist.o: ../include/mnodelist.h ../include/mnode.h
../bld/./mnodelist.o: ../include/mobject.h ../include/mclasses.h
../bld/./mnodelist.o: ../include/mlist.h
../bld/./mnoderenderer.o: ../include/mnoderenderer.h ../include/mobject.h
../bld/./mnoderenderer.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mnoderenderer.o: ../include/mclasses.h
../bld/./mobject.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./mobject.o: ../include/mmemutils.h ../include/mclasses.h
../bld/./mparser.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mparser.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./mparser.o: ../include/mtemplateloader.h ../include/mparser.h
../bld/./mparser.o: ../include/mparsercontext.h ../include/mlist.h
../bld/./mparser.o: ../include/mstringbuffer.h ../include/mstring.h
../bld/./mparser.o: ../include/mobject.h ../include/mmemutils.h
../bld/./mparser.o: ../include/mstringfactory.h ../include/mfreetext.h
../bld/./mparser.o: ../include/mnode.h ../include/mclasses.h
../bld/./mparser.o: ../include/mvarnode.h ../include/mtagnode.h
../bld/./mparser.o: ../include/mnodelist.h
../bld/./mrcstring.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mrcstring.o: ../include/mstringbuffer.h ../include/mstring.h
../bld/./mrcstring.o: ../include/mobject.h ../include/mmemutils.h
../bld/./mrcstring.o: ../include/mstringfactory.h ../include/mrcstring.h
../bld/./mrcstring.o: ../include/mrcstringtable.h
../bld/./mrcstringfactory.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mrcstringfactory.o: ../include/mstringbuffer.h ../include/mstring.h
../bld/./mrcstringfactory.o: ../include/mobject.h ../include/mmemutils.h
../bld/./mrcstringfactory.o: ../include/mrcstring.h
../bld/./mrcstringfactory.o: ../include/mrcstringfactory.h
../bld/./mrcstringfactory.o: ../include/mstringfactory.h
../bld/./mrcstringfactory.o: ../include/mrcstringtable.h
../bld/./mrcstringtable.o: ../include/mrcstringtable.h ../include/mfwddefs.h
../bld/./mrcstringtable.o: ../include/mmemutils.h ../include/mbintree.h
../bld/./mrcstringtable.o: ../include/marray.h ../include/mobject.h
../bld/./msingletons.o: ../include/msingletons.h ../include/mfwddefs.h
../bld/./msingletons.o: ../include/mlibrary.h ../include/mstring.h
../bld/./msingletons.o: ../include/mobject.h ../include/mmemutils.h
../bld/./mstringbuffer.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mstringbuffer.o: ../include/mstringbuffer.h ../include/mstring.h
../bld/./mstringbuffer.o: ../include/mobject.h ../include/mmemutils.h
../bld/./mstring.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mstring.o: ../include/mstring.h ../include/mobject.h
../bld/./mstring.o: ../include/mmemutils.h
../bld/./mstringfactory.o: ../include/mstringfactory.h ../include/mstring.h
../bld/./mstringfactory.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./mstringfactory.o: ../include/mmemutils.h
../bld/./mtable.o: ../include/mtable.h ../include/mfwddefs.h
../bld/./mtagnode.o: ../include/mnode.h ../include/mobject.h
../bld/./mtagnode.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mtagnode.o: ../include/mclasses.h ../include/merror.h
../bld/./mtagnode.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./mtagnode.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./mtagnode.o: ../include/mtemplateloader.h ../include/mtagnode.h
../bld/./mtagnode.o: ../include/mtagparser.h ../include/mtagparserlibrary.h
../bld/./mtagnode.o: ../include/mstringbuffer.h ../include/mstring.h
../bld/./mtagnode.o: ../include/mstringfactory.h
../bld/./mtagparserlibrary.o: ../include/mtagparserlibrary.h
../bld/./mtagparserlibrary.o: ../include/mfwddefs.h ../include/msingletons.h
../bld/./mtagparserlibrary.o: ../include/mlibrary.h ../include/mtagparser.h
../bld/./mtagparserlibrary.o: ../include/mobject.h ../include/mmemutils.h
../bld/./mtemplatecontext.o: ../include/mtemplatecontext.h
../bld/./mtemplatecontext.o: ../include/mfwddefs.h ../include/mstring.h
../bld/./mtemplatecontext.o: ../include/mobject.h ../include/mmemutils.h
../bld/./mtemplatecontext.o: ../include/mbintree.h
../bld/./mtoken.o: ../include/mtoken.h ../include/mfwddefs.h
../bld/./mtoken.o: ../include/mmemutils.h ../include/mstringbuffer.h
../bld/./mtoken.o: ../include/mstring.h ../include/mobject.h
../bld/./mtokenizer.o: ../include/merror.h ../include/mfwddefs.h
../bld/./mtokenizer.o: ../include/minputsource.h ../include/mstringbuffer.h
../bld/./mtokenizer.o: ../include/mstring.h ../include/mobject.h
../bld/./mtokenizer.o: ../include/mmemutils.h ../include/mtokenizer.h
../bld/./mtokenizer.o: ../include/mtoken.h
../bld/./mtokenlists.o: ../include/mtokenlists.h ../include/mfwddefs.h
../bld/./mtokenlists.o: ../include/mtoken.h
../bld/./mutils.o: ../include/mutils.h ../include/mfwddefs.h
../bld/./mvalue.o: ../include/mvalue.h ../include/mobject.h
../bld/./mvalue.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mvar.o: ../include/mvar.h ../include/mstring.h ../include/mobject.h
../bld/./mvar.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mvar.o: ../include/mlibrary.h ../include/mvarlibrary.h
../bld/./mvar.o: ../include/mparser.h ../include/mtokenizer.h
../bld/./mvar.o: ../include/mtoken.h ../include/mparsercontext.h
../bld/./mvar.o: ../include/mstringbuffer.h ../include/mstringfactory.h
../bld/./mvar.o: ../include/mtemplatecontext.h ../include/mnode.h
../bld/./mvar.o: ../include/mclasses.h ../include/mtokenlists.h
../bld/./mvar.o: ../include/mutils.h ../include/msingletons.h
../bld/./mvarlibrary.o: ../include/mvarlibrary.h ../include/mfwddefs.h
../bld/./mvarnode.o: ../include/mvarnode.h ../include/mnode.h
../bld/./mvarnode.o: ../include/mobject.h ../include/mfwddefs.h
../bld/./mvarnode.o: ../include/mmemutils.h ../include/mclasses.h
../bld/./mvarnode.o: ../include/merror.h ../include/mparser.h
../bld/./mvarnode.o: ../include/mtokenizer.h ../include/mtoken.h
../bld/./mvarnode.o: ../include/mparsercontext.h ../include/mvar.h
../bld/./mvarnode.o: ../include/mstring.h ../include/mfilternode.h
../bld/./mvarnode.o: ../include/mlist.h
../bld/./mvarresolver.o: ../include/mvarresolver.h ../include/mvar.h
../bld/./mvarresolver.o: ../include/mstring.h ../include/mobject.h
../bld/./mvarresolver.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/./mvarresolver.o: ../include/mtemplatecontext.h ../include/mvalue.h
../bld/ext/mfortag.o: ../include/mvalue.h ../include/mobject.h
../bld/ext/mfortag.o: ../include/mfwddefs.h ../include/mmemutils.h
../bld/ext/mfortag.o: ../include/mnode.h ../include/mclasses.h
../bld/ext/mfortag.o: ../include/merror.h ../include/mvar.h
../bld/ext/mfortag.o: ../include/mstring.h ../include/mstringbuffer.h
../bld/ext/mfortag.o: ../include/mstringfactory.h ../include/mlist.h
../bld/ext/mfortag.o: ../include/marray.h ../include/mtokenlists.h
../bld/ext/mfortag.o: ../include/mtoken.h ../include/mparser.h
../bld/ext/mfortag.o: ../include/mtokenizer.h ../include/mparsercontext.h

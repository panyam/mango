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

SOURCE_FOLDERS  =   . utils core parser nodes renderer resolver
INCLUDE_FOLDERS :=  $(foreach dir,$(SOURCE_FOLDERS),$(dir))
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
	makedepend -Y -p"$(OUTPUT_DIR)/" $(INCLUDE_FLAGS) -- $(MANGO_SOURCES)

# DO NOT DELETE

../bld/./marraylist.o: ../include/./marraylist.h ../include/./mlist.h
../bld/./marraylist.o: ../include/./mcollection.h ../include/./mobject.h
../bld/./marraylist.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./marraylist.o: ../include/./mutils.h
../bld/./mbintree.o: ../include/./mbintree.h ../include/./mfwddefs.h
../bld/./mbintree.o: ../include/./mmemutils.h
../bld/./mclasses.o: ../include/./mclasses.h ../include/./mfwddefs.h
../bld/./mclasses.o: ../include/./mbintree.h ../include/./mmemutils.h
../bld/./mcollection.o: ../include/./mcollection.h ../include/./mobject.h
../bld/./mcollection.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mcollection.o: ../include/./mutils.h
../bld/./merror.o: ../include/./merror.h ../include/./mfwddefs.h
../bld/./mfilter.o: ../include/./mmemutils.h ../include/./mfwddefs.h
../bld/./mfilter.o: ../include/./mfilter.h ../include/./mobject.h
../bld/./mfilter.o: ../include/./mutils.h ../include/./mvar.h
../bld/./mfilter.o: ../include/./mstring.h
../bld/./mfilterlibrary.o: ../include/./mfilterlibrary.h
../bld/./mfilterlibrary.o: ../include/./mfwddefs.h ../include/./msingletons.h
../bld/./mfilterlibrary.o: ../include/./mbintree.h ../include/./mtable.h
../bld/./mfilterlibrary.o: ../include/./mcollection.h ../include/./mobject.h
../bld/./mfilterlibrary.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mfilternode.o: ../include/./mmemutils.h ../include/./mfwddefs.h
../bld/./mfilternode.o: ../include/./mfilternode.h ../include/./mobject.h
../bld/./mfilternode.o: ../include/./mutils.h ../include/./mfilter.h
../bld/./mfilternode.o: ../include/./mvar.h ../include/./mstring.h
../bld/./mfilternode.o: ../include/./mfilterlibrary.h ../include/./merror.h
../bld/./mfilternode.o: ../include/./msingletons.h ../include/./mlinkedlist.h
../bld/./mfilternode.o: ../include/./mlist.h ../include/./mcollection.h
../bld/./mfilternode.o: ../include/./mtokenlists.h ../include/./mtoken.h
../bld/./mfilternode.o: ../include/./mparser.h ../include/./mtokenizer.h
../bld/./mfilternode.o: ../include/./mparsercontext.h
../bld/./mfilternode.o: ../include/./mstringbuffer.h
../bld/./mfilternode.o: ../include/./mstringfactory.h ../include/./mtmplctx.h
../bld/./mfreetext.o: ../include/./mstring.h ../include/./mobject.h
../bld/./mfreetext.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mfreetext.o: ../include/./mutils.h ../include/./mfreetext.h
../bld/./mfreetext.o: ../include/./mnode.h ../include/./mclasses.h
../bld/./miterator.o: ../include/./miterator.h ../include/./mobject.h
../bld/./miterator.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./miterator.o: ../include/./mutils.h
../bld/./mlinkedlist.o: ../include/./mlinkedlist.h ../include/./mlist.h
../bld/./mlinkedlist.o: ../include/./mcollection.h ../include/./mobject.h
../bld/./mlinkedlist.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mlinkedlist.o: ../include/./mutils.h
../bld/./mlist.o: ../include/./mlist.h ../include/./mcollection.h
../bld/./mlist.o: ../include/./mobject.h ../include/./mfwddefs.h
../bld/./mlist.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mnode.o: ../include/./mnode.h ../include/./mobject.h
../bld/./mnode.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mnode.o: ../include/./mutils.h ../include/./mclasses.h
../bld/./mnodelist.o: ../include/./mmemutils.h ../include/./mfwddefs.h
../bld/./mnodelist.o: ../include/./mnodelist.h ../include/./mnode.h
../bld/./mnodelist.o: ../include/./mobject.h ../include/./mutils.h
../bld/./mnodelist.o: ../include/./mclasses.h ../include/./mlinkedlist.h
../bld/./mnodelist.o: ../include/./mlist.h ../include/./mcollection.h
../bld/./mnumber.o: ../include/./mnumber.h ../include/./mobject.h
../bld/./mnumber.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mnumber.o: ../include/./mutils.h
../bld/./mobject.o: ../include/./mobject.h ../include/./mfwddefs.h
../bld/./mobject.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mobject.o: ../include/./mclasses.h
../bld/./mparser.o: ../include/./merror.h ../include/./mfwddefs.h
../bld/./mparser.o: ../include/./mtokenizer.h ../include/./mtoken.h
../bld/./mparser.o: ../include/./mtemplateloader.h ../include/./mparser.h
../bld/./mparser.o: ../include/./mparsercontext.h ../include/./mrawlist.h
../bld/./mparser.o: ../include/./mobject.h ../include/./mmemutils.h
../bld/./mparser.o: ../include/./mutils.h ../include/./mlinkedlist.h
../bld/./mparser.o: ../include/./mlist.h ../include/./mcollection.h
../bld/./mparser.o: ../include/./mstringbuffer.h ../include/./mstring.h
../bld/./mparser.o: ../include/./mstringfactory.h ../include/./mfreetext.h
../bld/./mparser.o: ../include/./mnode.h ../include/./mclasses.h
../bld/./mparser.o: ../include/./mvarnode.h ../include/./mtagnode.h
../bld/./mparser.o: ../include/./mnodelist.h
../bld/./mrawarray.o: ../include/./mrawarray.h ../include/./mobject.h
../bld/./mrawarray.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mrawarray.o: ../include/./mutils.h
../bld/./mrawlist.o: ../include/./mrawlist.h ../include/./mobject.h
../bld/./mrawlist.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mrawlist.o: ../include/./mutils.h
../bld/./mrcstring.o: ../include/./merror.h ../include/./mfwddefs.h
../bld/./mrcstring.o: ../include/./mstringbuffer.h ../include/./mstring.h
../bld/./mrcstring.o: ../include/./mobject.h ../include/./mmemutils.h
../bld/./mrcstring.o: ../include/./mutils.h ../include/./mstringfactory.h
../bld/./mrcstring.o: ../include/./mrcstring.h ../include/./mrcstringtable.h
../bld/./mrcstringfactory.o: ../include/./merror.h ../include/./mfwddefs.h
../bld/./mrcstringfactory.o: ../include/./mstringbuffer.h
../bld/./mrcstringfactory.o: ../include/./mstring.h ../include/./mobject.h
../bld/./mrcstringfactory.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mrcstringfactory.o: ../include/./mrcstring.h
../bld/./mrcstringfactory.o: ../include/./mrcstringfactory.h
../bld/./mrcstringfactory.o: ../include/./mstringfactory.h
../bld/./mrcstringfactory.o: ../include/./mrcstringtable.h
../bld/./mrcstringtable.o: ../include/./mrcstringtable.h
../bld/./mrcstringtable.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mrcstringtable.o: ../include/./mbintree.h ../include/./mrawarray.h
../bld/./mrcstringtable.o: ../include/./mobject.h ../include/./mutils.h
../bld/./mrenderer.o: ../include/./mrenderer.h ../include/./mobject.h
../bld/./mrenderer.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mrenderer.o: ../include/./mutils.h
../bld/./msingletons.o: ../include/./msingletons.h ../include/./mfwddefs.h
../bld/./msingletons.o: ../include/./mtreetable.h ../include/./mtable.h
../bld/./msingletons.o: ../include/./mcollection.h ../include/./mobject.h
../bld/./msingletons.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./msingletons.o: ../include/./mstring.h
../bld/./mstringbuffer.o: ../include/./merror.h ../include/./mfwddefs.h
../bld/./mstringbuffer.o: ../include/./mstringbuffer.h ../include/./mstring.h
../bld/./mstringbuffer.o: ../include/./mobject.h ../include/./mmemutils.h
../bld/./mstringbuffer.o: ../include/./mutils.h
../bld/./mstring.o: ../include/./merror.h ../include/./mfwddefs.h
../bld/./mstring.o: ../include/./mstring.h ../include/./mobject.h
../bld/./mstring.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mstringfactory.o: ../include/./mstringfactory.h
../bld/./mstringfactory.o: ../include/./mstring.h ../include/./mobject.h
../bld/./mstringfactory.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mstringfactory.o: ../include/./mutils.h
../bld/./mtable.o: ../include/./mtable.h ../include/./mcollection.h
../bld/./mtable.o: ../include/./mobject.h ../include/./mfwddefs.h
../bld/./mtable.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mtagnode.o: ../include/./mnode.h ../include/./mobject.h
../bld/./mtagnode.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mtagnode.o: ../include/./mutils.h ../include/./mclasses.h
../bld/./mtagnode.o: ../include/./merror.h ../include/./mparser.h
../bld/./mtagnode.o: ../include/./mtokenizer.h ../include/./mtoken.h
../bld/./mtagnode.o: ../include/./mparsercontext.h
../bld/./mtagnode.o: ../include/./mtemplateloader.h ../include/./mtagnode.h
../bld/./mtagnode.o: ../include/./mtagparser.h
../bld/./mtagnode.o: ../include/./mtagparserlibrary.h
../bld/./mtagnode.o: ../include/./mstringbuffer.h ../include/./mstring.h
../bld/./mtagnode.o: ../include/./mstringfactory.h
../bld/./mtagparserlibrary.o: ../include/./mtagparserlibrary.h
../bld/./mtagparserlibrary.o: ../include/./mfwddefs.h
../bld/./mtagparserlibrary.o: ../include/./msingletons.h
../bld/./mtagparserlibrary.o: ../include/./mtagparser.h
../bld/./mtagparserlibrary.o: ../include/./mobject.h ../include/./mmemutils.h
../bld/./mtagparserlibrary.o: ../include/./mutils.h ../include/./mtable.h
../bld/./mtagparserlibrary.o: ../include/./mcollection.h
../bld/./mtmplctx.o: ../include/./mtmplctx.h ../include/./mobject.h
../bld/./mtmplctx.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mtmplctx.o: ../include/./mutils.h ../include/./mstring.h
../bld/./mtmplctx.o: ../include/./mtreetable.h ../include/./mtable.h
../bld/./mtmplctx.o: ../include/./mcollection.h ../include/./mlinkedlist.h
../bld/./mtmplctx.o: ../include/./mlist.h
../bld/./mtoken.o: ../include/./mtoken.h ../include/./mfwddefs.h
../bld/./mtoken.o: ../include/./mmemutils.h ../include/./mstringbuffer.h
../bld/./mtoken.o: ../include/./mstring.h ../include/./mobject.h
../bld/./mtoken.o: ../include/./mutils.h
../bld/./mtokenizer.o: ../include/./merror.h ../include/./mfwddefs.h
../bld/./mtokenizer.o: ../include/./minputsource.h
../bld/./mtokenizer.o: ../include/./mstringbuffer.h ../include/./mstring.h
../bld/./mtokenizer.o: ../include/./mobject.h ../include/./mmemutils.h
../bld/./mtokenizer.o: ../include/./mutils.h ../include/./mtokenizer.h
../bld/./mtokenizer.o: ../include/./mtoken.h
../bld/./mtokenlists.o: ../include/./mtokenlists.h ../include/./mfwddefs.h
../bld/./mtokenlists.o: ../include/./mtoken.h
../bld/./mtreetable.o: ../include/./mstring.h ../include/./mobject.h
../bld/./mtreetable.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mtreetable.o: ../include/./mutils.h ../include/./mtreetable.h
../bld/./mtreetable.o: ../include/./mtable.h ../include/./mcollection.h
../bld/./mtreetable.o: ../include/./mbintree.h
../bld/./mutils.o: ../include/./mobject.h ../include/./mfwddefs.h
../bld/./mutils.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mvar.o: ../include/./mvar.h ../include/./mstring.h
../bld/./mvar.o: ../include/./mobject.h ../include/./mfwddefs.h
../bld/./mvar.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mvar.o: ../include/./mvarlibrary.h ../include/./mtable.h
../bld/./mvar.o: ../include/./mcollection.h ../include/./mparser.h
../bld/./mvar.o: ../include/./mtokenizer.h ../include/./mtoken.h
../bld/./mvar.o: ../include/./mparsercontext.h ../include/./mstringbuffer.h
../bld/./mvar.o: ../include/./mstringfactory.h ../include/./mtmplctx.h
../bld/./mvar.o: ../include/./mnode.h ../include/./mclasses.h
../bld/./mvar.o: ../include/./mtokenlists.h ../include/./msingletons.h
../bld/./mvarlibrary.o: ../include/./mvarlibrary.h ../include/./mtable.h
../bld/./mvarlibrary.o: ../include/./mcollection.h ../include/./mobject.h
../bld/./mvarlibrary.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mvarlibrary.o: ../include/./mutils.h
../bld/./mvarnode.o: ../include/./mvarnode.h ../include/./mnode.h
../bld/./mvarnode.o: ../include/./mobject.h ../include/./mfwddefs.h
../bld/./mvarnode.o: ../include/./mmemutils.h ../include/./mutils.h
../bld/./mvarnode.o: ../include/./mclasses.h ../include/./merror.h
../bld/./mvarnode.o: ../include/./mparser.h ../include/./mtokenizer.h
../bld/./mvarnode.o: ../include/./mtoken.h ../include/./mparsercontext.h
../bld/./mvarnode.o: ../include/./mvar.h ../include/./mstring.h
../bld/./mvarnode.o: ../include/./mfilternode.h ../include/./mlinkedlist.h
../bld/./mvarnode.o: ../include/./mlist.h ../include/./mcollection.h
../bld/./mvarresolver.o: ../include/./marraylist.h ../include/./mlist.h
../bld/./mvarresolver.o: ../include/./mcollection.h ../include/./mobject.h
../bld/./mvarresolver.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/./mvarresolver.o: ../include/./mutils.h ../include/./mvarresolver.h
../bld/./mvarresolver.o: ../include/./mvar.h ../include/./mstring.h
../bld/./mvarresolver.o: ../include/./mtmplctx.h ../include/./mnumber.h
../bld/ext/maddfilter.o: ../include/./mfilter.h ../include/./mobject.h
../bld/ext/maddfilter.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/ext/maddfilter.o: ../include/./mutils.h ../include/./mvar.h
../bld/ext/maddfilter.o: ../include/./mstring.h ../include/ext/maddfilter.h
../bld/ext/mfortag.o: ../include/ext/mfortag.h ../include/./mtagnode.h
../bld/ext/mfortag.o: ../include/./mnode.h ../include/./mobject.h
../bld/ext/mfortag.o: ../include/./mfwddefs.h ../include/./mmemutils.h
../bld/ext/mfortag.o: ../include/./mutils.h ../include/./mclasses.h
../bld/ext/mfortag.o: ../include/./mtagparser.h ../include/./merror.h
../bld/ext/mfortag.o: ../include/./mvar.h ../include/./mstring.h
../bld/ext/mfortag.o: ../include/./mstringbuffer.h
../bld/ext/mfortag.o: ../include/./mstringfactory.h
../bld/ext/mfortag.o: ../include/./mlinkedlist.h ../include/./mlist.h
../bld/ext/mfortag.o: ../include/./mcollection.h ../include/./marraylist.h
../bld/ext/mfortag.o: ../include/./mtokenlists.h ../include/./mtoken.h
../bld/ext/mfortag.o: ../include/./mparser.h ../include/./mtokenizer.h
../bld/ext/mfortag.o: ../include/./mparsercontext.h

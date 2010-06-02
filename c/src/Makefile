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

SOURCE_FOLDERS  =   . utils core io parser nodes renderer resolver
INCLUDE_FOLDERS :=  $(foreach dir,$(SOURCE_FOLDERS),$(dir))
MANGO_SOURCES   := $(foreach dir,$(SOURCE_FOLDERS),$(wildcard $(dir)/*.c))
MANGO_OBJS      = $(foreach obj, $(patsubst %.c,%.o,$(MANGO_SOURCES)), $(OUTPUT_DIR)/src/$(obj))
LIBS            = 

###################     Begin Targets       ######################

# Implicit rule to build .o into the build directory from .c
$(OUTPUT_DIR)/src/%.o : %.c
	@echo Building src/$<  \-\>  $@ 
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
	@mkdir -p "$(OUTPUT_DIR)/src"
	@cd $(OUTPUT_DIR)/src ; mkdir -p $(SOURCE_FOLDERS)

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

../bld/utils/marraylist.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/marraylist.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/marraylist.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/marraylist.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/marraylist.o: core/mrcstring.h core/mstring.h
../bld/utils/marraylist.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/marraylist.o: core/mrcstringtable.h core/mstring.h
../bld/utils/marraylist.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/marraylist.o: io/minputsource.h io/moutstream.h
../bld/utils/marraylist.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/utils/marraylist.o: nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/marraylist.o: nodes/mfilternode.h nodes/mfreetext.h
../bld/utils/marraylist.o: nodes/mnode.h nodes/mnode.h nodes/mnodelist.h
../bld/utils/marraylist.o: nodes/mtagnode.h nodes/mvar.h nodes/mvariterator.h
../bld/utils/marraylist.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/utils/marraylist.o: parser/mparser.h parser/mtokenizer.h
../bld/utils/marraylist.o: parser/mtoken.h parser/mtagparser.h
../bld/utils/marraylist.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/marraylist.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/marraylist.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/marraylist.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/marraylist.o: utils/marraylist.h utils/mlist.h
../bld/utils/marraylist.o: utils/mcollection.h utils/mbintree.h
../bld/utils/marraylist.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/marraylist.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/utils/marraylist.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/marraylist.o: utils/msingletons.h utils/mtable.h
../bld/utils/marraylist.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mbintree.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mbintree.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/mbintree.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/mbintree.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/mbintree.o: core/mrcstring.h core/mstring.h
../bld/utils/mbintree.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/mbintree.o: core/mrcstringtable.h core/mstring.h
../bld/utils/mbintree.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/mbintree.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/utils/mbintree.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/utils/mbintree.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/utils/mbintree.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/utils/mbintree.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/utils/mbintree.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mbintree.o: nodes/mvarnode.h parser/mparser.h
../bld/utils/mbintree.o: parser/mtokenizer.h parser/mtoken.h
../bld/utils/mbintree.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mbintree.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mbintree.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mbintree.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mbintree.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mbintree.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mbintree.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mbintree.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/utils/mbintree.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mbintree.o: utils/msingletons.h utils/mtable.h
../bld/utils/mbintree.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mcollection.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mcollection.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/mcollection.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/mcollection.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/mcollection.o: core/mrcstring.h core/mstring.h
../bld/utils/mcollection.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/mcollection.o: core/mrcstringtable.h core/mstring.h
../bld/utils/mcollection.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/mcollection.o: io/minputsource.h io/moutstream.h
../bld/utils/mcollection.o: io/mstroutstream.h io/moutstream.h
../bld/utils/mcollection.o: nodes/mfilter.h nodes/mvar.h
../bld/utils/mcollection.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/utils/mcollection.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/utils/mcollection.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/utils/mcollection.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mcollection.o: nodes/mvarnode.h parser/mparser.h
../bld/utils/mcollection.o: parser/mtokenizer.h parser/mtoken.h
../bld/utils/mcollection.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mcollection.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mcollection.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mcollection.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mcollection.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mcollection.o: utils/mlist.h utils/mcollection.h
../bld/utils/mcollection.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mcollection.o: utils/mlinkedlist.h utils/mlist.h
../bld/utils/mcollection.o: utils/mlibrary.h utils/mmemutils.h
../bld/utils/mcollection.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mcollection.o: utils/msingletons.h utils/mtable.h
../bld/utils/mcollection.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mlibrary.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mlibrary.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/mlibrary.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/mlibrary.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/mlibrary.o: core/mrcstring.h core/mstring.h
../bld/utils/mlibrary.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/mlibrary.o: core/mrcstringtable.h core/mstring.h
../bld/utils/mlibrary.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/mlibrary.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/utils/mlibrary.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/utils/mlibrary.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/utils/mlibrary.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/utils/mlibrary.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/utils/mlibrary.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mlibrary.o: nodes/mvarnode.h parser/mparser.h
../bld/utils/mlibrary.o: parser/mtokenizer.h parser/mtoken.h
../bld/utils/mlibrary.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mlibrary.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mlibrary.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mlibrary.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mlibrary.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mlibrary.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mlibrary.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mlibrary.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/utils/mlibrary.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mlibrary.o: utils/msingletons.h utils/mtable.h
../bld/utils/mlibrary.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mlinkedlist.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mlinkedlist.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/mlinkedlist.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/mlinkedlist.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/mlinkedlist.o: core/mrcstring.h core/mstring.h
../bld/utils/mlinkedlist.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/mlinkedlist.o: core/mrcstringtable.h core/mstring.h
../bld/utils/mlinkedlist.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/mlinkedlist.o: io/minputsource.h io/moutstream.h
../bld/utils/mlinkedlist.o: io/mstroutstream.h io/moutstream.h
../bld/utils/mlinkedlist.o: nodes/mfilter.h nodes/mvar.h
../bld/utils/mlinkedlist.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/utils/mlinkedlist.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/utils/mlinkedlist.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/utils/mlinkedlist.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mlinkedlist.o: nodes/mvarnode.h parser/mparser.h
../bld/utils/mlinkedlist.o: parser/mtokenizer.h parser/mtoken.h
../bld/utils/mlinkedlist.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mlinkedlist.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mlinkedlist.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mlinkedlist.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mlinkedlist.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mlinkedlist.o: utils/mlist.h utils/mcollection.h
../bld/utils/mlinkedlist.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mlinkedlist.o: utils/mlinkedlist.h utils/mlist.h
../bld/utils/mlinkedlist.o: utils/mlibrary.h utils/mmemutils.h
../bld/utils/mlinkedlist.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mlinkedlist.o: utils/msingletons.h utils/mtable.h
../bld/utils/mlinkedlist.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mlist.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/utils/mlist.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/mlist.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/utils/mlist.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/utils/mlist.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/mlist.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/mlist.o: core/mstring.h core/mstringbuffer.h
../bld/utils/mlist.o: core/mstringfactory.h io/minputsource.h io/moutstream.h
../bld/utils/mlist.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/utils/mlist.o: nodes/mvar.h nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/utils/mlist.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/utils/mlist.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/utils/mlist.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mlist.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/utils/mlist.o: parser/mtoken.h parser/mtagparser.h
../bld/utils/mlist.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mlist.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mlist.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mlist.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mlist.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/utils/mlist.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mlist.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/utils/mlist.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mlist.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mlist.o: utils/mtable.h
../bld/utils/mnumber.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/utils/mnumber.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/mnumber.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/utils/mnumber.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/utils/mnumber.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/mnumber.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/mnumber.o: core/mstring.h core/mstringbuffer.h
../bld/utils/mnumber.o: core/mstringfactory.h io/minputsource.h
../bld/utils/mnumber.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/utils/mnumber.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mnumber.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/mnumber.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/mnumber.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mnumber.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/utils/mnumber.o: parser/mtoken.h parser/mtagparser.h
../bld/utils/mnumber.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mnumber.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mnumber.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mnumber.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mnumber.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/utils/mnumber.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mnumber.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/utils/mnumber.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mnumber.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mnumber.o: utils/mtable.h
../bld/utils/mrawarray.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mrawarray.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/mrawarray.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/mrawarray.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/mrawarray.o: core/mrcstring.h core/mstring.h
../bld/utils/mrawarray.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/mrawarray.o: core/mrcstringtable.h core/mstring.h
../bld/utils/mrawarray.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/mrawarray.o: io/minputsource.h io/moutstream.h
../bld/utils/mrawarray.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/utils/mrawarray.o: nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mrawarray.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/mrawarray.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/mrawarray.o: nodes/mvar.h nodes/mvariterator.h
../bld/utils/mrawarray.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/utils/mrawarray.o: parser/mparser.h parser/mtokenizer.h
../bld/utils/mrawarray.o: parser/mtoken.h parser/mtagparser.h
../bld/utils/mrawarray.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mrawarray.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mrawarray.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mrawarray.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mrawarray.o: utils/marraylist.h utils/mlist.h
../bld/utils/mrawarray.o: utils/mcollection.h utils/mbintree.h
../bld/utils/mrawarray.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mrawarray.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/utils/mrawarray.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mrawarray.o: utils/msingletons.h utils/mtable.h
../bld/utils/mrawarray.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mrawlist.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mrawlist.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/mrawlist.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/mrawlist.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/mrawlist.o: core/mrcstring.h core/mstring.h
../bld/utils/mrawlist.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/mrawlist.o: core/mrcstringtable.h core/mstring.h
../bld/utils/mrawlist.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/mrawlist.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/utils/mrawlist.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/utils/mrawlist.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/utils/mrawlist.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/utils/mrawlist.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/utils/mrawlist.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mrawlist.o: nodes/mvarnode.h parser/mparser.h
../bld/utils/mrawlist.o: parser/mtokenizer.h parser/mtoken.h
../bld/utils/mrawlist.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mrawlist.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mrawlist.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mrawlist.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mrawlist.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mrawlist.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mrawlist.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mrawlist.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/utils/mrawlist.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mrawlist.o: utils/msingletons.h utils/mtable.h
../bld/utils/mrawlist.o: utils/mtreetable.h utils/mtable.h
../bld/utils/msingletons.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/msingletons.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/msingletons.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/msingletons.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/msingletons.o: core/mrcstring.h core/mstring.h
../bld/utils/msingletons.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/msingletons.o: core/mrcstringtable.h core/mstring.h
../bld/utils/msingletons.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/msingletons.o: io/minputsource.h io/moutstream.h
../bld/utils/msingletons.o: io/mstroutstream.h io/moutstream.h
../bld/utils/msingletons.o: nodes/mfilter.h nodes/mvar.h
../bld/utils/msingletons.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/utils/msingletons.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/utils/msingletons.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/utils/msingletons.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/msingletons.o: nodes/mvarnode.h parser/mparser.h
../bld/utils/msingletons.o: parser/mtokenizer.h parser/mtoken.h
../bld/utils/msingletons.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/msingletons.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/msingletons.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/msingletons.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/msingletons.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/msingletons.o: utils/mlist.h utils/mcollection.h
../bld/utils/msingletons.o: utils/mbintree.h utils/mcollection.h
../bld/utils/msingletons.o: utils/mlinkedlist.h utils/mlist.h
../bld/utils/msingletons.o: utils/mlibrary.h utils/mmemutils.h
../bld/utils/msingletons.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/msingletons.o: utils/msingletons.h utils/mtable.h
../bld/utils/msingletons.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mtable.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/utils/mtable.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/mtable.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/utils/mtable.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/utils/mtable.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/mtable.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/mtable.o: core/mstring.h core/mstringbuffer.h
../bld/utils/mtable.o: core/mstringfactory.h io/minputsource.h
../bld/utils/mtable.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/utils/mtable.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mtable.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/mtable.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/mtable.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mtable.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/utils/mtable.o: parser/mtoken.h parser/mtagparser.h
../bld/utils/mtable.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mtable.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mtable.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mtable.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mtable.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/utils/mtable.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mtable.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/utils/mtable.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mtable.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mtable.o: utils/mtable.h
../bld/utils/mtreetable.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mtreetable.o: core/mcontext.h core/merror.h core/miterator.h
../bld/utils/mtreetable.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/utils/mtreetable.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/utils/mtreetable.o: core/mrcstring.h core/mstring.h
../bld/utils/mtreetable.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/utils/mtreetable.o: core/mrcstringtable.h core/mstring.h
../bld/utils/mtreetable.o: core/mstringbuffer.h core/mstringfactory.h
../bld/utils/mtreetable.o: io/minputsource.h io/moutstream.h
../bld/utils/mtreetable.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/utils/mtreetable.o: nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mtreetable.o: nodes/mfilternode.h nodes/mfreetext.h
../bld/utils/mtreetable.o: nodes/mnode.h nodes/mnode.h nodes/mnodelist.h
../bld/utils/mtreetable.o: nodes/mtagnode.h nodes/mvar.h nodes/mvariterator.h
../bld/utils/mtreetable.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/utils/mtreetable.o: parser/mparser.h parser/mtokenizer.h
../bld/utils/mtreetable.o: parser/mtoken.h parser/mtagparser.h
../bld/utils/mtreetable.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mtreetable.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mtreetable.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mtreetable.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mtreetable.o: utils/marraylist.h utils/mlist.h
../bld/utils/mtreetable.o: utils/mcollection.h utils/mbintree.h
../bld/utils/mtreetable.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mtreetable.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/utils/mtreetable.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mtreetable.o: utils/msingletons.h utils/mtable.h
../bld/utils/mtreetable.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mutils.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/utils/mutils.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/mutils.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/utils/mutils.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/utils/mutils.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/mutils.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/mutils.o: core/mstring.h core/mstringbuffer.h
../bld/utils/mutils.o: core/mstringfactory.h io/minputsource.h
../bld/utils/mutils.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/utils/mutils.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mutils.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/mutils.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/mutils.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/utils/mutils.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/utils/mutils.o: parser/mtoken.h parser/mtagparser.h
../bld/utils/mutils.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mutils.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mutils.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mutils.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mutils.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/utils/mutils.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mutils.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/utils/mutils.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mutils.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mutils.o: utils/mtable.h
../bld/core/mclasses.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/core/mclasses.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/mclasses.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/core/mclasses.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/core/mclasses.o: core/mstring.h core/mrcstringfactory.h
../bld/core/mclasses.o: core/mstringfactory.h core/mrcstringtable.h
../bld/core/mclasses.o: core/mstring.h core/mstringbuffer.h
../bld/core/mclasses.o: core/mstringfactory.h io/minputsource.h
../bld/core/mclasses.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/core/mclasses.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/core/mclasses.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/core/mclasses.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/core/mclasses.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/mclasses.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/core/mclasses.o: parser/mtoken.h parser/mtagparser.h
../bld/core/mclasses.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mclasses.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mclasses.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mclasses.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mclasses.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/core/mclasses.o: utils/mbintree.h utils/mcollection.h
../bld/core/mclasses.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/core/mclasses.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/mclasses.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/mclasses.o: utils/mtable.h
../bld/core/merror.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/core/merror.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/merror.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/core/merror.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/core/merror.o: core/mstring.h core/mrcstringfactory.h
../bld/core/merror.o: core/mstringfactory.h core/mrcstringtable.h
../bld/core/merror.o: core/mstring.h core/mstringbuffer.h
../bld/core/merror.o: core/mstringfactory.h io/minputsource.h io/moutstream.h
../bld/core/merror.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/core/merror.o: nodes/mvar.h nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/merror.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/merror.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/core/merror.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/merror.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/core/merror.o: parser/mtoken.h parser/mtagparser.h
../bld/core/merror.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/merror.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/merror.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/merror.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/merror.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/core/merror.o: utils/mbintree.h utils/mcollection.h
../bld/core/merror.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/core/merror.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/merror.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/merror.o: utils/mtable.h
../bld/core/miterator.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/miterator.o: core/mcontext.h core/merror.h core/miterator.h
../bld/core/miterator.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/core/miterator.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/core/miterator.o: core/mrcstring.h core/mstring.h
../bld/core/miterator.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/core/miterator.o: core/mrcstringtable.h core/mstring.h
../bld/core/miterator.o: core/mstringbuffer.h core/mstringfactory.h
../bld/core/miterator.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/core/miterator.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/core/miterator.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/miterator.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/miterator.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/core/miterator.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/miterator.o: nodes/mvarnode.h parser/mparser.h
../bld/core/miterator.o: parser/mtokenizer.h parser/mtoken.h
../bld/core/miterator.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/miterator.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/miterator.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/miterator.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/miterator.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/miterator.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/core/miterator.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/miterator.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/core/miterator.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/miterator.o: utils/msingletons.h utils/mtable.h
../bld/core/miterator.o: utils/mtreetable.h utils/mtable.h
../bld/core/mobject.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/core/mobject.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/mobject.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/core/mobject.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/core/mobject.o: core/mstring.h core/mrcstringfactory.h
../bld/core/mobject.o: core/mstringfactory.h core/mrcstringtable.h
../bld/core/mobject.o: core/mstring.h core/mstringbuffer.h
../bld/core/mobject.o: core/mstringfactory.h io/minputsource.h
../bld/core/mobject.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/core/mobject.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/core/mobject.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/core/mobject.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/core/mobject.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/mobject.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/core/mobject.o: parser/mtoken.h parser/mtagparser.h
../bld/core/mobject.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mobject.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mobject.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mobject.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mobject.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/core/mobject.o: utils/mbintree.h utils/mcollection.h
../bld/core/mobject.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/core/mobject.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/mobject.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/mobject.o: utils/mtable.h
../bld/core/mprototype.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mprototype.o: core/mcontext.h core/merror.h core/miterator.h
../bld/core/mprototype.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/core/mprototype.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/core/mprototype.o: core/mrcstring.h core/mstring.h
../bld/core/mprototype.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/core/mprototype.o: core/mrcstringtable.h core/mstring.h
../bld/core/mprototype.o: core/mstringbuffer.h core/mstringfactory.h
../bld/core/mprototype.o: io/minputsource.h io/moutstream.h
../bld/core/mprototype.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/core/mprototype.o: nodes/mvar.h nodes/mfilterlibrary.h
../bld/core/mprototype.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/core/mprototype.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/core/mprototype.o: nodes/mvar.h nodes/mvariterator.h
../bld/core/mprototype.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/core/mprototype.o: parser/mparser.h parser/mtokenizer.h
../bld/core/mprototype.o: parser/mtoken.h parser/mtagparser.h
../bld/core/mprototype.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mprototype.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mprototype.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mprototype.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mprototype.o: utils/marraylist.h utils/mlist.h
../bld/core/mprototype.o: utils/mcollection.h utils/mbintree.h
../bld/core/mprototype.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/mprototype.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/core/mprototype.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mprototype.o: utils/msingletons.h utils/mtable.h
../bld/core/mprototype.o: utils/mtreetable.h utils/mtable.h
../bld/core/mrcstring.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mrcstring.o: core/mcontext.h core/merror.h core/miterator.h
../bld/core/mrcstring.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/core/mrcstring.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/core/mrcstring.o: core/mrcstring.h core/mstring.h
../bld/core/mrcstring.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/core/mrcstring.o: core/mrcstringtable.h core/mstring.h
../bld/core/mrcstring.o: core/mstringbuffer.h core/mstringfactory.h
../bld/core/mrcstring.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/core/mrcstring.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/core/mrcstring.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/mrcstring.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/mrcstring.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/core/mrcstring.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/mrcstring.o: nodes/mvarnode.h parser/mparser.h
../bld/core/mrcstring.o: parser/mtokenizer.h parser/mtoken.h
../bld/core/mrcstring.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/mrcstring.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/mrcstring.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/mrcstring.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/mrcstring.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/mrcstring.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/core/mrcstring.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/mrcstring.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/core/mrcstring.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mrcstring.o: utils/msingletons.h utils/mtable.h
../bld/core/mrcstring.o: utils/mtreetable.h utils/mtable.h
../bld/core/mrcstringfactory.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mrcstringfactory.o: core/mcontext.h core/merror.h
../bld/core/mrcstringfactory.o: core/miterator.h core/mobject.h
../bld/core/mrcstringfactory.o: core/mprototype.h utils/mutils.h
../bld/core/mrcstringfactory.o: core/mnumber.h core/mobject.h
../bld/core/mrcstringfactory.o: core/mprototype.h core/mrcstring.h
../bld/core/mrcstringfactory.o: core/mstring.h core/mrcstringfactory.h
../bld/core/mrcstringfactory.o: core/mstringfactory.h core/mrcstringtable.h
../bld/core/mrcstringfactory.o: core/mstring.h core/mstringbuffer.h
../bld/core/mrcstringfactory.o: core/mstringfactory.h io/minputsource.h
../bld/core/mrcstringfactory.o: io/moutstream.h io/mstroutstream.h
../bld/core/mrcstringfactory.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/core/mrcstringfactory.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/mrcstringfactory.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/mrcstringfactory.o: nodes/mnodelist.h nodes/mtagnode.h
../bld/core/mrcstringfactory.o: nodes/mvar.h nodes/mvariterator.h
../bld/core/mrcstringfactory.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/core/mrcstringfactory.o: parser/mparser.h parser/mtokenizer.h
../bld/core/mrcstringfactory.o: parser/mtoken.h parser/mtagparser.h
../bld/core/mrcstringfactory.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mrcstringfactory.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mrcstringfactory.o: renderer/mrenderer.h
../bld/core/mrcstringfactory.o: resolver/mtemplateloader.h
../bld/core/mrcstringfactory.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mrcstringfactory.o: utils/marraylist.h utils/mlist.h
../bld/core/mrcstringfactory.o: utils/mcollection.h utils/mbintree.h
../bld/core/mrcstringfactory.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/mrcstringfactory.o: utils/mlist.h utils/mlibrary.h
../bld/core/mrcstringfactory.o: utils/mmemutils.h utils/mrawarray.h
../bld/core/mrcstringfactory.o: utils/mrawlist.h utils/msingletons.h
../bld/core/mrcstringfactory.o: utils/mtable.h utils/mtreetable.h
../bld/core/mrcstringfactory.o: utils/mtable.h
../bld/core/mrcstringtable.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mrcstringtable.o: core/mcontext.h core/merror.h core/miterator.h
../bld/core/mrcstringtable.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/core/mrcstringtable.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/core/mrcstringtable.o: core/mrcstring.h core/mstring.h
../bld/core/mrcstringtable.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/core/mrcstringtable.o: core/mrcstringtable.h core/mstring.h
../bld/core/mrcstringtable.o: core/mstringbuffer.h core/mstringfactory.h
../bld/core/mrcstringtable.o: io/minputsource.h io/moutstream.h
../bld/core/mrcstringtable.o: io/mstroutstream.h io/moutstream.h
../bld/core/mrcstringtable.o: nodes/mfilter.h nodes/mvar.h
../bld/core/mrcstringtable.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/mrcstringtable.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/mrcstringtable.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/core/mrcstringtable.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/mrcstringtable.o: nodes/mvarnode.h parser/mparser.h
../bld/core/mrcstringtable.o: parser/mtokenizer.h parser/mtoken.h
../bld/core/mrcstringtable.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/mrcstringtable.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/mrcstringtable.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/mrcstringtable.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/mrcstringtable.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/mrcstringtable.o: utils/mlist.h utils/mcollection.h
../bld/core/mrcstringtable.o: utils/mbintree.h utils/mcollection.h
../bld/core/mrcstringtable.o: utils/mlinkedlist.h utils/mlist.h
../bld/core/mrcstringtable.o: utils/mlibrary.h utils/mmemutils.h
../bld/core/mrcstringtable.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mrcstringtable.o: utils/msingletons.h utils/mtable.h
../bld/core/mrcstringtable.o: utils/mtreetable.h utils/mtable.h
../bld/core/mstringbuffer.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mstringbuffer.o: core/mcontext.h core/merror.h core/miterator.h
../bld/core/mstringbuffer.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/core/mstringbuffer.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/core/mstringbuffer.o: core/mrcstring.h core/mstring.h
../bld/core/mstringbuffer.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/core/mstringbuffer.o: core/mrcstringtable.h core/mstring.h
../bld/core/mstringbuffer.o: core/mstringbuffer.h core/mstringfactory.h
../bld/core/mstringbuffer.o: io/minputsource.h io/moutstream.h
../bld/core/mstringbuffer.o: io/mstroutstream.h io/moutstream.h
../bld/core/mstringbuffer.o: nodes/mfilter.h nodes/mvar.h
../bld/core/mstringbuffer.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/mstringbuffer.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/mstringbuffer.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/core/mstringbuffer.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/mstringbuffer.o: nodes/mvarnode.h parser/mparser.h
../bld/core/mstringbuffer.o: parser/mtokenizer.h parser/mtoken.h
../bld/core/mstringbuffer.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/mstringbuffer.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/mstringbuffer.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/mstringbuffer.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/mstringbuffer.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/mstringbuffer.o: utils/mlist.h utils/mcollection.h
../bld/core/mstringbuffer.o: utils/mbintree.h utils/mcollection.h
../bld/core/mstringbuffer.o: utils/mlinkedlist.h utils/mlist.h
../bld/core/mstringbuffer.o: utils/mlibrary.h utils/mmemutils.h
../bld/core/mstringbuffer.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mstringbuffer.o: utils/msingletons.h utils/mtable.h
../bld/core/mstringbuffer.o: utils/mtreetable.h utils/mtable.h
../bld/core/mstring.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/core/mstring.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/mstring.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/core/mstring.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/core/mstring.o: core/mstring.h core/mrcstringfactory.h
../bld/core/mstring.o: core/mstringfactory.h core/mrcstringtable.h
../bld/core/mstring.o: core/mstring.h core/mstringbuffer.h
../bld/core/mstring.o: core/mstringfactory.h io/minputsource.h
../bld/core/mstring.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/core/mstring.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/core/mstring.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/core/mstring.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/core/mstring.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/mstring.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/core/mstring.o: parser/mtoken.h parser/mtagparser.h
../bld/core/mstring.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mstring.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mstring.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mstring.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mstring.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/core/mstring.o: utils/mbintree.h utils/mcollection.h
../bld/core/mstring.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/core/mstring.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/mstring.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/mstring.o: utils/mtable.h
../bld/core/mstringfactory.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mstringfactory.o: core/mcontext.h core/merror.h core/miterator.h
../bld/core/mstringfactory.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/core/mstringfactory.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/core/mstringfactory.o: core/mrcstring.h core/mstring.h
../bld/core/mstringfactory.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/core/mstringfactory.o: core/mrcstringtable.h core/mstring.h
../bld/core/mstringfactory.o: core/mstringbuffer.h core/mstringfactory.h
../bld/core/mstringfactory.o: io/minputsource.h io/moutstream.h
../bld/core/mstringfactory.o: io/mstroutstream.h io/moutstream.h
../bld/core/mstringfactory.o: nodes/mfilter.h nodes/mvar.h
../bld/core/mstringfactory.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/mstringfactory.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/mstringfactory.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/core/mstringfactory.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/core/mstringfactory.o: nodes/mvarnode.h parser/mparser.h
../bld/core/mstringfactory.o: parser/mtokenizer.h parser/mtoken.h
../bld/core/mstringfactory.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/mstringfactory.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/mstringfactory.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/mstringfactory.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/mstringfactory.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/mstringfactory.o: utils/mlist.h utils/mcollection.h
../bld/core/mstringfactory.o: utils/mbintree.h utils/mcollection.h
../bld/core/mstringfactory.o: utils/mlinkedlist.h utils/mlist.h
../bld/core/mstringfactory.o: utils/mlibrary.h utils/mmemutils.h
../bld/core/mstringfactory.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mstringfactory.o: utils/msingletons.h utils/mtable.h
../bld/core/mstringfactory.o: utils/mtreetable.h utils/mtable.h
../bld/io/moutstream.o: io/moutstream.h
../bld/io/mstroutstream.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/io/mstroutstream.o: core/mcontext.h core/merror.h core/miterator.h
../bld/io/mstroutstream.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/io/mstroutstream.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/io/mstroutstream.o: core/mrcstring.h core/mstring.h
../bld/io/mstroutstream.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/io/mstroutstream.o: core/mrcstringtable.h core/mstring.h
../bld/io/mstroutstream.o: core/mstringbuffer.h core/mstringfactory.h
../bld/io/mstroutstream.o: io/minputsource.h io/moutstream.h
../bld/io/mstroutstream.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/io/mstroutstream.o: nodes/mvar.h nodes/mfilterlibrary.h
../bld/io/mstroutstream.o: nodes/mfilternode.h nodes/mfreetext.h
../bld/io/mstroutstream.o: nodes/mnode.h nodes/mnode.h nodes/mnodelist.h
../bld/io/mstroutstream.o: nodes/mtagnode.h nodes/mvar.h nodes/mvariterator.h
../bld/io/mstroutstream.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/io/mstroutstream.o: parser/mparser.h parser/mtokenizer.h
../bld/io/mstroutstream.o: parser/mtoken.h parser/mtagparser.h
../bld/io/mstroutstream.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/io/mstroutstream.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/io/mstroutstream.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/io/mstroutstream.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/io/mstroutstream.o: utils/marraylist.h utils/mlist.h
../bld/io/mstroutstream.o: utils/mcollection.h utils/mbintree.h
../bld/io/mstroutstream.o: utils/mcollection.h utils/mlinkedlist.h
../bld/io/mstroutstream.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/io/mstroutstream.o: utils/mrawarray.h utils/mrawlist.h
../bld/io/mstroutstream.o: utils/msingletons.h utils/mtable.h
../bld/io/mstroutstream.o: utils/mtreetable.h utils/mtable.h
../bld/parser/mparser.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/parser/mparser.o: core/mcontext.h core/merror.h core/miterator.h
../bld/parser/mparser.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/parser/mparser.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/parser/mparser.o: core/mrcstring.h core/mstring.h
../bld/parser/mparser.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/parser/mparser.o: core/mrcstringtable.h core/mstring.h
../bld/parser/mparser.o: core/mstringbuffer.h core/mstringfactory.h
../bld/parser/mparser.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/parser/mparser.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/parser/mparser.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/parser/mparser.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/parser/mparser.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/parser/mparser.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/parser/mparser.o: nodes/mvarnode.h parser/mparser.h
../bld/parser/mparser.o: parser/mtokenizer.h parser/mtoken.h
../bld/parser/mparser.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/parser/mparser.o: parser/mtoken.h parser/mtokenizer.h
../bld/parser/mparser.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/parser/mparser.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/parser/mparser.o: resolver/mvarresolver.h utils/marraylist.h
../bld/parser/mparser.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/parser/mparser.o: utils/mcollection.h utils/mlinkedlist.h
../bld/parser/mparser.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/parser/mparser.o: utils/mrawarray.h utils/mrawlist.h
../bld/parser/mparser.o: utils/msingletons.h utils/mtable.h
../bld/parser/mparser.o: utils/mtreetable.h utils/mtable.h
../bld/parser/mtagparserlibrary.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/parser/mtagparserlibrary.o: core/mcontext.h core/merror.h
../bld/parser/mtagparserlibrary.o: core/miterator.h core/mobject.h
../bld/parser/mtagparserlibrary.o: core/mprototype.h utils/mutils.h
../bld/parser/mtagparserlibrary.o: core/mnumber.h core/mobject.h
../bld/parser/mtagparserlibrary.o: core/mprototype.h core/mrcstring.h
../bld/parser/mtagparserlibrary.o: core/mstring.h core/mrcstringfactory.h
../bld/parser/mtagparserlibrary.o: core/mstringfactory.h
../bld/parser/mtagparserlibrary.o: core/mrcstringtable.h core/mstring.h
../bld/parser/mtagparserlibrary.o: core/mstringbuffer.h core/mstringfactory.h
../bld/parser/mtagparserlibrary.o: io/minputsource.h io/moutstream.h
../bld/parser/mtagparserlibrary.o: io/mstroutstream.h io/moutstream.h
../bld/parser/mtagparserlibrary.o: nodes/mfilter.h nodes/mvar.h
../bld/parser/mtagparserlibrary.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/parser/mtagparserlibrary.o: nodes/mfreetext.h nodes/mnode.h
../bld/parser/mtagparserlibrary.o: nodes/mnode.h nodes/mnodelist.h
../bld/parser/mtagparserlibrary.o: nodes/mtagnode.h nodes/mvar.h
../bld/parser/mtagparserlibrary.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/parser/mtagparserlibrary.o: nodes/mvarnode.h parser/mparser.h
../bld/parser/mtagparserlibrary.o: parser/mtokenizer.h parser/mtoken.h
../bld/parser/mtagparserlibrary.o: parser/mtagparser.h
../bld/parser/mtagparserlibrary.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/parser/mtagparserlibrary.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/parser/mtagparserlibrary.o: renderer/mrenderer.h
../bld/parser/mtagparserlibrary.o: resolver/mtemplateloader.h
../bld/parser/mtagparserlibrary.o: resolver/mtmplctx.h
../bld/parser/mtagparserlibrary.o: resolver/mvarresolver.h utils/marraylist.h
../bld/parser/mtagparserlibrary.o: utils/mlist.h utils/mcollection.h
../bld/parser/mtagparserlibrary.o: utils/mbintree.h utils/mcollection.h
../bld/parser/mtagparserlibrary.o: utils/mlinkedlist.h utils/mlist.h
../bld/parser/mtagparserlibrary.o: utils/mlibrary.h utils/mmemutils.h
../bld/parser/mtagparserlibrary.o: utils/mrawarray.h utils/mrawlist.h
../bld/parser/mtagparserlibrary.o: utils/msingletons.h utils/mtable.h
../bld/parser/mtagparserlibrary.o: utils/mtreetable.h utils/mtable.h
../bld/parser/mtoken.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/parser/mtoken.o: core/merror.h core/miterator.h core/mobject.h
../bld/parser/mtoken.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/parser/mtoken.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/parser/mtoken.o: core/mstring.h core/mrcstringfactory.h
../bld/parser/mtoken.o: core/mstringfactory.h core/mrcstringtable.h
../bld/parser/mtoken.o: core/mstring.h core/mstringbuffer.h
../bld/parser/mtoken.o: core/mstringfactory.h io/minputsource.h
../bld/parser/mtoken.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/parser/mtoken.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/parser/mtoken.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/parser/mtoken.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/parser/mtoken.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/parser/mtoken.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/parser/mtoken.o: parser/mtoken.h parser/mtagparser.h
../bld/parser/mtoken.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/parser/mtoken.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/parser/mtoken.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/parser/mtoken.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/parser/mtoken.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/parser/mtoken.o: utils/mbintree.h utils/mcollection.h
../bld/parser/mtoken.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/parser/mtoken.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/parser/mtoken.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/parser/mtoken.o: utils/mtable.h
../bld/parser/mtokenizer.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/parser/mtokenizer.o: core/mcontext.h core/merror.h core/miterator.h
../bld/parser/mtokenizer.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/parser/mtokenizer.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/parser/mtokenizer.o: core/mrcstring.h core/mstring.h
../bld/parser/mtokenizer.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/parser/mtokenizer.o: core/mrcstringtable.h core/mstring.h
../bld/parser/mtokenizer.o: core/mstringbuffer.h core/mstringfactory.h
../bld/parser/mtokenizer.o: io/minputsource.h io/moutstream.h
../bld/parser/mtokenizer.o: io/mstroutstream.h io/moutstream.h
../bld/parser/mtokenizer.o: nodes/mfilter.h nodes/mvar.h
../bld/parser/mtokenizer.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/parser/mtokenizer.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/parser/mtokenizer.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/parser/mtokenizer.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/parser/mtokenizer.o: nodes/mvarnode.h parser/mparser.h
../bld/parser/mtokenizer.o: parser/mtokenizer.h parser/mtoken.h
../bld/parser/mtokenizer.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/parser/mtokenizer.o: parser/mtoken.h parser/mtokenizer.h
../bld/parser/mtokenizer.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/parser/mtokenizer.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/parser/mtokenizer.o: resolver/mvarresolver.h utils/marraylist.h
../bld/parser/mtokenizer.o: utils/mlist.h utils/mcollection.h
../bld/parser/mtokenizer.o: utils/mbintree.h utils/mcollection.h
../bld/parser/mtokenizer.o: utils/mlinkedlist.h utils/mlist.h
../bld/parser/mtokenizer.o: utils/mlibrary.h utils/mmemutils.h
../bld/parser/mtokenizer.o: utils/mrawarray.h utils/mrawlist.h
../bld/parser/mtokenizer.o: utils/msingletons.h utils/mtable.h
../bld/parser/mtokenizer.o: utils/mtreetable.h utils/mtable.h
../bld/parser/mtokenlists.o: parser/mtokenlists.h mfwddefs.h parser/mtoken.h
../bld/nodes/mfilter.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/nodes/mfilter.o: core/merror.h core/miterator.h core/mobject.h
../bld/nodes/mfilter.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/nodes/mfilter.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/nodes/mfilter.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mfilter.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mfilter.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mfilter.o: core/mstringfactory.h io/minputsource.h
../bld/nodes/mfilter.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/nodes/mfilter.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/nodes/mfilter.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/nodes/mfilter.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mfilter.o: nodes/mvar.h nodes/mvariterator.h nodes/mvarlibrary.h
../bld/nodes/mfilter.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/nodes/mfilter.o: parser/mtoken.h parser/mtagparser.h
../bld/nodes/mfilter.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mfilter.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mfilter.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mfilter.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mfilter.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/nodes/mfilter.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mfilter.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/nodes/mfilter.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mfilter.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/nodes/mfilter.o: utils/mtable.h
../bld/nodes/mfilterlibrary.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mfilterlibrary.o: core/mcontext.h core/merror.h core/miterator.h
../bld/nodes/mfilterlibrary.o: core/mobject.h core/mprototype.h
../bld/nodes/mfilterlibrary.o: utils/mutils.h core/mnumber.h core/mobject.h
../bld/nodes/mfilterlibrary.o: core/mprototype.h core/mrcstring.h
../bld/nodes/mfilterlibrary.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mfilterlibrary.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mfilterlibrary.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mfilterlibrary.o: core/mstringfactory.h io/minputsource.h
../bld/nodes/mfilterlibrary.o: io/moutstream.h io/mstroutstream.h
../bld/nodes/mfilterlibrary.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/nodes/mfilterlibrary.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mfilterlibrary.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mfilterlibrary.o: nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mfilterlibrary.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mfilterlibrary.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mfilterlibrary.o: parser/mparser.h parser/mtokenizer.h
../bld/nodes/mfilterlibrary.o: parser/mtoken.h parser/mtagparser.h
../bld/nodes/mfilterlibrary.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mfilterlibrary.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mfilterlibrary.o: renderer/mrenderer.h
../bld/nodes/mfilterlibrary.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mfilterlibrary.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mfilterlibrary.o: utils/mlist.h utils/mcollection.h
../bld/nodes/mfilterlibrary.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mfilterlibrary.o: utils/mlinkedlist.h utils/mlist.h
../bld/nodes/mfilterlibrary.o: utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mfilterlibrary.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mfilterlibrary.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mfilterlibrary.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mfilternode.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mfilternode.o: core/mcontext.h core/merror.h core/miterator.h
../bld/nodes/mfilternode.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/nodes/mfilternode.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/nodes/mfilternode.o: core/mrcstring.h core/mstring.h
../bld/nodes/mfilternode.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/nodes/mfilternode.o: core/mrcstringtable.h core/mstring.h
../bld/nodes/mfilternode.o: core/mstringbuffer.h core/mstringfactory.h
../bld/nodes/mfilternode.o: io/minputsource.h io/moutstream.h
../bld/nodes/mfilternode.o: io/mstroutstream.h io/moutstream.h
../bld/nodes/mfilternode.o: nodes/mfilter.h nodes/mvar.h
../bld/nodes/mfilternode.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mfilternode.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mfilternode.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/nodes/mfilternode.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/nodes/mfilternode.o: nodes/mvarnode.h parser/mparser.h
../bld/nodes/mfilternode.o: parser/mtokenizer.h parser/mtoken.h
../bld/nodes/mfilternode.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mfilternode.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mfilternode.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mfilternode.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mfilternode.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mfilternode.o: utils/mlist.h utils/mcollection.h
../bld/nodes/mfilternode.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mfilternode.o: utils/mlinkedlist.h utils/mlist.h
../bld/nodes/mfilternode.o: utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mfilternode.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mfilternode.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mfilternode.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mfreetext.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mfreetext.o: core/mcontext.h core/merror.h core/miterator.h
../bld/nodes/mfreetext.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/nodes/mfreetext.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/nodes/mfreetext.o: core/mrcstring.h core/mstring.h
../bld/nodes/mfreetext.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/nodes/mfreetext.o: core/mrcstringtable.h core/mstring.h
../bld/nodes/mfreetext.o: core/mstringbuffer.h core/mstringfactory.h
../bld/nodes/mfreetext.o: io/minputsource.h io/moutstream.h
../bld/nodes/mfreetext.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/nodes/mfreetext.o: nodes/mvar.h nodes/mfilterlibrary.h
../bld/nodes/mfreetext.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/nodes/mfreetext.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mfreetext.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mfreetext.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mfreetext.o: parser/mparser.h parser/mtokenizer.h
../bld/nodes/mfreetext.o: parser/mtoken.h parser/mtagparser.h
../bld/nodes/mfreetext.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mfreetext.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mfreetext.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mfreetext.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mfreetext.o: utils/marraylist.h utils/mlist.h
../bld/nodes/mfreetext.o: utils/mcollection.h utils/mbintree.h
../bld/nodes/mfreetext.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mfreetext.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mfreetext.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mfreetext.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mfreetext.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mnode.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/nodes/mnode.o: core/merror.h core/miterator.h core/mobject.h
../bld/nodes/mnode.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/nodes/mnode.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/nodes/mnode.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mnode.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mnode.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mnode.o: core/mstringfactory.h io/minputsource.h io/moutstream.h
../bld/nodes/mnode.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/nodes/mnode.o: nodes/mvar.h nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mnode.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mnode.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/nodes/mnode.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/nodes/mnode.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/nodes/mnode.o: parser/mtoken.h parser/mtagparser.h
../bld/nodes/mnode.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mnode.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mnode.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mnode.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mnode.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/nodes/mnode.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mnode.o: utils/mlinkedlist.h utils/mlist.h utils/mlibrary.h
../bld/nodes/mnode.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mnode.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/nodes/mnode.o: utils/mtable.h
../bld/nodes/mnodelist.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mnodelist.o: core/mcontext.h core/merror.h core/miterator.h
../bld/nodes/mnodelist.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/nodes/mnodelist.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/nodes/mnodelist.o: core/mrcstring.h core/mstring.h
../bld/nodes/mnodelist.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/nodes/mnodelist.o: core/mrcstringtable.h core/mstring.h
../bld/nodes/mnodelist.o: core/mstringbuffer.h core/mstringfactory.h
../bld/nodes/mnodelist.o: io/minputsource.h io/moutstream.h
../bld/nodes/mnodelist.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/nodes/mnodelist.o: nodes/mvar.h nodes/mfilterlibrary.h
../bld/nodes/mnodelist.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/nodes/mnodelist.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mnodelist.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mnodelist.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mnodelist.o: parser/mparser.h parser/mtokenizer.h
../bld/nodes/mnodelist.o: parser/mtoken.h parser/mtagparser.h
../bld/nodes/mnodelist.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mnodelist.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mnodelist.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mnodelist.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mnodelist.o: utils/marraylist.h utils/mlist.h
../bld/nodes/mnodelist.o: utils/mcollection.h utils/mbintree.h
../bld/nodes/mnodelist.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mnodelist.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mnodelist.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mnodelist.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mnodelist.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mtagnode.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mtagnode.o: core/mcontext.h core/merror.h core/miterator.h
../bld/nodes/mtagnode.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/nodes/mtagnode.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/nodes/mtagnode.o: core/mrcstring.h core/mstring.h
../bld/nodes/mtagnode.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/nodes/mtagnode.o: core/mrcstringtable.h core/mstring.h
../bld/nodes/mtagnode.o: core/mstringbuffer.h core/mstringfactory.h
../bld/nodes/mtagnode.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/nodes/mtagnode.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/nodes/mtagnode.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mtagnode.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mtagnode.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/nodes/mtagnode.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/nodes/mtagnode.o: nodes/mvarnode.h parser/mparser.h
../bld/nodes/mtagnode.o: parser/mtokenizer.h parser/mtoken.h
../bld/nodes/mtagnode.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mtagnode.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mtagnode.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mtagnode.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mtagnode.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mtagnode.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/nodes/mtagnode.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mtagnode.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mtagnode.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mtagnode.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mtagnode.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mvar.o: mangopub.h mfwddefs.h core/mclasses.h core/mcontext.h
../bld/nodes/mvar.o: core/merror.h core/miterator.h core/mobject.h
../bld/nodes/mvar.o: core/mprototype.h utils/mutils.h core/mnumber.h
../bld/nodes/mvar.o: core/mobject.h core/mprototype.h core/mrcstring.h
../bld/nodes/mvar.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mvar.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mvar.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mvar.o: core/mstringfactory.h io/minputsource.h io/moutstream.h
../bld/nodes/mvar.o: io/mstroutstream.h io/moutstream.h nodes/mfilter.h
../bld/nodes/mvar.o: nodes/mvar.h nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mvar.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mvar.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/nodes/mvar.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/nodes/mvar.o: nodes/mvarnode.h parser/mparser.h parser/mtokenizer.h
../bld/nodes/mvar.o: parser/mtoken.h parser/mtagparser.h
../bld/nodes/mvar.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mvar.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mvar.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mvar.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mvar.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/nodes/mvar.o: utils/mbintree.h utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mvar.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mvar.o: utils/mrawarray.h utils/mrawlist.h utils/msingletons.h
../bld/nodes/mvar.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/nodes/mvarlibrary.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mvarlibrary.o: core/mcontext.h core/merror.h core/miterator.h
../bld/nodes/mvarlibrary.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/nodes/mvarlibrary.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/nodes/mvarlibrary.o: core/mrcstring.h core/mstring.h
../bld/nodes/mvarlibrary.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/nodes/mvarlibrary.o: core/mrcstringtable.h core/mstring.h
../bld/nodes/mvarlibrary.o: core/mstringbuffer.h core/mstringfactory.h
../bld/nodes/mvarlibrary.o: io/minputsource.h io/moutstream.h
../bld/nodes/mvarlibrary.o: io/mstroutstream.h io/moutstream.h
../bld/nodes/mvarlibrary.o: nodes/mfilter.h nodes/mvar.h
../bld/nodes/mvarlibrary.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mvarlibrary.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mvarlibrary.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/nodes/mvarlibrary.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/nodes/mvarlibrary.o: nodes/mvarnode.h parser/mparser.h
../bld/nodes/mvarlibrary.o: parser/mtokenizer.h parser/mtoken.h
../bld/nodes/mvarlibrary.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mvarlibrary.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mvarlibrary.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mvarlibrary.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mvarlibrary.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mvarlibrary.o: utils/mlist.h utils/mcollection.h
../bld/nodes/mvarlibrary.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mvarlibrary.o: utils/mlinkedlist.h utils/mlist.h
../bld/nodes/mvarlibrary.o: utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mvarlibrary.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mvarlibrary.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mvarlibrary.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mvarnode.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mvarnode.o: core/mcontext.h core/merror.h core/miterator.h
../bld/nodes/mvarnode.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/nodes/mvarnode.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/nodes/mvarnode.o: core/mrcstring.h core/mstring.h
../bld/nodes/mvarnode.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/nodes/mvarnode.o: core/mrcstringtable.h core/mstring.h
../bld/nodes/mvarnode.o: core/mstringbuffer.h core/mstringfactory.h
../bld/nodes/mvarnode.o: io/minputsource.h io/moutstream.h io/mstroutstream.h
../bld/nodes/mvarnode.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/nodes/mvarnode.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mvarnode.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mvarnode.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/nodes/mvarnode.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/nodes/mvarnode.o: nodes/mvarnode.h parser/mparser.h
../bld/nodes/mvarnode.o: parser/mtokenizer.h parser/mtoken.h
../bld/nodes/mvarnode.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mvarnode.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mvarnode.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mvarnode.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mvarnode.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mvarnode.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/nodes/mvarnode.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mvarnode.o: utils/mlist.h utils/mlibrary.h utils/mmemutils.h
../bld/nodes/mvarnode.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mvarnode.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mvarnode.o: utils/mtreetable.h utils/mtable.h
../bld/renderer/mrenderer.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/renderer/mrenderer.o: core/mcontext.h core/merror.h core/miterator.h
../bld/renderer/mrenderer.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/renderer/mrenderer.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/renderer/mrenderer.o: core/mrcstring.h core/mstring.h
../bld/renderer/mrenderer.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/renderer/mrenderer.o: core/mrcstringtable.h core/mstring.h
../bld/renderer/mrenderer.o: core/mstringbuffer.h core/mstringfactory.h
../bld/renderer/mrenderer.o: io/minputsource.h io/moutstream.h
../bld/renderer/mrenderer.o: io/mstroutstream.h io/moutstream.h
../bld/renderer/mrenderer.o: nodes/mfilter.h nodes/mvar.h
../bld/renderer/mrenderer.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/renderer/mrenderer.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/renderer/mrenderer.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/renderer/mrenderer.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/renderer/mrenderer.o: nodes/mvarnode.h parser/mparser.h
../bld/renderer/mrenderer.o: parser/mtokenizer.h parser/mtoken.h
../bld/renderer/mrenderer.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/renderer/mrenderer.o: parser/mtoken.h parser/mtokenizer.h
../bld/renderer/mrenderer.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/renderer/mrenderer.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/renderer/mrenderer.o: resolver/mvarresolver.h utils/marraylist.h
../bld/renderer/mrenderer.o: utils/mlist.h utils/mcollection.h
../bld/renderer/mrenderer.o: utils/mbintree.h utils/mcollection.h
../bld/renderer/mrenderer.o: utils/mlinkedlist.h utils/mlist.h
../bld/renderer/mrenderer.o: utils/mlibrary.h utils/mmemutils.h
../bld/renderer/mrenderer.o: utils/mrawarray.h utils/mrawlist.h
../bld/renderer/mrenderer.o: utils/msingletons.h utils/mtable.h
../bld/renderer/mrenderer.o: utils/mtreetable.h utils/mtable.h
../bld/resolver/mtmplctx.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/resolver/mtmplctx.o: core/mcontext.h core/merror.h core/miterator.h
../bld/resolver/mtmplctx.o: core/mobject.h core/mprototype.h utils/mutils.h
../bld/resolver/mtmplctx.o: core/mnumber.h core/mobject.h core/mprototype.h
../bld/resolver/mtmplctx.o: core/mrcstring.h core/mstring.h
../bld/resolver/mtmplctx.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/resolver/mtmplctx.o: core/mrcstringtable.h core/mstring.h
../bld/resolver/mtmplctx.o: core/mstringbuffer.h core/mstringfactory.h
../bld/resolver/mtmplctx.o: io/minputsource.h io/moutstream.h
../bld/resolver/mtmplctx.o: io/mstroutstream.h io/moutstream.h
../bld/resolver/mtmplctx.o: nodes/mfilter.h nodes/mvar.h
../bld/resolver/mtmplctx.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/resolver/mtmplctx.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/resolver/mtmplctx.o: nodes/mnodelist.h nodes/mtagnode.h nodes/mvar.h
../bld/resolver/mtmplctx.o: nodes/mvariterator.h nodes/mvarlibrary.h
../bld/resolver/mtmplctx.o: nodes/mvarnode.h parser/mparser.h
../bld/resolver/mtmplctx.o: parser/mtokenizer.h parser/mtoken.h
../bld/resolver/mtmplctx.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/resolver/mtmplctx.o: parser/mtoken.h parser/mtokenizer.h
../bld/resolver/mtmplctx.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/resolver/mtmplctx.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/resolver/mtmplctx.o: resolver/mvarresolver.h utils/marraylist.h
../bld/resolver/mtmplctx.o: utils/mlist.h utils/mcollection.h
../bld/resolver/mtmplctx.o: utils/mbintree.h utils/mcollection.h
../bld/resolver/mtmplctx.o: utils/mlinkedlist.h utils/mlist.h
../bld/resolver/mtmplctx.o: utils/mlibrary.h utils/mmemutils.h
../bld/resolver/mtmplctx.o: utils/mrawarray.h utils/mrawlist.h
../bld/resolver/mtmplctx.o: utils/msingletons.h utils/mtable.h
../bld/resolver/mtmplctx.o: utils/mtreetable.h utils/mtable.h
../bld/resolver/mvarresolver.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/resolver/mvarresolver.o: core/mcontext.h core/merror.h
../bld/resolver/mvarresolver.o: core/miterator.h core/mobject.h
../bld/resolver/mvarresolver.o: core/mprototype.h utils/mutils.h
../bld/resolver/mvarresolver.o: core/mnumber.h core/mobject.h
../bld/resolver/mvarresolver.o: core/mprototype.h core/mrcstring.h
../bld/resolver/mvarresolver.o: core/mstring.h core/mrcstringfactory.h
../bld/resolver/mvarresolver.o: core/mstringfactory.h core/mrcstringtable.h
../bld/resolver/mvarresolver.o: core/mstring.h core/mstringbuffer.h
../bld/resolver/mvarresolver.o: core/mstringfactory.h io/minputsource.h
../bld/resolver/mvarresolver.o: io/moutstream.h io/mstroutstream.h
../bld/resolver/mvarresolver.o: io/moutstream.h nodes/mfilter.h nodes/mvar.h
../bld/resolver/mvarresolver.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/resolver/mvarresolver.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/resolver/mvarresolver.o: nodes/mnodelist.h nodes/mtagnode.h
../bld/resolver/mvarresolver.o: nodes/mvar.h nodes/mvariterator.h
../bld/resolver/mvarresolver.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/resolver/mvarresolver.o: parser/mparser.h parser/mtokenizer.h
../bld/resolver/mvarresolver.o: parser/mtoken.h parser/mtagparser.h
../bld/resolver/mvarresolver.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/resolver/mvarresolver.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/resolver/mvarresolver.o: renderer/mrenderer.h
../bld/resolver/mvarresolver.o: resolver/mtemplateloader.h
../bld/resolver/mvarresolver.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/resolver/mvarresolver.o: utils/marraylist.h utils/mlist.h
../bld/resolver/mvarresolver.o: utils/mcollection.h utils/mbintree.h
../bld/resolver/mvarresolver.o: utils/mcollection.h utils/mlinkedlist.h
../bld/resolver/mvarresolver.o: utils/mlist.h utils/mlibrary.h
../bld/resolver/mvarresolver.o: utils/mmemutils.h utils/mrawarray.h
../bld/resolver/mvarresolver.o: utils/mrawlist.h utils/msingletons.h
../bld/resolver/mvarresolver.o: utils/mtable.h utils/mtreetable.h
../bld/resolver/mvarresolver.o: utils/mtable.h

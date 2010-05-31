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
../bld/utils/marraylist.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/marraylist.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/utils/marraylist.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/marraylist.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/marraylist.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/marraylist.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/marraylist.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/marraylist.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/marraylist.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/marraylist.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/marraylist.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/utils/marraylist.o: utils/mrawlist.h utils/msingletons.h
../bld/utils/marraylist.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/utils/mbintree.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/mbintree.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/mbintree.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/utils/mbintree.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/mbintree.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/mbintree.o: core/mstring.h core/mstringbuffer.h
../bld/utils/mbintree.o: core/mstringfactory.h io/minputsource.h
../bld/utils/mbintree.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/utils/mbintree.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mbintree.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/mbintree.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/mbintree.o: nodes/mvar.h nodes/mvariterator.h
../bld/utils/mbintree.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/utils/mbintree.o: parser/mparser.h parser/mtokenizer.h parser/mtoken.h
../bld/utils/mbintree.o: parser/mparsercontext.h parser/mtagparser.h
../bld/utils/mbintree.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mbintree.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mbintree.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mbintree.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mbintree.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/utils/mbintree.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mbintree.o: utils/mlinkedlist.h utils/mlist.h utils/mmemutils.h
../bld/utils/mbintree.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mbintree.o: utils/msingletons.h utils/mtable.h
../bld/utils/mbintree.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mcollection.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mcollection.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/mcollection.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/utils/mcollection.o: parser/mparsercontext.h parser/mtagparser.h
../bld/utils/mcollection.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mcollection.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mcollection.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mcollection.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mcollection.o: utils/marraylist.h utils/mlist.h
../bld/utils/mcollection.o: utils/mcollection.h utils/mbintree.h
../bld/utils/mcollection.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mcollection.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/utils/mcollection.o: utils/mrawlist.h utils/msingletons.h
../bld/utils/mcollection.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/utils/miterator.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/miterator.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/miterator.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/utils/miterator.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/miterator.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/miterator.o: core/mstring.h core/mstringbuffer.h
../bld/utils/miterator.o: core/mstringfactory.h io/minputsource.h
../bld/utils/miterator.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/utils/miterator.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/miterator.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/miterator.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/miterator.o: nodes/mvar.h nodes/mvariterator.h
../bld/utils/miterator.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/utils/miterator.o: parser/mparser.h parser/mtokenizer.h
../bld/utils/miterator.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/miterator.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/miterator.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/miterator.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/miterator.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/miterator.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/miterator.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/miterator.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/miterator.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/utils/miterator.o: utils/mrawlist.h utils/msingletons.h utils/mtable.h
../bld/utils/miterator.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mlinkedlist.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mlinkedlist.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/mlinkedlist.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/utils/mlinkedlist.o: parser/mparsercontext.h parser/mtagparser.h
../bld/utils/mlinkedlist.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mlinkedlist.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mlinkedlist.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mlinkedlist.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mlinkedlist.o: utils/marraylist.h utils/mlist.h
../bld/utils/mlinkedlist.o: utils/mcollection.h utils/mbintree.h
../bld/utils/mlinkedlist.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mlinkedlist.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/utils/mlinkedlist.o: utils/mrawlist.h utils/msingletons.h
../bld/utils/mlinkedlist.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/utils/mlist.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/mlist.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/mlist.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/utils/mlist.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/mlist.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mlist.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mlist.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mlist.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mlist.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mlist.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mlist.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/utils/mlist.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mlist.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mlist.o: utils/mtable.h
../bld/utils/mnumber.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/mnumber.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/mnumber.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/utils/mnumber.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/mnumber.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mnumber.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mnumber.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mnumber.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mnumber.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mnumber.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mnumber.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/utils/mnumber.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mnumber.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mnumber.o: utils/mtable.h
../bld/utils/mrawarray.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/mrawarray.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/mrawarray.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/utils/mrawarray.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/mrawarray.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/mrawarray.o: core/mstring.h core/mstringbuffer.h
../bld/utils/mrawarray.o: core/mstringfactory.h io/minputsource.h
../bld/utils/mrawarray.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/utils/mrawarray.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mrawarray.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/mrawarray.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/mrawarray.o: nodes/mvar.h nodes/mvariterator.h
../bld/utils/mrawarray.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/utils/mrawarray.o: parser/mparser.h parser/mtokenizer.h
../bld/utils/mrawarray.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/mrawarray.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mrawarray.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mrawarray.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mrawarray.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mrawarray.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mrawarray.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mrawarray.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mrawarray.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/utils/mrawarray.o: utils/mrawlist.h utils/msingletons.h utils/mtable.h
../bld/utils/mrawarray.o: utils/mtreetable.h utils/mtable.h
../bld/utils/mrawlist.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/mrawlist.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/mrawlist.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/utils/mrawlist.o: core/mstring.h core/mrcstringfactory.h
../bld/utils/mrawlist.o: core/mstringfactory.h core/mrcstringtable.h
../bld/utils/mrawlist.o: core/mstring.h core/mstringbuffer.h
../bld/utils/mrawlist.o: core/mstringfactory.h io/minputsource.h
../bld/utils/mrawlist.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/utils/mrawlist.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/utils/mrawlist.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/utils/mrawlist.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/utils/mrawlist.o: nodes/mvar.h nodes/mvariterator.h
../bld/utils/mrawlist.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/utils/mrawlist.o: parser/mparser.h parser/mtokenizer.h parser/mtoken.h
../bld/utils/mrawlist.o: parser/mparsercontext.h parser/mtagparser.h
../bld/utils/mrawlist.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/mrawlist.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/mrawlist.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/mrawlist.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/mrawlist.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/utils/mrawlist.o: utils/mbintree.h utils/mcollection.h
../bld/utils/mrawlist.o: utils/mlinkedlist.h utils/mlist.h utils/mmemutils.h
../bld/utils/mrawlist.o: utils/mrawarray.h utils/mrawlist.h
../bld/utils/mrawlist.o: utils/msingletons.h utils/mtable.h
../bld/utils/mrawlist.o: utils/mtreetable.h utils/mtable.h
../bld/utils/msingletons.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/msingletons.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/msingletons.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/utils/msingletons.o: parser/mparsercontext.h parser/mtagparser.h
../bld/utils/msingletons.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/utils/msingletons.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/utils/msingletons.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/utils/msingletons.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/utils/msingletons.o: utils/marraylist.h utils/mlist.h
../bld/utils/msingletons.o: utils/mcollection.h utils/mbintree.h
../bld/utils/msingletons.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/msingletons.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/utils/msingletons.o: utils/mrawlist.h utils/msingletons.h
../bld/utils/msingletons.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/utils/mtable.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/mtable.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/mtable.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/utils/mtable.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/mtable.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mtable.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mtable.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mtable.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mtable.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mtable.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mtable.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/utils/mtable.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mtable.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mtable.o: utils/mtable.h
../bld/utils/mtreetable.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/utils/mtreetable.o: core/merror.h core/miterator.h core/mobject.h
../bld/utils/mtreetable.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/utils/mtreetable.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/mtreetable.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mtreetable.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mtreetable.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mtreetable.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mtreetable.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mtreetable.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mtreetable.o: utils/mcollection.h utils/mlinkedlist.h
../bld/utils/mtreetable.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/utils/mtreetable.o: utils/mrawlist.h utils/msingletons.h
../bld/utils/mtreetable.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/utils/mutils.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/utils/mutils.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/utils/mutils.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/utils/mutils.o: parser/mtoken.h parser/mparsercontext.h
../bld/utils/mutils.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/utils/mutils.o: parser/mtoken.h parser/mtokenizer.h
../bld/utils/mutils.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/utils/mutils.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/utils/mutils.o: resolver/mvarresolver.h utils/marraylist.h
../bld/utils/mutils.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/utils/mutils.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/utils/mutils.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/utils/mutils.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/utils/mutils.o: utils/mtable.h
../bld/core/mclasses.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/core/mclasses.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/core/mclasses.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/core/mclasses.o: parser/mtoken.h parser/mparsercontext.h
../bld/core/mclasses.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/mclasses.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/mclasses.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/mclasses.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/mclasses.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/mclasses.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/core/mclasses.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/core/mclasses.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/mclasses.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/mclasses.o: utils/mtable.h
../bld/core/merror.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/core/merror.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/core/merror.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/core/merror.o: parser/mtoken.h parser/mparsercontext.h
../bld/core/merror.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/merror.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/merror.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/merror.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/merror.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/merror.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/core/merror.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/core/merror.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/merror.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/merror.o: utils/mtable.h
../bld/core/mobject.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/core/mobject.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/core/mobject.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/core/mobject.o: parser/mtoken.h parser/mparsercontext.h
../bld/core/mobject.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/mobject.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/mobject.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/mobject.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/mobject.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/mobject.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/core/mobject.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/core/mobject.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/mobject.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/mobject.o: utils/mtable.h
../bld/core/mrcstring.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/core/mrcstring.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/core/mrcstring.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/core/mrcstring.o: core/mstring.h core/mrcstringfactory.h
../bld/core/mrcstring.o: core/mstringfactory.h core/mrcstringtable.h
../bld/core/mrcstring.o: core/mstring.h core/mstringbuffer.h
../bld/core/mrcstring.o: core/mstringfactory.h io/minputsource.h
../bld/core/mrcstring.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/core/mrcstring.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/core/mrcstring.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/core/mrcstring.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/core/mrcstring.o: nodes/mvar.h nodes/mvariterator.h
../bld/core/mrcstring.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/core/mrcstring.o: parser/mparser.h parser/mtokenizer.h parser/mtoken.h
../bld/core/mrcstring.o: parser/mparsercontext.h parser/mtagparser.h
../bld/core/mrcstring.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mrcstring.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mrcstring.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mrcstring.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mrcstring.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/core/mrcstring.o: utils/mbintree.h utils/mcollection.h
../bld/core/mrcstring.o: utils/mlinkedlist.h utils/mlist.h utils/mmemutils.h
../bld/core/mrcstring.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mrcstring.o: utils/msingletons.h utils/mtable.h
../bld/core/mrcstring.o: utils/mtreetable.h utils/mtable.h
../bld/core/mrcstringfactory.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mrcstringfactory.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/mrcstringfactory.o: utils/mutils.h core/mnumber.h core/mobject.h
../bld/core/mrcstringfactory.o: core/mrcstring.h core/mstring.h
../bld/core/mrcstringfactory.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/core/mrcstringfactory.o: core/mrcstringtable.h core/mstring.h
../bld/core/mrcstringfactory.o: core/mstringbuffer.h core/mstringfactory.h
../bld/core/mrcstringfactory.o: io/minputsource.h io/moutstream.h
../bld/core/mrcstringfactory.o: io/mstroutstream.h io/moutstream.h
../bld/core/mrcstringfactory.o: nodes/mfilter.h nodes/mvar.h
../bld/core/mrcstringfactory.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/core/mrcstringfactory.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/core/mrcstringfactory.o: nodes/mnodelist.h nodes/mtagnode.h
../bld/core/mrcstringfactory.o: nodes/mvar.h nodes/mvariterator.h
../bld/core/mrcstringfactory.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/core/mrcstringfactory.o: parser/mparser.h parser/mtokenizer.h
../bld/core/mrcstringfactory.o: parser/mtoken.h parser/mparsercontext.h
../bld/core/mrcstringfactory.o: parser/mtagparser.h
../bld/core/mrcstringfactory.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mrcstringfactory.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mrcstringfactory.o: renderer/mrenderer.h
../bld/core/mrcstringfactory.o: resolver/mtemplateloader.h
../bld/core/mrcstringfactory.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mrcstringfactory.o: utils/marraylist.h utils/mlist.h
../bld/core/mrcstringfactory.o: utils/mcollection.h utils/mbintree.h
../bld/core/mrcstringfactory.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/mrcstringfactory.o: utils/mlist.h utils/mmemutils.h
../bld/core/mrcstringfactory.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mrcstringfactory.o: utils/msingletons.h utils/mtable.h
../bld/core/mrcstringfactory.o: utils/mtreetable.h utils/mtable.h
../bld/core/mrcstringtable.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mrcstringtable.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/mrcstringtable.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/core/mrcstringtable.o: parser/mparsercontext.h parser/mtagparser.h
../bld/core/mrcstringtable.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mrcstringtable.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mrcstringtable.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mrcstringtable.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mrcstringtable.o: utils/marraylist.h utils/mlist.h
../bld/core/mrcstringtable.o: utils/mcollection.h utils/mbintree.h
../bld/core/mrcstringtable.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/mrcstringtable.o: utils/mlist.h utils/mmemutils.h
../bld/core/mrcstringtable.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mrcstringtable.o: utils/msingletons.h utils/mtable.h
../bld/core/mrcstringtable.o: utils/mtreetable.h utils/mtable.h
../bld/core/mstringbuffer.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mstringbuffer.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/mstringbuffer.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/core/mstringbuffer.o: parser/mparsercontext.h parser/mtagparser.h
../bld/core/mstringbuffer.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mstringbuffer.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mstringbuffer.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mstringbuffer.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mstringbuffer.o: utils/marraylist.h utils/mlist.h
../bld/core/mstringbuffer.o: utils/mcollection.h utils/mbintree.h
../bld/core/mstringbuffer.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/mstringbuffer.o: utils/mlist.h utils/mmemutils.h
../bld/core/mstringbuffer.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mstringbuffer.o: utils/msingletons.h utils/mtable.h
../bld/core/mstringbuffer.o: utils/mtreetable.h utils/mtable.h
../bld/core/mstring.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/core/mstring.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/core/mstring.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/core/mstring.o: parser/mtoken.h parser/mparsercontext.h
../bld/core/mstring.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/core/mstring.o: parser/mtoken.h parser/mtokenizer.h
../bld/core/mstring.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/core/mstring.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/core/mstring.o: resolver/mvarresolver.h utils/marraylist.h
../bld/core/mstring.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/core/mstring.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/core/mstring.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/core/mstring.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/core/mstring.o: utils/mtable.h
../bld/core/mstringfactory.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/core/mstringfactory.o: core/merror.h core/miterator.h core/mobject.h
../bld/core/mstringfactory.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/core/mstringfactory.o: parser/mparsercontext.h parser/mtagparser.h
../bld/core/mstringfactory.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/core/mstringfactory.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/core/mstringfactory.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/core/mstringfactory.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/core/mstringfactory.o: utils/marraylist.h utils/mlist.h
../bld/core/mstringfactory.o: utils/mcollection.h utils/mbintree.h
../bld/core/mstringfactory.o: utils/mcollection.h utils/mlinkedlist.h
../bld/core/mstringfactory.o: utils/mlist.h utils/mmemutils.h
../bld/core/mstringfactory.o: utils/mrawarray.h utils/mrawlist.h
../bld/core/mstringfactory.o: utils/msingletons.h utils/mtable.h
../bld/core/mstringfactory.o: utils/mtreetable.h utils/mtable.h
../bld/parser/mparser.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/parser/mparser.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/parser/mparser.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/parser/mparser.o: core/mstring.h core/mrcstringfactory.h
../bld/parser/mparser.o: core/mstringfactory.h core/mrcstringtable.h
../bld/parser/mparser.o: core/mstring.h core/mstringbuffer.h
../bld/parser/mparser.o: core/mstringfactory.h io/minputsource.h
../bld/parser/mparser.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/parser/mparser.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/parser/mparser.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/parser/mparser.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/parser/mparser.o: nodes/mvar.h nodes/mvariterator.h
../bld/parser/mparser.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/parser/mparser.o: parser/mparser.h parser/mtokenizer.h parser/mtoken.h
../bld/parser/mparser.o: parser/mparsercontext.h parser/mtagparser.h
../bld/parser/mparser.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/parser/mparser.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/parser/mparser.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/parser/mparser.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/parser/mparser.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/parser/mparser.o: utils/mbintree.h utils/mcollection.h
../bld/parser/mparser.o: utils/mlinkedlist.h utils/mlist.h utils/mmemutils.h
../bld/parser/mparser.o: utils/mrawarray.h utils/mrawlist.h
../bld/parser/mparser.o: utils/msingletons.h utils/mtable.h
../bld/parser/mparser.o: utils/mtreetable.h utils/mtable.h
../bld/parser/mtagparserlibrary.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/parser/mtagparserlibrary.o: core/merror.h core/miterator.h
../bld/parser/mtagparserlibrary.o: core/mobject.h utils/mutils.h
../bld/parser/mtagparserlibrary.o: core/mnumber.h core/mobject.h
../bld/parser/mtagparserlibrary.o: core/mrcstring.h core/mstring.h
../bld/parser/mtagparserlibrary.o: core/mrcstringfactory.h
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
../bld/parser/mtagparserlibrary.o: parser/mparsercontext.h
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
../bld/parser/mtagparserlibrary.o: utils/mmemutils.h utils/mrawarray.h
../bld/parser/mtagparserlibrary.o: utils/mrawlist.h utils/msingletons.h
../bld/parser/mtagparserlibrary.o: utils/mtable.h utils/mtreetable.h
../bld/parser/mtagparserlibrary.o: utils/mtable.h
../bld/parser/mtoken.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/parser/mtoken.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/parser/mtoken.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/parser/mtoken.o: parser/mtoken.h parser/mparsercontext.h
../bld/parser/mtoken.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/parser/mtoken.o: parser/mtoken.h parser/mtokenizer.h
../bld/parser/mtoken.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/parser/mtoken.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/parser/mtoken.o: resolver/mvarresolver.h utils/marraylist.h
../bld/parser/mtoken.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/parser/mtoken.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/parser/mtoken.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/parser/mtoken.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/parser/mtoken.o: utils/mtable.h
../bld/parser/mtokenizer.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/parser/mtokenizer.o: core/merror.h core/miterator.h core/mobject.h
../bld/parser/mtokenizer.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/parser/mtokenizer.o: parser/mparsercontext.h parser/mtagparser.h
../bld/parser/mtokenizer.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/parser/mtokenizer.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/parser/mtokenizer.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/parser/mtokenizer.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/parser/mtokenizer.o: utils/marraylist.h utils/mlist.h
../bld/parser/mtokenizer.o: utils/mcollection.h utils/mbintree.h
../bld/parser/mtokenizer.o: utils/mcollection.h utils/mlinkedlist.h
../bld/parser/mtokenizer.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/parser/mtokenizer.o: utils/mrawlist.h utils/msingletons.h
../bld/parser/mtokenizer.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/parser/mtokenlists.o: parser/mtokenlists.h mfwddefs.h parser/mtoken.h
../bld/nodes/mfilter.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/nodes/mfilter.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/nodes/mfilter.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/nodes/mfilter.o: parser/mtoken.h parser/mparsercontext.h
../bld/nodes/mfilter.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mfilter.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mfilter.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mfilter.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mfilter.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mfilter.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/nodes/mfilter.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/nodes/mfilter.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mfilter.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/nodes/mfilter.o: utils/mtable.h
../bld/nodes/mfilterlibrary.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mfilterlibrary.o: core/merror.h core/miterator.h core/mobject.h
../bld/nodes/mfilterlibrary.o: utils/mutils.h core/mnumber.h core/mobject.h
../bld/nodes/mfilterlibrary.o: core/mrcstring.h core/mstring.h
../bld/nodes/mfilterlibrary.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/nodes/mfilterlibrary.o: core/mrcstringtable.h core/mstring.h
../bld/nodes/mfilterlibrary.o: core/mstringbuffer.h core/mstringfactory.h
../bld/nodes/mfilterlibrary.o: io/minputsource.h io/moutstream.h
../bld/nodes/mfilterlibrary.o: io/mstroutstream.h io/moutstream.h
../bld/nodes/mfilterlibrary.o: nodes/mfilter.h nodes/mvar.h
../bld/nodes/mfilterlibrary.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/nodes/mfilterlibrary.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/nodes/mfilterlibrary.o: nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mfilterlibrary.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mfilterlibrary.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mfilterlibrary.o: parser/mparser.h parser/mtokenizer.h
../bld/nodes/mfilterlibrary.o: parser/mtoken.h parser/mparsercontext.h
../bld/nodes/mfilterlibrary.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mfilterlibrary.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mfilterlibrary.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mfilterlibrary.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mfilterlibrary.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mfilterlibrary.o: utils/mlist.h utils/mcollection.h
../bld/nodes/mfilterlibrary.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mfilterlibrary.o: utils/mlinkedlist.h utils/mlist.h
../bld/nodes/mfilterlibrary.o: utils/mmemutils.h utils/mrawarray.h
../bld/nodes/mfilterlibrary.o: utils/mrawlist.h utils/msingletons.h
../bld/nodes/mfilterlibrary.o: utils/mtable.h utils/mtreetable.h
../bld/nodes/mfilterlibrary.o: utils/mtable.h
../bld/nodes/mfilternode.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mfilternode.o: core/merror.h core/miterator.h core/mobject.h
../bld/nodes/mfilternode.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/nodes/mfilternode.o: parser/mparsercontext.h parser/mtagparser.h
../bld/nodes/mfilternode.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mfilternode.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mfilternode.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mfilternode.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mfilternode.o: utils/marraylist.h utils/mlist.h
../bld/nodes/mfilternode.o: utils/mcollection.h utils/mbintree.h
../bld/nodes/mfilternode.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mfilternode.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/nodes/mfilternode.o: utils/mrawlist.h utils/msingletons.h
../bld/nodes/mfilternode.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/nodes/mfreetext.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/nodes/mfreetext.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/nodes/mfreetext.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/nodes/mfreetext.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mfreetext.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mfreetext.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mfreetext.o: core/mstringfactory.h io/minputsource.h
../bld/nodes/mfreetext.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/nodes/mfreetext.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/nodes/mfreetext.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/nodes/mfreetext.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mfreetext.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mfreetext.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mfreetext.o: parser/mparser.h parser/mtokenizer.h
../bld/nodes/mfreetext.o: parser/mtoken.h parser/mparsercontext.h
../bld/nodes/mfreetext.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mfreetext.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mfreetext.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mfreetext.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mfreetext.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mfreetext.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/nodes/mfreetext.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mfreetext.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/nodes/mfreetext.o: utils/mrawlist.h utils/msingletons.h utils/mtable.h
../bld/nodes/mfreetext.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mnode.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/nodes/mnode.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/nodes/mnode.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/nodes/mnode.o: parser/mtoken.h parser/mparsercontext.h
../bld/nodes/mnode.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mnode.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mnode.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mnode.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mnode.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mnode.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/nodes/mnode.o: utils/mcollection.h utils/mlinkedlist.h utils/mlist.h
../bld/nodes/mnode.o: utils/mmemutils.h utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mnode.o: utils/msingletons.h utils/mtable.h utils/mtreetable.h
../bld/nodes/mnode.o: utils/mtable.h
../bld/nodes/mnodelist.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/nodes/mnodelist.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/nodes/mnodelist.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/nodes/mnodelist.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mnodelist.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mnodelist.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mnodelist.o: core/mstringfactory.h io/minputsource.h
../bld/nodes/mnodelist.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/nodes/mnodelist.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/nodes/mnodelist.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/nodes/mnodelist.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mnodelist.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mnodelist.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mnodelist.o: parser/mparser.h parser/mtokenizer.h
../bld/nodes/mnodelist.o: parser/mtoken.h parser/mparsercontext.h
../bld/nodes/mnodelist.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mnodelist.o: parser/mtoken.h parser/mtokenizer.h
../bld/nodes/mnodelist.o: parser/mtokenlists.h renderer/mrenderer.h
../bld/nodes/mnodelist.o: resolver/mtemplateloader.h resolver/mtmplctx.h
../bld/nodes/mnodelist.o: resolver/mvarresolver.h utils/marraylist.h
../bld/nodes/mnodelist.o: utils/mlist.h utils/mcollection.h utils/mbintree.h
../bld/nodes/mnodelist.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mnodelist.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/nodes/mnodelist.o: utils/mrawlist.h utils/msingletons.h utils/mtable.h
../bld/nodes/mnodelist.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mtagnode.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/nodes/mtagnode.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/nodes/mtagnode.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/nodes/mtagnode.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mtagnode.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mtagnode.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mtagnode.o: core/mstringfactory.h io/minputsource.h
../bld/nodes/mtagnode.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/nodes/mtagnode.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/nodes/mtagnode.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/nodes/mtagnode.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mtagnode.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mtagnode.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mtagnode.o: parser/mparser.h parser/mtokenizer.h parser/mtoken.h
../bld/nodes/mtagnode.o: parser/mparsercontext.h parser/mtagparser.h
../bld/nodes/mtagnode.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mtagnode.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mtagnode.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mtagnode.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mtagnode.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/nodes/mtagnode.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mtagnode.o: utils/mlinkedlist.h utils/mlist.h utils/mmemutils.h
../bld/nodes/mtagnode.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mtagnode.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mtagnode.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mvar.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/nodes/mvar.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/nodes/mvar.o: core/mnumber.h core/mobject.h core/mrcstring.h
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
../bld/nodes/mvar.o: parser/mtoken.h parser/mparsercontext.h
../bld/nodes/mvar.o: parser/mtagparser.h parser/mtagparserlibrary.h
../bld/nodes/mvar.o: parser/mtoken.h parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mvar.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mvar.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mvar.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/nodes/mvar.o: utils/mbintree.h utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mvar.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/nodes/mvar.o: utils/mrawlist.h utils/msingletons.h utils/mtable.h
../bld/nodes/mvar.o: utils/mtreetable.h utils/mtable.h
../bld/nodes/mvarlibrary.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/nodes/mvarlibrary.o: core/merror.h core/miterator.h core/mobject.h
../bld/nodes/mvarlibrary.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/nodes/mvarlibrary.o: parser/mparsercontext.h parser/mtagparser.h
../bld/nodes/mvarlibrary.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mvarlibrary.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mvarlibrary.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mvarlibrary.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mvarlibrary.o: utils/marraylist.h utils/mlist.h
../bld/nodes/mvarlibrary.o: utils/mcollection.h utils/mbintree.h
../bld/nodes/mvarlibrary.o: utils/mcollection.h utils/mlinkedlist.h
../bld/nodes/mvarlibrary.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/nodes/mvarlibrary.o: utils/mrawlist.h utils/msingletons.h
../bld/nodes/mvarlibrary.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/nodes/mvarnode.o: mangopub.h mfwddefs.h core/mclasses.h core/merror.h
../bld/nodes/mvarnode.o: core/miterator.h core/mobject.h utils/mutils.h
../bld/nodes/mvarnode.o: core/mnumber.h core/mobject.h core/mrcstring.h
../bld/nodes/mvarnode.o: core/mstring.h core/mrcstringfactory.h
../bld/nodes/mvarnode.o: core/mstringfactory.h core/mrcstringtable.h
../bld/nodes/mvarnode.o: core/mstring.h core/mstringbuffer.h
../bld/nodes/mvarnode.o: core/mstringfactory.h io/minputsource.h
../bld/nodes/mvarnode.o: io/moutstream.h io/mstroutstream.h io/moutstream.h
../bld/nodes/mvarnode.o: nodes/mfilter.h nodes/mvar.h nodes/mfilterlibrary.h
../bld/nodes/mvarnode.o: nodes/mfilternode.h nodes/mfreetext.h nodes/mnode.h
../bld/nodes/mvarnode.o: nodes/mnode.h nodes/mnodelist.h nodes/mtagnode.h
../bld/nodes/mvarnode.o: nodes/mvar.h nodes/mvariterator.h
../bld/nodes/mvarnode.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/nodes/mvarnode.o: parser/mparser.h parser/mtokenizer.h parser/mtoken.h
../bld/nodes/mvarnode.o: parser/mparsercontext.h parser/mtagparser.h
../bld/nodes/mvarnode.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/nodes/mvarnode.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/nodes/mvarnode.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/nodes/mvarnode.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/nodes/mvarnode.o: utils/marraylist.h utils/mlist.h utils/mcollection.h
../bld/nodes/mvarnode.o: utils/mbintree.h utils/mcollection.h
../bld/nodes/mvarnode.o: utils/mlinkedlist.h utils/mlist.h utils/mmemutils.h
../bld/nodes/mvarnode.o: utils/mrawarray.h utils/mrawlist.h
../bld/nodes/mvarnode.o: utils/msingletons.h utils/mtable.h
../bld/nodes/mvarnode.o: utils/mtreetable.h utils/mtable.h
../bld/renderer/mrenderer.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/renderer/mrenderer.o: core/merror.h core/miterator.h core/mobject.h
../bld/renderer/mrenderer.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/renderer/mrenderer.o: parser/mparsercontext.h parser/mtagparser.h
../bld/renderer/mrenderer.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/renderer/mrenderer.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/renderer/mrenderer.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/renderer/mrenderer.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/renderer/mrenderer.o: utils/marraylist.h utils/mlist.h
../bld/renderer/mrenderer.o: utils/mcollection.h utils/mbintree.h
../bld/renderer/mrenderer.o: utils/mcollection.h utils/mlinkedlist.h
../bld/renderer/mrenderer.o: utils/mlist.h utils/mmemutils.h
../bld/renderer/mrenderer.o: utils/mrawarray.h utils/mrawlist.h
../bld/renderer/mrenderer.o: utils/msingletons.h utils/mtable.h
../bld/renderer/mrenderer.o: utils/mtreetable.h utils/mtable.h
../bld/resolver/mtmplctx.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/resolver/mtmplctx.o: core/merror.h core/miterator.h core/mobject.h
../bld/resolver/mtmplctx.o: utils/mutils.h core/mnumber.h core/mobject.h
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
../bld/resolver/mtmplctx.o: parser/mparsercontext.h parser/mtagparser.h
../bld/resolver/mtmplctx.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/resolver/mtmplctx.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/resolver/mtmplctx.o: renderer/mrenderer.h resolver/mtemplateloader.h
../bld/resolver/mtmplctx.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/resolver/mtmplctx.o: utils/marraylist.h utils/mlist.h
../bld/resolver/mtmplctx.o: utils/mcollection.h utils/mbintree.h
../bld/resolver/mtmplctx.o: utils/mcollection.h utils/mlinkedlist.h
../bld/resolver/mtmplctx.o: utils/mlist.h utils/mmemutils.h utils/mrawarray.h
../bld/resolver/mtmplctx.o: utils/mrawlist.h utils/msingletons.h
../bld/resolver/mtmplctx.o: utils/mtable.h utils/mtreetable.h utils/mtable.h
../bld/resolver/mvarresolver.o: mangopub.h mfwddefs.h core/mclasses.h
../bld/resolver/mvarresolver.o: core/merror.h core/miterator.h core/mobject.h
../bld/resolver/mvarresolver.o: utils/mutils.h core/mnumber.h core/mobject.h
../bld/resolver/mvarresolver.o: core/mrcstring.h core/mstring.h
../bld/resolver/mvarresolver.o: core/mrcstringfactory.h core/mstringfactory.h
../bld/resolver/mvarresolver.o: core/mrcstringtable.h core/mstring.h
../bld/resolver/mvarresolver.o: core/mstringbuffer.h core/mstringfactory.h
../bld/resolver/mvarresolver.o: io/minputsource.h io/moutstream.h
../bld/resolver/mvarresolver.o: io/mstroutstream.h io/moutstream.h
../bld/resolver/mvarresolver.o: nodes/mfilter.h nodes/mvar.h
../bld/resolver/mvarresolver.o: nodes/mfilterlibrary.h nodes/mfilternode.h
../bld/resolver/mvarresolver.o: nodes/mfreetext.h nodes/mnode.h nodes/mnode.h
../bld/resolver/mvarresolver.o: nodes/mnodelist.h nodes/mtagnode.h
../bld/resolver/mvarresolver.o: nodes/mvar.h nodes/mvariterator.h
../bld/resolver/mvarresolver.o: nodes/mvarlibrary.h nodes/mvarnode.h
../bld/resolver/mvarresolver.o: parser/mparser.h parser/mtokenizer.h
../bld/resolver/mvarresolver.o: parser/mtoken.h parser/mparsercontext.h
../bld/resolver/mvarresolver.o: parser/mtagparser.h
../bld/resolver/mvarresolver.o: parser/mtagparserlibrary.h parser/mtoken.h
../bld/resolver/mvarresolver.o: parser/mtokenizer.h parser/mtokenlists.h
../bld/resolver/mvarresolver.o: renderer/mrenderer.h
../bld/resolver/mvarresolver.o: resolver/mtemplateloader.h
../bld/resolver/mvarresolver.o: resolver/mtmplctx.h resolver/mvarresolver.h
../bld/resolver/mvarresolver.o: utils/marraylist.h utils/mlist.h
../bld/resolver/mvarresolver.o: utils/mcollection.h utils/mbintree.h
../bld/resolver/mvarresolver.o: utils/mcollection.h utils/mlinkedlist.h
../bld/resolver/mvarresolver.o: utils/mlist.h utils/mmemutils.h
../bld/resolver/mvarresolver.o: utils/mrawarray.h utils/mrawlist.h
../bld/resolver/mvarresolver.o: utils/msingletons.h utils/mtable.h
../bld/resolver/mvarresolver.o: utils/mtreetable.h utils/mtable.h

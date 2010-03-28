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

include Makefile.common

# 
# Main Makefile
#
.PHONY: all libs test install
all: libs test

libs:
	@cd src ; make static shared

test: libs
	@cd test ; make

install: 
	@cd src ; make install
	@cd test ; make install

.PHONY: clean cleanall distclean package
clean:
	@cd src ; make clean
	@cd test ; make clean
	@rm -Rf $(OUTPUT_DIR)

cleanall: clean
	@cd src ; make cleanall
	@cd test ; make cleanall
	@rm -Rf $(OUTPUT_DIR)

distclean: cleanall
	@cd src ; make distclean
	@cd test ; make distclean
	@rm -Rf Makefile Makefile.common autom4te.cache config.* configure
	@rm -Rf $(OUTPUT_DIR)

dep:
	cd test ; make dep
	cd src ; make dep

PACKAGE_NAME = $(PRODUCT_NAME)-$(MAJOR_VERSION).$(MINOR_VERSION).$(BUILD_VERSION)
# 
# Creates the archive.
#
package:
	@rm -f /tmp/$(PACKAGE_NAME).zip /tmp/$(PACKAGE_NAME).tar.bz2 /tmp/$(PACKAGE_NAME).tgz
	@if [ -d /tmp/$(PACKAGE_NAME) ]; then echo "Error: Directory /tmp/$(PACKAGE_NAME) already exists." ; exit 1 ; fi
	@autoconf
	@cp -r `pwd` /tmp/$(PACKAGE_NAME)
	@rm -Rf `find /tmp/$(PACKAGE_NAME) | grep .svn`
	@rm -Rf /tmp/$(PACKAGE_NAME)/bld 
	@rm -Rf /tmp/$(PACKAGE_NAME)/Makefile /tmp/$(PACKAGE_NAME)/Makefile.common
	@rm -Rf /tmp/$(PACKAGE_NAME)/src/Makefile /tmp/$(PACKAGE_NAME)/test/Makefile
	@rm -Rf /tmp/$(PACKAGE_NAME)/autom4te.cache /tmp/$(PACKAGE_NAME)/config.*
	@tar -C /tmp -zcvf /tmp/$(PACKAGE_NAME).tgz $(PACKAGE_NAME)
	@tar -C /tmp -jcvf /tmp/$(PACKAGE_NAME).tar.bz2 $(PACKAGE_NAME)
	@cd /tmp ; zip -r /tmp/$(PACKAGE_NAME).zip $(PACKAGE_NAME)
	@rm -Rf /tmp/$(PACKAGE_NAME)

help:
	@echo   "Usage: make <options> <targets>"
	@echo   "   Options:"
	@echo   "       BUILD_MODE=[debug | release]        -   Default: release"
	@echo   "       OUTPUT_DIR=<output_dir>             -   Directory to place all outputs. Default: bld"
	@echo   "   Targets:"
	@echo   "       all:        Builds test executable and libraries (default)"
	@echo   "       test:       Builds test executable"
	@echo   "       libs:       Builds static and shared libraries"
	@echo   "       clean:      Cleans all object files"
	@echo   "       cleanall:   Cleans all object files and executables"
	@echo   "       install:    Installs the test executable and libraries"
	@echo   "       help:       Prints help information about targets and options"

include rules.$(shell uname)

PATH := $(PATH):.

export PATH

#
# To use this makefile:
#
#   "make"                    with no arguments builds the tools
#   "make tests"              runs all the tests (1 minute at least)
#   "sudo root make install"  installs the tools
#   "make install_tests"      tests the installed tools
#

INSTALLABLES= covtool.exe \
	      covmerge.exe \
	      covannotate.exe \
	      covtoolhelper.o \
	      covtoolhelper_debug.o \
	      covtoolhelper.c \
	      README \
	      cov++ \
	      cov++.cfg \
	      COPYRIGHT \
	      covtool_version \
	      gen_html
	

install:
	@mkdir -p $(INSTALL_DIR)
	if [ -w $(INSTALL_DIR)/. ] ; \
	 then \
	     for f in $(INSTALLABLES) ;\
	     do \
	       echo "installing $$f" ;\
	       cp $$f $(INSTALL_DIR) ;\
	     done ;\
	     cp -r man $(INSTALL_DIR) ;\
	 else \
	     echo "Error:  can't create $(INSTALL_DIR)" ; \
	     exit 1; \
	 fi
	@echo ""
	@echo ""
	@echo ""
	@echo "Installation complete"
	@echo "Add $(INSTALL_DIR) to your path"
	@echo ""
	@echo "Then run make install_tests (but not as ROOT!)"
	@echo ""
	@echo ""
	@echo "Also, add $(INSTALL_DIR) to your MANPATH."
	@echo ""
	
	
install_tests:
	cd install_test ; $(MAKE) all ; $(MAKE) tests
	@if grep '^[-+]' install_test/covmerge.ann >/dev/null ; \
	 then \
	   echo "Installation test succeded" ;\
	 else \
	   echo "Installation test failed" ;\
	   exit 1 ;\
	 fi
	 @echo ""
	 @echo ""
	 @echo ""
	 @echo "You are all set.  See README for an overview of how to use the tools"
	 @echo ""
	 @echo ""
	 @echo ""
	
	
	

all:: covtool.exe
all:: covtoolhelper.o
all:: covtoolhelper_debug.o

covtoolhelper_debug.o: covtoolhelper.c
	rm -f covtoolhelper.o
	$(MAKE) DEBUGGING=1 covtoolhelper.o
	mv covtoolhelper.o covtoolhelper_debug.o
	$(MAKE) covtoolhelper.o

covtool.exe: covtool.o covlib.a
	$(LN) -o $@ $+
	
covlib.a:  covstream.o bomb.o read_database.o
	rm -f $@
	ar cvq $@ $+


backup::
	-zip -ru ../covtool.zip *
	
clean::
	cd example; $(MAKE) clean
	cd install_test;  $(MAKE) clean
	cd tests; $(MAKE) clean

depend::
	makedepend -I. -I/usr/include/g++ *.c



all:: covmerge.exe
covmerge.exe: covmerge.o read_database.o
	$(LN) -g -o $@ covmerge.o read_database.o



all:: covannotate.exe covlib.a
covannotate.exe: covannotate.o covlib.a
	$(LN) -o $@ covannotate.o covlib.a


tests clean ::
	cd tests; $(MAKE) $@


tests::
	cd tests; $(MAKE) icov_test


tests clean ::
	cd cov++_test; $(MAKE) $@
	
clean::
	find * -name 'core' -print | xargs rm -f
	rm -f log log.make 

all::    # must be next to last
	@echo ""
	@echo ""
	@echo ""
	@echo "Now run $(MAKE) tests"
	@echo ""
	@echo ""
	@echo ""

tests::  # must be last
	@echo ""
	@echo ""
	@echo ""
	@echo "Now run '$(MAKE) install' as root"
	@echo ""
	@echo ""
	@echo ""


# DO NOT DELETE



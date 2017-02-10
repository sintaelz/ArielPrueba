#
# An example of how to build an application with and without
# instrumentation.  This is a trivial example doesn't deal
# with the complexities of passing options to the various
# phases of the compiler.  This example's goal is clarity and
# completeness of a trivial case.
#

#
# by default, no instrumentation is used, but if you run make
# like this, you'll get a build with instrumentation
#
#   make INSTRUMENTATION=1
#
# Note that you must do a clean build do get instrumentation
# turned on everywhere.
#
# Note that the symbols above are defined with := not just =
# this is necessary if you are going to redefine the symbols
# using += as we do below
#
###################################################################
# DEFINITIONS AND COMPILATION RULES
###################################################################

INSTRUMENTATION=0
COVTOOL_DIR=..

CCDEFS:=
CCINCS:=
CCLIBS:=
CCOPTS:=

ifeq ($(INSTRUMENTATION),0)
CC    := g++
LN    := g++
else
CC    := $(COVTOOL_DIR)/cov++
LN    := $(COVTOOL_DIR)/cov++
endif

.SUFFIXES: .c .o
.c.o:
	$(CC) -g -c $(CCDEFS) $(CCINCS) $(CCOPTS) $<


#########################################################################
# PROGRAM COMPONENT DEFINITIONS
#########################################################################

all::

ifeq ($(INSTRUMENTATION),0)
all::
	@echo Building WITHOUT instrumentation
endif

all::  program


program: program.o
	$(CC) -g -o program program.o $(CCLIBS)

clean:
	rm -fr program program.o *.covexp *.db *.ann covexp.* coverage_html


#########################################################################
# TEST COMPONENT DEFINITIONS
#########################################################################

ifeq ($(INSTRUMENTATION),0)

tests::
	@echo "You can only run the tests if you build like this"
	@echo "  make clean"
	@echo "  make INSTRUMENTATION=1"
	@echo "  make INSTRUMENTATION=1 tests"

else
tests:: program
	#
	rm -fr *.covexp
	@echo "RUN 1"
	program
	@if [ ! -f *.covexp ] ; then echo NOT COMPILED FOR INSTRUMENTATION ;  fi
	$(COVTOOL_DIR)/covmerge.exe *.covexp >merge.db
	$(COVTOOL_DIR)/covannotate.exe program.c *.db >1.ann
	mv *.covexp covexp.1
	@echo "RUN 2"
	program 1
	$(COVTOOL_DIR)/covmerge.exe *.covexp >merge.db
	$(COVTOOL_DIR)/covannotate.exe program.c *.db >2.ann
	mv *.covexp covexp.2
	@echo "RUN 3"
	program 1 2
	$(COVTOOL_DIR)/covmerge.exe *.covexp >merge.db
	$(COVTOOL_DIR)/covannotate.exe program.c *.db >3.ann
	mv *.covexp covexp.3
	@echo ""
	@echo ""
	@echo ""
	@echo "MERGING TEST RESULTS"
	$(COVTOOL_DIR)/covmerge.exe covexp.* >merge.db
	$(COVTOOL_DIR)/gen_html merge.db
	@echo ""
	@echo "See 1,2, and 3.ann to see what got covered in each run"
	@echo ""
	@echo "Next, point your browser at `pwd`/coverage_html/index.html"
	@echo ""
	@echo "Example tests passed -- see commentary above"
	@echo ""
	@echo ""
endif
	



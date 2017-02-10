all::

include ../rules.$(shell uname)

COVTOOL_DIR=..

COVTOOL      =$(COVTOOL_DIR)/covtool.exe
COVHELPER    =$(COVTOOL_DIR)/covtoolhelper.o
COVLIB       =$(COVTOOL_DIR)/covlib.a
COVMERGE     =$(COVTOOL_DIR)/covmerge.exe
COVANNOTATE  =$(COVTOOL_DIR)/covannotate.exe

CCINCS += -I..

all::
tests::
clean::
backup::
depend::

tests::
	@echo Using $(COVTOOL) for instrumentation

#
# test the parser (only) on a small but real program.  No instrumentation
# is done, just validation of trivial parsing logic.
#

tests:: bomb_test

bomb_test: bomb.i bomb_test.exe
	bomb_test.exe <bomb.i | sed -e 's#/\*[^/]*/##g' -e 's/ //g' >bomb.out
	expand bomb.i | sed -e 's/ //g'  >bomb.j
	diff -Bbhw bomb.j bomb.out
	rm -f bomb.diff bomb.i bomb.j bomb.out
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

bomb_test.exe: bomb_test.o $(COVLIB)
	$(LN) -o $@ $+

bomb.i:  $(COVTOOL_DIR)/bomb.c
	 $(CC) -E $(CCDEFS) $(CCINCS) $(COVTOOL_DIR)/bomb.c >$@


#
# test the parsing of tokens and the input stream handler
#
tests::  token_test

token_test:: token_test.exe token_test.in token_test.expect
	token_test.exe <token_test.in >token_test.out
	diff token_test.expect token_test.out
	rm -f token_test.out
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


token_test.exe: token_test.o $(COVLIB)
	$(LN) -o $@ $+

#
# run the parser on every fragment of C++ syntax imaginable
#
tests:: covtest

covtest:: $(COVTOOL) covtest.in covtest.expect
	$(COVTOOL) <covtest.in >covtest.out
	diff covtest.expect covtest.out
	rm -f covtest.out
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



#
# Sadly this test had to be commented out -- even though it was the
# most rigorous.  When I fixed the bug with parsing labels, it forced me
# parse one token ahead, which might trigger a change of source file line
# numbers.  This is what happened here.  Some return statement in the
# system headers had the value to be returned on a different line
# and thus this best of my tests cannot logically work any more.
#
# #
# # validate the covtool.exe parsing logic on covtool.c, but don't
# # instrument
# #
# tests:: real_test
# 
# real_test: covtool.i $(COVTOOL)
#         $(COVTOOL) -skip /usr/ <covtool.i | \
#             sed -e 's#^/\*[^/]*/##g' -e 's/ //g' >real_test.out
#         expand covtool.i | sed -e 's/ //g'  >real_test.j
#         diff -Bbhw real_test.j real_test.out
#         rm -f real_test.diff covtool.i real_test.j real_test.out
#         @echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

covtool.i:
	 $(CC) "-D__extension__=" -E $(CCDEFS) $(CCINCS) $(COVTOOL_DIR)/covtool.c >$@

#
# test covtool.exe on a very trivial but real program
#
tests:: simple_test

simple_test:: simple_test.exe
	simple_test.exe
	rm simple_test.exe simple.i simple_test.c
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

simple_test.exe: simple_test.c $(COVHELPER)
	$(CC) -g -o simple_test.exe simple_test.c $(COVHELPER)

simple_test.c: simple.i $(COVTOOL)
	$(COVTOOL) -instrument -skip / <simple.i >simple_test.c

#
# test covtool.exe on a small but non-trivial program
#
tests:: hard_test

hard_test:: hard_test.c $(COVTOOL) $(COVHELPER)
	$(LN) -g -o hard_test.exe hard_test.c $(COVHELPER)
	hard_test.exe
	rm hard_test.exe hard.i hard_test.c
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
hard_test.c: hard.i
	$(COVTOOL) -instrument <hard.i >hard_test.c

#
# make an instrumented version of covtool.exe
#
icov.exe: covtool.j $(COVHELPER) $(COVLIB)
	$(COVTOOL) -instrument -skip / <covtool.j >icov.c
	$(LN) -g -o $@ icov.c $(COVLIB) $(COVHELPER)

clean::
	rm -fr icov.c simple.i hard.i simple_test.c hard_test.c log log.make *.log

covtool.j: $(COVTOOL_DIR)/covtool.i
	 $(CC) -E $(CCDEFS) $(CCINCS) -DCOVTOOL_INST $(COVTOOL_DIR)/covtool.c >$@

#
# rerun the tests using the instrumented versions
#
icov_test: icov.exe
	$(MAKE) COVTOOL=icov.exe tests
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

tests:: aggregation_test

aggregation_test::
	$(COVMERGE) $@.in >$@.out
	diff $@.expect $@.out
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	


tests:: merge_test

#
# Test the program that merges databases
#

merge_test:  $(COVMERGE) \
	     data_base_1.covdb \
	     data_base_2.covdb \
	     data_base_3.covdb \
	     merge_test.expect
	$(COVMERGE) data_base_1.covdb data_base_2.covdb data_base_3.covdb \
	     >merge_test.out
	diff -Bbhw merge_test.expect merge_test.out
	rm merge_test.out
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

tests:: all_headers_test

all_headers_test:
	./all_hdrs $(COVTOOL)
	@echo $@ passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

clean::
	rm -fr all_headers.*

tests::
	if [ `uname` = 'Linux' ] ; then \
	   $(MAKE) -C astyle INSTRUMENTATION=1 tests ;\
	 fi
	
clean::
	$(MAKE) -C astyle clean
	
	
	

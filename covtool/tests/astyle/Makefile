# "Artistic Style" Makefile

all:: astyle
tests:: astyle
clean::

INSTRUMENTATION=0
COVTOOL_DIR=../..

ifeq ($(INSTRUMENTATION),0)
COMPILER=g++
else
COMPILER=$(COVTOOL_DIR)/cov++ -skip /usr -EXT .cpp .c++
endif


CPPFLAGS = -Wno-sign-compare -O2
OBJS = ASResource.o ASBeautifier.o ASFormatter.o astyle_main.o

astyle:: $(OBJS)
	$(COMPILER) $(CPPFLAGS) -o astyle  $(OBJS)

.cpp.o:
	$(COMPILER) $(CPPFLAGS) -c $<
.SUFFIXES: .cpp .c .o

clean::
	rm -fr *.o *.out astyle *.covexp merged.db coverage_html

tests::
	for f in *.cpp *.h ; do astyle <$$f ; done >test.out
	diff -uBbhw test.expect test.out
	@echo "astyle function test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

ifeq ($(INSTRUMENTATION),1)
tests::  astyle
	$(COVTOOL_DIR)/covmerge.exe *.covexp >merged.db
	for f in *.cpp *.h ; do $(COVTOOL_DIR)/covannotate.exe $$f merged.db >$$f.out ; if [ $$? != 0 ] ; then exit 1; fi ; done
	grep totals: merged.db >totals.out
	diff -uBbhw totals.expect totals.out
	for f in *.cpp *.h ; do diff -Bbhwu $$f.expect $$f.out ; if [ $$? != 0 ] ; then exit 1; fi ; done
	@echo "astyle instrumentation test passed @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
endif

include ../rules.$(shell uname)

CCINCS += -I..

	
all:: merge.test

tests::
	merge.test
	merge.test *.covexp >merged.db # rerun to get useful info
	merge.test *.covexp >merged.db
	$(INSTALL_DIR)/covannotate.exe ../covmerge.c *.db >covmerge.ann
	$(INSTALL_DIR)/covannotate.exe ../read_database.c *.db >read_database.ann

merge.test: ./covmerge.o ./read_database.o $(INSTALL_DIR)/covtoolhelper.o
	$(LN) -o $@ $+


./covmerge.o ./read_database.o:
	$(CC) -E $(CCDEFS) $(CCINCS) -DCOVTOOL_INST ../`basename $@ .o`.c | \
	$(INSTALL_DIR)/covtool.exe -instrument -skip / >`basename $@ .o`.c++
	$(CC) -g -c `basename $@ .o`.c++
	rm `basename $@ .o`.c++

tests::
	if [ ! -e $(INSTALL_DIR)/cov++ ] ; \
	then \
	  echo "find cov++ in $(INSTALL_DIR)" ; \
	  exit 1 ; \
	fi
	

clean::
	rm -fr *.o *.covexp *.db merge.test *.c++ *.ann

tests::
	make -C ../tests/astyle COVTOOL_DIR=$(INSTALL_DIR) INSTRUMENTATION=1 clean
	make -C ../tests/astyle COVTOOL_DIR=$(INSTALL_DIR) INSTRUMENTATION=1 tests
	make -C ../tests/astyle COVTOOL_DIR=$(INSTALL_DIR) INSTRUMENTATION=1 clean
	
	

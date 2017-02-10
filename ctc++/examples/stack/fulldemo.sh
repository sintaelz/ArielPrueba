#!/bin/sh

# deleting possible previous demo generated files.
if [ -f MON.sym ]
then
    rm MON.sym
fi
if [ -f MON.dat ]
then
    rm MON.dat
fi
if [ -d CTCHTML ]
then
    rm -rf CTCHTML
fi

echo
echo "Now instrumenting the example test program stacktest with"
echo "CTC++. stacktest is a simple C++ program consisting of source"
echo "files cstack.cpp, revstack.cpp and stacktst.cpp. Program"
echo "implements a stack data structure and tests its integrity."
echo "With CTC++ we can check the thoroughness of this testing."
echo
echo "Now compiling and linking the instrumented version of the program."
echo "When working with makefiles, the recommended (and most simple) way"
echo "to do the instrumentation would be to to prepend the make command"
echo "with "ctcwrap ctc-options make ....". It could be used also in this"
echo "case, because the makefile here emits the compile and link command"
echo "without path."
echo
echo "However, here we arrange the makefile to emit directly the ctc"
echo "instrumentation commands. The makefile has variables CXX and LINK,"
echo "which we replace as follows:"
echo
echo "make \"CXX=ctc -i m g++\" \"LINK=ctc g++\" clean all"
echo
echo "Press enter to continue"
read foo
make "CXX=ctc -i m g++" "LINK=ctc g++" clean all

echo
echo "As a result we have instrumented executable stacktest."
echo "Let's run it:"
echo
echo "Press enter to continue"
read foo
echo "./stacktest"
./stacktest
echo
echo "Press enter to continue"
read foo

echo
echo "Now we run ctcpost to get Execution Profile Listing to stdout, as follows:"
echo
echo "ctcpost MON.sym MON.dat -p - | more"
echo
echo "Press enter to continue"
read foo
ctcpost MON.sym MON.dat -p - | more

echo
echo "Press enter to continue"
read foo
echo
echo "There's also Untested Code Listing. Let's see how it looks:"
echo
echo "ctcpost MON.sym MON.dat -u - | more"
echo "Press enter to continue"
read foo
ctcpost MON.sym MON.dat -u - | more

echo
echo ---End of demo---

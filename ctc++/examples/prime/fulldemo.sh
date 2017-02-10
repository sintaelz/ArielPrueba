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
echo "Now instrumenting the example program prime with CTC++."
echo "Prime is a simple program consisting of source files prime.c,"
echo "calc.c and io.c. Program prompts for numbers and tells whether"
echo "they are prime or not. End with 0 input."
echo
echo "Press enter to continue"
read foo

echo "We have a makefile for doing the builds. First we clean the project by"
echo "issuing command:"
echo
echo "make clean"
echo
echo "Press enter to continue"
read foo
make clean
echo "Press enter to continue"
read foo

echo
echo "Normally we would build the program by issuing command"
echo
echo "make all"
echo
echo "But we do the build with ctc by prepeding "ctc ctc-options" in front"
echo "of the make command, here as follows:"
echo
echo "ctcwrap -v -i mti make all"
echo
echo "We use ctc-options -v (verbose, for learning what ctc does internally at"
echo "each compile and link command) and -i mti (instrument for multicondition"
echo "coverage and for inclusive timing)."
echo "Press enter to continue"
read foo

echo
ctcwrap -v -i mti make all
echo
echo "Press enter to continue"
read foo

echo
echo "Now we have instrumented Prime. At the instrumentation phase a symbolfile"
echo "(MON.sym) was created, see"
ls -al MON.sym
echo
echo "Now we run the program with some input."
echo "Press enter to continue"
read foo

echo "./prime"
echo "1" > demo.tmp
echo "23" >> demo.tmp
echo "666" >> demo.tmp
echo "100434334" >> demo.tmp
echo "16" >> demo.tmp
echo "32" >> demo.tmp
echo "3782098" >> demo.tmp
echo "223" >> demo.tmp
echo "3" >> demo.tmp
echo "0" >> demo.tmp
./prime < demo.tmp
rm demo.tmp
echo
echo "Press enter to continue"
read foo

echo
echo "In the test run a datafile (MON.dat) was created, see"
ls -al MON.dat
echo
echo "Press enter to continue"
read foo

echo
echo "Now see what kind of code coverage we got on this program. We take"
echo "Execution Profile Listing to stdout with command:"
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
echo "We can take the same listing to a file and then convert it to HTML"
echo "form with commands:"
echo
echo "ctcpost MON.sym MON.dat -p profile.txt"
echo "ctc2html -i profile.txt"
echo
echo "Press enter to continue"
read foo
ctcpost MON.sym MON.dat -p profile.txt
ctc2html -i profile.txt
echo
echo "Some CTCHTML/*.html files got born. Start your browser from file"
echo "CTCHTML/index.html for seeing the HTML representation."
echo
echo "Press enter to continue"
read foo

echo
echo "The code was instrumented also for timing. Lets see how the"
echo "Execution Time Listing looks. We use command:"
echo
echo "ctcpost MON.sym MON.dat -t - | more"
echo
echo "Press enter to continue"
read foo
ctcpost MON.sym MON.dat -t - | more
echo
echo "Press enter to continue"
read foo

echo
echo "You may want to play with this example by your own. Instrument this with"
echo "different instrumentation options, run the program multiple times with"
echo "different input and see if you get the coverage TER% to grow, etc."
echo
echo "---End of demo---"

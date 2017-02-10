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
echo "In this example we have a main program (main.c), which we"
echo "do not instrument. The main program calls two static libraries"
echo "(in files strutil.c and reverse.c correspondingly), which we"
echo "instrument. We have a makefile for doing the builds."
echo
echo "First we clean the project by issuing command:"
echo
echo "make clean"
echo
echo "Press enter to continue"
read foo
make clean

echo
echo "Now we compile the main.c file without ctc, as follows:"
echo
echo gcc -c main.c
echo
echo "Press enter to continue"
read foo
gcc -c main.c

echo
echo "Now we compile the rest of the project files by the makefile."
echo "Normally it would be done as follows"
echo
echo "make all"
echo
echo "But we issue command:"
echo
echo "ctcwrap -i m make all"
echo
echo "instead. This makes the build as "ctc-build". Note that main.c is"
echo "not recompiled (i.e. it remains as uninstrumented)."
echo
echo "Press enter to continue"
read foo
ctcwrap -i m make all

echo
echo "As a result we have instrumented executable multilib. Let's run it:"
echo

echo "Press enter to continue"
read foo
echo "./multilib"

./multilib

echo
echo "Press enter to continue"
read foo
echo "Now we run ctcpost to get profile listing to stdout"
echo
echo "To do this we run command:"
echo "ctcpost MON.sym MON.dat -p - | more"
echo
echo "Press enter to continue"
read foo

ctcpost MON.sym MON.dat -p - | more

echo
echo "Press enter to continue"
read foo
echo "Now we generate the same listing to a file and convert to it"
echo "to HTML form with commands:"
echo
echo "ctcpost MON.sym MON.dat -p profile.txt"
echo "ctc2html -i profile.txt"
echo
echo "Press enter to continue"
read foo

ctcpost MON.sym MON.dat -p profile.txt
ctc2html -i profile.txt

echo
echo "HTML-browsable files can now be found from subdirectory CTCHTML."
echo "Browsing starts from file index.html."
echo
echo "---End of demo---"

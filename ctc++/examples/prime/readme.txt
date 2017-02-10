
CTC example
-----------

This directory contains following files

   readme.txt      -- This file
   makefile        -- Makefile
   fulldemo.sh     -- Demo-script

                      \
   calc.c          --  \
   calc.h          --   \
   io.c            --   / Program source files
   io.h            --  /
   prime.c         -- /

This example demonstrates testing of a (very) simple program with CTC++.

Following targets are defined for the makefile

   make all      Build the example (default target), prime
   make clean    Remove files produces with this makefile

To see a demo of the CTC++-usage with prime-program run the script
fulldemo.sh.

######################################################################
#
# This is a sample makefile for cstack example for unix/linux
#
#                  Copyright (c) 2001-2011 Testwell Oy
######################################################################
# Last modified 6.9.2011

# C++ Compiler
CXX     = g++

# C++ Linker
LINK    = g++

######################################################################

# Executable name
EXENAME = stacktest

# Sourcefiles and objectfiles
SRCS    = cstack.cc revstack.cc stacktst.cc
OBJS    = $(SRCS:.cc=.o)


# Rule for compiling .cc files:
.cc.o:
	$(CXX) -c $<


# The main target, builds executable
all: $(OBJS)
	$(LINK) -o $(EXENAME) $(OBJS)

# Clean target
clean:
	rm -f $(OBJS) $(EXENAME)

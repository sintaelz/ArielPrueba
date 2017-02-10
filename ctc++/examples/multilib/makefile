######################################################################
#
# This is a sample makefile for multilib example for unix/linux
#
#                  Copyright (c) 2000-2011 Testwell Oy
######################################################################
# Last modified 6.9.2011

# C Compiler
CC              = gcc

# C Linker
LINK            = gcc

LD              = ld
AR              = ar

######################################################################

# Executable name
EXENAME = multilib

# Sourcefiles and objectfiles
SRCS            = main.c reverse.c strutil.c
OBJS            = $(SRCS:.c=.o)

# Names of libraries
REVLIB        	= libreverse.a
STRLIB        	= libstrutil.a

# The main target, builds executable
all: compobj libcomp linkprog

# Rule for compiling .c files:
.c.o:
	$(CC) -c $<

# Builds objects
compobj: $(OBJS)

# Builds libraries
libcomp:
	$(LD) -r -o $(REVLIB:.a=.o) reverse.o
	$(AR) r $(REVLIB) $(REVLIB:.a=.o)
	rm $(REVLIB:.a=.o)
	$(LD) -r -o $(STRLIB:.a=.o) strutil.o
	$(AR) r $(STRLIB) $(STRLIB:.a=.o)
	rm $(STRLIB:.a=.o)

# Links object and libraries to create executable
linkprog:
	$(LINK) -o $(EXENAME) main.o $(REVLIB) $(STRLIB)

# Clean target
clean:
	rm -f $(REVLIB) $(STRLIB) $(OBJS) $(EXENAME) *~ core


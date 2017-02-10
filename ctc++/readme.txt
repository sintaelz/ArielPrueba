Testwell Oy                             CTC++ System Version 8.1 for
Verifysoft Technology GmbH              Linux x86/ELF
27 December 2016


This readme.txt file contains Linux platform-specific information about
installation and use of Testwell CTC++, Test Coverage Analyzer for C/C++.

For general, platform-independent information about CTC++, see the CTC++
User's Guide. For a list of changes in this version, see the version.txt
file.


CONTENTS:

  Hardware and Software Environment Compatibility
  Installation Disk
  Installation Procedure
    General
    Considerations about the installation directory
    License control, installing a permanent floating license
    License control, installing an evaluation copy license
    PERL 5 interpreter
    Bringing new compile and link commands to ctcwrap support
  Uninstalling
  Remark of ctc.h, libctc.a and libctc64.a files
  64-bit support
  How to check if a file is instrumented
  Getting Help


========================================================================


Hardware and Software Environment Compatibility
-----------------------------------------------

The binaries in this Linux distribution were built on Red Hat Enterprise
Linux 4, gcc 3.4.6 C compiler.


Installation Disk
-----------------

The CTC++ installation disk contains the following files:

  makefile       Installation makefile
  ctc            CTC++ preprocessor program
  ctcpost        CTC++ postprocessor program
  ctc2html       CTC++ to HTML converter utility
  ctc2excel      CTC++ to TSV (tab-separated values) converter utility
  ctcxmlmerge    CTC++ XML merger utility
  ctcwrap        CTC++ wrapper for Unix utility
  ctcagent       An auxiliary script used by ctcwrap
  ctc2dat        CTC++ host-target receiver utility (also used internally
                 by libctc64.a)
  libctc.a       CTC++ run-time library (depending on the delivery there
                 can also be libctc.so)
  libctc64.a     CTC++ 64-bit run-time library (depending on the delivery
                 there can also be libctc64.so)
  ctc.h          CTC++ header file
  ctc.ini        Default configuration and license file
  ctc2html.ini   Default configuration file for ctc2html
  ctc.1          Unix man-page for the CTC++ preprocessor
  ctcpost.1      Unix man-page for the CTC++ postprocessor
  ctc2html.1     Unix man-page for the CTC++ to HTML converter utility
  ctc2excel.1    Unix man-page for the CTC++ to TSV converter utility
  ctcxmlmerge.1  Unix man-page for the CTC++ XML merger utility
  ctcwrap.1      Unix man-page for the CTC++ wrapper utility
  ctc2dat.1      Unix man-page for the CTC++ receiver utility
  readme.txt     This file
  version.txt    Version information
  doc/*          Directory containing the CTC++ User's Guide and other
                 documentation files, see doc/readme.txt
  examples/*     Directory containing examples of CTC++ usage, see
                 examples/multilib/readme.txt, examples/prime/readme.txt
                 and examples/stack/readme.txt


Installation Procedure
----------------------

General
- - - -

Installation is done by the makefile. For running it you first have to
specify a root directory ($prefix) for the CTC++ installation. It must
be an existing directory. The makefile copies the CTC++ files to the
following directories, relative to $prefix:

- $prefix/bin: CTC++ executables
- $prefix/lib: CTC++ run-time libraries
- $prefix/man/man1: CTC++ man pages
- $prefix/lib/ctc: other CTC++ files
- $prefix/include: ctc.h file

The installation directory can be whatever directory you choose. For
example, it might be /opt/testwell/ctc_v8.1, and the installation
command could be

   make install prefix=/opt/testwell/ctc_v8.1 \
                ...plus sometimes something more, see below

After executing the makefile the following needs to be done:

- add /opt/testwell/ctc_v8.1/bin to PATH (for finding ctc executables)
- add /opt/testwell/ctc_v8.1/man to MANPATH (for finding ctc manpages)
- define environment variable CTCHOME to point to
  /opt/testwell/ctc_v8.1/lib/ctc (for ctc executables to find ctc.ini)

Starting from CTC++ v8.0, when reinstalling to same directory, the
installation makefile no more takes copies of previously installed CTC++
files (renaming them with .old extension). Instead, now the possible
previous CTC++ files are silently overwritten and removing the possible
.old named copies of them.


Considerations about the installation directory
- - - - - - - - - - - - - - - - - - - - - - - -

Depending on what the installation directory is, you may or may not need
admin rights to install CTC++ there. When you want to get rid of CTC++,
and if the installation directory contains only CTC++ files, simply remove
the $prefix directory. When an upgrade version comes, say v8.1, it could
be installed to /opt/testwell/ctc_v8.1, and the PATH, MANPATH and CTCHOME
need to be adjusted correspondingly.

If you install CTC++ to /usr/local:
- you presumably need admin rights to do it
- the /bin and /man directories may already be in your PATH and MANPATH
- in ctc executables it is hard-coded that they seek ctc.ini from
  /usr/local/lib/ctc/ctc.ini, i.e. CTCHOME need not be defined
- when you want to get rid of CTC++, it may be laborious to pick the
  CTC++ files from among the many other non-CTC++ files that are in
  these directories
- in your system, you can have only one CTC++ version in use, the latest

If you install CTC++ to your HOME directory, to ~ :
- you do not need admin rights to do it
- the ~/bin and ~/man directories may already be in your PATH and MANPATH
- in ctc executables it is hard-coded that they seek ctc.ini also from
  ~/lib/ctc/ctc.ini, i.e. CTCHOME need not be defined
- when you want to get rid of CTC++, it may be laborious to pick the
  CTC++ files from among the many other non-CTC++ files that are in
  these directories
- in your system, you can have only one CTC++ version in use, the latest


License control, installing a permanent floating license
- - - - - - - - - - - - - - - - - - - - - - - - - - - -

In CTC++ executables and in the instrumented executable there is license
control. In the installation this needs to be taken into notice as
discussed below.

Permanent CTC++ licenses on this platform are floating licenses. They are
controlled by Flexlm license manager. There is a separate delivery package
and installation on the Flexlm license server software. It may be installed
to another machine, which even may not be running Linux, than this Linux
machine, where you are now installing CTC++.

How the licensed CTC++ components check out the license (more precisely,
how they establish connection to the license server for doing the license
check out) can be arranged in a couple of ways. Often it is done by the
LM_LICENSE_FILE environment variable. It is discussed more in the Flexlm
server software delivery package, in its readme.txt. Many IT departments
use LM_LICENSE_FILE environment variable to arrange the connection to the
license server for the Flexlm-licensed tools.

Use of LM_LICENSE_FILE arrangement is not mandatory. If LM_LICENSE_FILE
arrangement is not used, there needs to be advice in ctc.ini file how the
connection to the license server is established. The installation script
updates this information into ctc.ini file, and you have to give it when
starting the installation.

This could be done as follows:

   make install prefix=/opt/testwell/ctc_v8.1 \
                FLEXLICFILE=27000@flxservermachinename

While the following example

   make install prefix=/opt/testwell/ctc_v8.1

is for the situation, where you rely that LM_LICENSE_FILE arrangement is
used (and in the ctc.ini file this "advice" is marked as "empty").

However, both the LM_LICENSE_FILE arrangement and advice in the ctc.ini
file can be used. If the license server connection succeeds based on
LM_LICENSE_FILE, it will be used. If connection cannot be established
based on LM_LICENSE_FILE, the advice from ctc.ini file will be tried next.
(There is still ~/.flexlmrc file, where Flexlm maintains successful
connections and consults as needed)

So, you install a permanent floating license with either of the two ways
as shown in the above examples. After running the makefile you need to
check environment variables PATH, MANPATH and CTCHOME in the way as
discussed above.


License control, installing an evaluation copy license
- - - - - - - - - - - - - - - - - - - - - - - - - - - -

Installing an evaluation copy is done by the makefile basically in the
same way as permanent floating license. Normally, however, an evaluation
copy is not technically a floating license. Instead, it is a node-locked
license to one (or to a couple of) specified machines only, and has an
expiration date.

License control of evaluation copy can be established by 'testwell.lic'
file or it can be established by adjusting ctc.ini file. Flexlm license
manager software is not needed.

When testwell.lic file is used (you have got this file separately from
the vendor), installing would go as follows (example):

   make install prefix=/opt/testwell/ctc_v8.1 \
                FLEXLICFILE=/opt/testwell/ctc_v8.1/lib/ctc/testwell.lic

and after having adjusted PATH, MANPATH and CTCHOME you copy testwell.lic
file to directory /opt/testwell/ctc_v8.1/lib/ctc.

When ctc.ini file is used (you have got COMPUTER, EXPIRATION and CONTROL
arguments separately from the vendor), installing would go as follows
(example)

   make install prefix=/opt/testwell/ctc_v8.1 \
                COMPUTER="Linux 123.44.55.66" \
                EXPIRATION="15 Apr 2017" \
                CONTROL=ABCDEFGHIJKL

and then PATH, MANPATH and CTCHOME are adjusted as needed.

Alternatively, when ctc.ini file is used in license control, it may
already be adjusted for a working evaluation copy setup. In such a case
the installation would go as follows (example)

   make install $prefix=/opt/testwell/ctc_v8.1

and then PATH, MANPATH and CTCHOME are adjusted as needed.


PERL 5 interpreter
- - - - - - - - -

The ctc2html, ctc2excel, and ctcwrap utilities require a Perl 5 interpreter.
If you don't have a Perl interpreter on your system, you can download the
latest version from, for example, http://www.perl.org/

Some of the CTC++ utilities are perl scripts. The installation makefile
looks your system from certain commonly used directories where you have
Perl interpreter and updates the Perl script headers a working reference
to the Perl interpreter. If that fails, you are informed and you need to
fix that manually.


Bringing new compile and link commands to ctcwrap support
- - - - - - - - - - - - - - - - - - - - - - - - - - - - -

In your system you may have other compile commands in use than CTC++ is
prepared for by default. For example besides gcc (normal/default gcc), you
might have gcc3 (some special old gcc version). For getting CTC++ to work
also with gcc3 command you have to introduce it to the ctc.ini file (see
the User's Guide on how to do it).

There is an issue with CTC++'s ctcwrap utility. For example the following

   ctcwrap -i d make -f makefile_emitting_gcc_commands.mak

works after default CTC++ installation. But the following

   ctcwrap -i d make -f makefile_emitting_gcc3_commands.mak

does not. For getting this to work (and after gcc3 command has been
introduced in ctc.ini file), you have to go to $prefix/lib/ctc/wrap
directory and define there similar symbolic link for gcc3 as there is
for gcc and some other compile and link commands.


Uninstalling
------------

Remove manually the files and directories that the installation makefile
had created. See the installation makefile what they were.

You might also want to polish PATH, MANPATH and CTCHOME environment
variables from CTC++.

If you have made a copy of the configuration file ctc.ini to the name
.ctc.ini in your home directory or to any working directory, these files
can be removed, too. Remove the $HOME/ctcopts.rsp file, if one exists.


Remark of ctc.h, libctc.a and libctc64.a files
----------------------------------------------

When CTC++ instruments a source file, it uses the compiler to compile
the instrumented version of it. In this compilation ctc.h file is needed.
The installation makefile records to ctc.ini file the directory where the
ctc.h file resides. And based on that the ctc-machinery can use proper -I
option at the compile. The points here are a) the installation directories
and ctc.ini must be in sync, and b) ctc.h need not be copied to any such
directory from where the compiler generally finds included files.

Similarly as with ctc.h, the installation makefile records into ctc.ini
where the libctc.a and libctc64.a reside. When ctc-machinery generates
a link command for the instrumented executable, it specifies the ctc
run-time library file with explicit path. By default the 32-bit variant
libctc.a will be used, unless the installation makefile has detected that
it's a 64-bit machine (x86_64) in which case the 64-bit variant libctc64.a
will be used instead.


64-bit support
--------------

When CTC++ is used to instrument 64-bit code, the CTC++ 64-bit library
libctc64.a must be used instead, not the default 32-bit libctc.a. As of
version 8.1, the installation makefile sets libctc64.a as the default
on a 64-bit machine (x86_64).

The library that will be used is specified by the configuration parameter
LIBRARY. The configuration file (ctc.ini) default setting can be overridden
using the -C option at the command line. For example,

   ctc ... -C LIBRARY=-L/opt/testwell/ctc_v8.1/lib,-lctc64 gcc -m64 ...

where /opt/testwell/ctc_v8.1/lib is the directory containing the CTC++
libraries.

If CTC++ is used solely or mainly for 64-bit code, the LIBRARY setting can
be changed permanently in ctc.ini. Replace the current setting by the
following:

   LIBRARY = -L/opt/testwell/ctc_v8.1/lib,-lctc64

Note that libctc64.a uses internally the ctc2dat* utility when writing
coverage data to a datafile. For this reason, ctc2dat* must be in PATH.

The 64-bit library libctc64.a was built on an x86_64 machine using gcc
version 4.6.


How to check if a file is instrumented
--------------------------------------

You may use some utility being able to read binary files and try to
search some traces of instrumentation from your object files, libraries,
executables, etc. For example,

   grep -c "ctc_register_module" myprog

If the count is zero, the file is not instrumented.

Here's another example:

   strings -a myprog | grep "ctc_register_module"

If no "ctc_register_module" lines are displayed, the file is not
instrumented.

If your test run does not produce coverage data, it may be that you are
after all running the original/uninstrumented version of the program. To
check this you could temporarily rename the ctc.ini configuration file
to some other name and then do a test run. If an instrumented executable
is run and it does not find ctc.ini file, you should receive the following
error message from the CTC++ run-time library:

   CTC++ run-time error 8: Cannot open file ctc.ini

If you are sure that you executed instrumented executable but you still
did not get this error message, the explanation may be that not any
instrumented function was called during the program run. Perhaps not all
program files were instrumented.

If, after having performed the above checks, you are convinced that the
instrumented executable gets executed, but you still do not find the
datafile, see the chapter "Saving Execution Counters" of the CTC++ User's
Guide for more information about where and when the counters are saved
(or not saved) to a datafile.

Note that there may be several configuration files (see the User's Guide
where CTC++ searched for configuration files). With the command "ctc -V"
(upper-case 'V') you can check what configuration files are found and
loaded.


Getting Help
------------

It is advisable to start by reading the CTC++ User's Guide which is
available in PDF format (Portable Document Format). It resides at
$prefix/lib/ctc/doc/ctcug.pdf.

Besides the User's Guide, the doc directory may also contain other
documentary type of files related to CTC++.

For more information about ctc*, ctcpost*, ctc2html*, ctc2excel*,
ctcwrap*, ctcxmlmerge*, or ctc2dat*, see also their man pages,

   man ctc
   man ctcpost
   man ctc2html
   man ctc2excel
   man ctcwrap
   man ctcxmlmerge
   man ctc2dat

For these man commands to work, you have to had updated MANPATH, or
use -M option to look the man pages from $prefix/man.

There is also an example directory at $prefix/lib/ctc/examples
containing examples of the use of the tool. See the readme.txt files in
each of the example subdirectories for more information.

If you need to ask help from Verifysoft (or from the distributor where
you purchased CTC++), see when_problems.txt in the doc directory for
more information.

--- end of readme.txt ---

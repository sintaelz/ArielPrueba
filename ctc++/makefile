# Testwell Oy
# Verifysoft Technology GmbH
# 27 December 2016
#
# This is a makefile for installing Testwell CTC++ 8.1 (and later)
# on Linux systems.
#
# See the readme.txt for various installation alternatives, how you
# can run this makefile and what you need to do after having run this.
#
.SILENT:

SHELL   = /bin/bash
INSTALL = /usr/bin/install

# Base directory for CTC++ installation. This MUST always be defined,
# something like /usr/local or ~ or /opt/testwell/ctc_vi.j.k
prefix      =/usr/local

# Flexlm license connection. When it needs to be defined, something like
# @host or port@host or full path to the 'testwell.lic' file
FLEXLICFILE =

# In some evaluation copy arrangements, the following three must be defined
COMPUTER    =Any Linux
EXPIRATION  =14 Feb 2017
CONTROL     =PEQBJSEWKNLI

# Path for the CTC++ preprocessor, postprocessor, ctc2html, ctc2excel,
# ctcwrap, ctcxmlmerge, and ctc2dat
BINDIR      = $(prefix)/bin

# Path for libctc.a / .so, and libctc64.a / .so
LIBDIR      = $(prefix)/lib

# Path for the configuration directory (ctc.ini etc.)
INIDIR      = $(LIBDIR)/ctc

# Path for ctc.h
INCDIR      = $(prefix)/include

# Path for man pages
MANDIR      = $(prefix)/man

# Man page section
MANEXT      = 1

# Path for examples
EXAMPLEDIR  = $(INIDIR)/examples

# Path for documentation files
DOCDIR      = $(INIDIR)/doc

# Path for wrap directory
WRAPDIR     = $(INIDIR)/wrap

# Path for temporary files used by CTC++, and also by this makefile
TEMPDIR     = /tmp

# =================================================================

default:
	echo
	echo See readme.txt for the various installation alternatives. For example
	echo it could be done as follows:
	echo
	echo \ \ \ \ make install prefix=/opt/testwell/ctc_vi.j.k \\
	echo \ \ \ \ \ \ \ \ FLEXLICFILE=27000@flxservermachinename
	echo
	echo The installation directory must exist and you need to have rights to
	echo write there. After executing this makefile you need to check and adjust
	echo PATH, MANPATH and CTCHOME environment variables as may be needed.
	echo See readme.txt.
	echo

install: check binaries headers libraries config wrapdir ctcwrapp \
         manpages docs exampledir finis

check:
	if test "$(prefix)" = ""; then                                  \
	  echo The prefix directory must be defined!;                   \
	  exit 1;                                                       \
	fi
	if [ ! -d $(prefix) ]; then                                     \
	  echo The prefix directory $(prefix) does not exist!;          \
	  echo Please create it first or choose some other directory;   \
	  exit 1;                                                       \
	fi
	if test `pwd` = $(TEMPDIR) ; then                               \
	  echo This makefile must not be invoked from the TEMPDIR directory; \
	  exit 1;                                                       \
	fi

binaries:
	echo
	if [ -f $(BINDIR)/ctc.old ]; then                               \
	  rm $(BINDIR)/ctc.old &&                                       \
	  echo Found and removed obsolete $(BINDIR)/ctc.old;            \
	fi
	if [ -f $(BINDIR)/ctcpost.old ]; then                           \
	  rm $(BINDIR)/ctcpost.old &&                                   \
	  echo Found and removed obsolete $(BINDIR)/ctcpost.old;        \
	fi
	if [ -f $(BINDIR)/ctc2html.old ]; then                          \
	  rm $(BINDIR)/ctc2html.old &&                                  \
	  echo Found and removed obsolete $(BINDIR)/ctc2html.old;       \
	fi
	if [ -f $(BINDIR)/ctc2excel.old ]; then                         \
	  rm $(BINDIR)/ctc2excel.old &&                                 \
	  echo Found and removed obsolete $(BINDIR)/ctc2excel.old;      \
	fi
	if [ -f $(BINDIR)/ctcxmlmerge.old ]; then                       \
	  rm $(BINDIR)/ctcxmlmerge.old &&                               \
	  echo Found and removed obsolete $(BINDIR)/ctcxmlmerge.old;    \
	fi
	if [ -f $(BINDIR)/ctc2dat.old ]; then                           \
	  rm $(BINDIR)/ctc2dat.old &&                                   \
	  echo Found and removed obsolete $(BINDIR)/ctc2dat.old;        \
	fi
	if [ ! -d $(BINDIR) ]; then                                     \
	  mkdir -p -m 755 $(BINDIR) &&                                  \
	  echo Created directory $(BINDIR);                             \
	fi
	cp -v ctc ctcpost ctcxmlmerge ctc2dat $(BINDIR) &&              \
	chmod 0755 $(BINDIR)/ctc &&                                     \
	chmod 0755 $(BINDIR)/ctcpost &&                                 \
	chmod 0755 $(BINDIR)/ctcxmlmerge &&                             \
	chmod 0755 $(BINDIR)/ctc2dat
	for p in /bin /usr/bin /usr/local/bin; do                       \
	  [ -x $$p/perl -a ! -d $$p/perl ] && perldir=$$p;              \
	done;                                                           \
	if [ -x $$perldir/perl ]; then                                  \
	  sed < ctc2html > $(TEMPDIR)/ctc2html                          \
	  -e "s%/usr/local/lib/ctc%$(INIDIR)%"                          \
	  -e "s%^#!/usr/bin/perl$$%#!$$perldir/perl%";                  \
	  sed < ctc2excel > $(TEMPDIR)/ctc2excel                        \
	  -e "s%^#!/usr/bin/perl$$%#!$$perldir/perl%";                  \
	  cd $(TEMPDIR);                                                \
	  cp -v ctc2html $(BINDIR) &&                                   \
	  chmod 0755 $(BINDIR)/ctc2html;                                \
	  cp -v ctc2excel $(BINDIR) &&                                  \
	  chmod 0755 $(BINDIR)/ctc2excel;                               \
	  rm ./ctc2html;                                                \
	  rm ./ctc2excel;                                               \
	else                                                            \
	  echo;                                                         \
	  echo "Could not find perl in /bin /usr/bin /usr/local/bin";   \
	  echo "Please edit the correct path to $(BINDIR)/ctc2html";    \
	  echo "and to $(BINDIR)/ctc2excel";                            \
	  echo;                                                         \
	  cp -v ctc2excel $(BINDIR) &&                                  \
	  chmod 0755 $(BINDIR)/ctc2excel;                               \
	  sed < ctc2html > $(TEMPDIR)/ctc2html                          \
	  -e "s%/usr/local/lib/ctc%$(INIDIR)%";                         \
	  cd $(TEMPDIR);                                                \
	  cp -v ctc2html $(BINDIR) &&                                   \
	  chmod 0755 $(BINDIR)/ctc2html;                                \
	  rm ./ctc2html;                                                \
	fi

headers:
	echo
	if [ -f $(INCDIR)/ctc.h.old ]; then                             \
	  rm $(INCDIR)/ctc.h.old &&                                     \
	  echo Found and removed obsolete $(INCDIR)/ctc.h.old;          \
	fi
	if [ ! -d $(INCDIR) ]; then                                     \
	  mkdir -p -m 755 $(INCDIR) &&                                  \
	  echo Created directory $(INCDIR);                             \
	fi
	cp -v ctc.h $(INCDIR) &&                                        \
	chmod 0644 $(INCDIR)/ctc.h

libraries:
	echo
	if [ -f $(LIBDIR)/libctc.a.old ]; then                          \
	  rm $(LIBDIR)/libctc.a.old &&                                  \
	  echo Found and removed obsolete $(LIBDIR)/libctc.a.old;       \
	fi
	if [ -f $(LIBDIR)/libctc.so.old ]; then                         \
	  rm $(LIBDIR)/libctc.so.old &&                                 \
	  echo Found and removed obsolete $(LIBDIR)/libctc.so.old;      \
	fi
	if [ -f $(LIBDIR)/libctc64.a.old ]; then                        \
	  rm $(LIBDIR)/libctc64.a.old &&                                \
	  echo Found and removed obsolete $(LIBDIR)/libctc64.a.old;     \
	fi
	if [ ! -d $(LIBDIR) ]; then                                     \
	  mkdir -p -m 755 $(LIBDIR) &&                                  \
	  echo Created directory $(LIBDIR);                             \
	fi
	if [ -f libctc.a ]; then                                        \
	  cp -v libctc.a $(LIBDIR) &&                                   \
	  chmod 0644 $(LIBDIR)/libctc.a;                                \
	fi
	if [ -f libctc.so ]; then                                       \
	  cp -v libctc.so $(LIBDIR) &&                                  \
	  chmod 0644 $(LIBDIR)/libctc.so;                               \
	fi
	if [ -f libctc64.a ]; then                                      \
	  cp -v libctc64.a $(LIBDIR) &&                                 \
	  chmod 0644 $(LIBDIR)/libctc64.a;                              \
	fi
	if [ -f libctc64.so ]; then                                     \
	  cp -v libctc64.so $(LIBDIR) &&                                \
	  chmod 0644 $(LIBDIR)/libctc64.so;                             \
	fi

config:
	echo
	if [ -f $(INIDIR)/ctc.ini.old ]; then                           \
	  rm $(INIDIR)/ctc.ini.old &&                                   \
	  echo Found and removed obsolete $(INIDIR)/ctc.ini.old;        \
	fi
	if [ -f $(INIDIR)/readme.txt.old ]; then                        \
	  rm $(INIDIR)/readme.txt.old &&                                \
	  echo Found and removed obsolete $(INIDIR)/readme.txt.old;     \
	fi
	if [ -f $(INIDIR)/version.txt.old ]; then                       \
	  rm $(INIDIR)/version.txt.old &&                               \
	  echo Found and removed obsolete $(INIDIR)/version.txt.old;    \
	fi
	if [ -f $(INIDIR)/ctc2html.ini.old ]; then                      \
	  rm $(INIDIR)/ctc2html.ini.old &&                              \
	  echo Found and removed obsolete $(INIDIR)/ctc2html.ini.old;   \
	fi
	if [ ! -d $(INIDIR) ]; then                                     \
	  mkdir -p -m 755 $(INIDIR) &&                                  \
	  echo Created directory $(INIDIR);                             \
	fi
	cp -v readme.txt $(INIDIR) &&                                   \
	chmod 0644 $(INIDIR)/readme.txt
	cp -v version.txt $(INIDIR) &&                                  \
	chmod 0644 $(INIDIR)/version.txt
	sed < ctc.ini > $(TEMPDIR)/ctc.ini                              \
	-e "s;I/usr/local/include;I$(INCDIR);"                          \
	-e "s;L/usr/local/lib;L$(LIBDIR);"                              \
	-e "s;/tmp;$(TEMPDIR);"                                         \
	-e "s;^FLEXLM_LICENSE_FILE.*=.*;FLEXLM_LICENSE_FILE=$(FLEXLICFILE);"
	cd $(TEMPDIR);                                                  \
	if test "$(COMPUTER)" != "" ; then                              \
	  sed < ctc.ini > ctc.ini.tmp                                   \
	  -e "s;^COMPUTER=.*;COMPUTER=$(COMPUTER);" ;                   \
	  mv ctc.ini.tmp ctc.ini;                                       \
	fi;                                                             \
	if test "$(EXPIRATION)" != "" ; then                            \
	  sed < ctc.ini > ctc.ini.tmp                                   \
	  -e "s;^EXPIRATION=.*;EXPIRATION=$(EXPIRATION);"               \
	  -e "s;^NOTE1=.*;NOTE1=License notice: This is a limited period evaluation copy license.;" ; \
	  mv ctc.ini.tmp ctc.ini;                                       \
	fi;                                                             \
	if test "$(CONTROL)" != "" ; then                               \
	  sed < ctc.ini > ctc.ini.tmp                                   \
	  -e "s;^CONTROL=.*;CONTROL=$(CONTROL);" ;                      \
	  mv ctc.ini.tmp ctc.ini;                                       \
	fi;                                                             \
	if test `uname -m` == "x86_64" ; then                           \
	  sed < ctc.ini > ctc.ini.tmp                                   \
	  -e "s;^  # LIBRARY =;  LIBRARY = ;" ;                         \
	  mv ctc.ini.tmp ctc.ini;                                       \
	fi;                                                             \
	cp -v ctc.ini $(INIDIR) &&                                      \
	chmod 0644 $(INIDIR)/ctc.ini;                                   \
	rm ./ctc.ini
	cp -v ctc2html.ini $(INIDIR) &&                                 \
	chmod 0644 $(INIDIR)/ctc2html.ini

manpages:
	echo
	if [ -f $(MANDIR)/man$(MANEXT)/ctc.old.$(MANEXT) ]; then        \
	  rm $(MANDIR)/man$(MANEXT)/ctc.old.$(MANEXT) &&                \
	  echo Found and removed obsolete $(MANDIR)/man$(MANEXT)/ctc.old.$(MANEXT); \
	fi
	if [ -f $(MANDIR)/man$(MANEXT)/ctcpost.old.$(MANEXT) ]; then    \
	  rm $(MANDIR)/man$(MANEXT)/ctcpost.old.$(MANEXT) &&            \
	  echo Found and removed obsolete $(MANDIR)/man$(MANEXT)/ctcpost.old.$(MANEXT); \
	fi
	if [ -f $(MANDIR)/man$(MANEXT)/ctc2html.old.$(MANEXT) ]; then   \
	  rm $(MANDIR)/man$(MANEXT)/ctc2html.old.$(MANEXT) &&           \
	  echo Found and removed obsolete $(MANDIR)/man$(MANEXT)/ctc2html.old.$(MANEXT); \
	fi
	if [ -f $(MANDIR)/man$(MANEXT)/ctc2excel.old.$(MANEXT) ]; then  \
	  rm $(MANDIR)/man$(MANEXT)/ctc2excel.old.$(MANEXT) &&          \
	  echo Found and removed obsolete $(MANDIR)/man$(MANEXT)/ctc2excel.old.$(MANEXT); \
	fi
	if [ -f $(MANDIR)/man$(MANEXT)/ctcxmlmerge.old.$(MANEXT) ]; then \
	  rm $(MANDIR)/man$(MANEXT)/ctcxmlmerge.old.$(MANEXT) &&         \
	  echo Found and removed obsolete $(MANDIR)/man$(MANEXT)/ctcxmlmerge.old.$(MANEXT); \
	fi
	if [ -f $(MANDIR)/man$(MANEXT)/ctcwrap.old.$(MANEXT) ]; then    \
	  rm $(MANDIR)/man$(MANEXT)/ctcwrap.old.$(MANEXT) &&            \
	  echo Found and removed obsolete $(MANDIR)/man$(MANEXT)/ctcwrap.old.$(MANEXT); \
	fi
	if [ -f $(MANDIR)/man$(MANEXT)/ctc2dat.old.$(MANEXT) ]; then    \
	  rm $(MANDIR)/man$(MANEXT)/ctc2dat.old.$(MANEXT) &&            \
	  echo Found and removed obsolete $(MANDIR)/man$(MANEXT)/ctc2dat.old.$(MANEXT); \
	fi
	sed < ctc.1 > $(TEMPDIR)/ctc.$(MANEXT)                          \
	-e "s;^\.TH CTC++ 1;.TH CTC++ $(MANEXT);"                       \
	-e "s;ctcpost (1);ctcpost ($(MANEXT));"                         \
	-e "s;ctc2html (1);ctc2html ($(MANEXT));"                       \
	-e "s;ctc2excel (1);ctc2excel ($(MANEXT));"                     \
	-e "s;ctcxmlmerge (1);ctcxmlmerge ($(MANEXT));"                 \
	-e "s;ctcwrap (1);ctcwrap ($(MANEXT));"                         \
	-e "s;ctc2dat (1);ctc2dat ($(MANEXT));"                         \
	-e "s;/usr/local/lib/libctc.a;$(LIBDIR)/libctc.a;"              \
	-e "s;/usr/local/lib/libctc64.a;$(LIBDIR)/libctc64.a;"          \
	-e "s;/usr/local/include/ctc.h;$(INCDIR)/ctc.h;"                \
	-e "s;/usr/local/bin;$(BINDIR);"
	sed < ctcpost.1 > $(TEMPDIR)/ctcpost.$(MANEXT)                  \
	-e "s;^\.TH ctcpost 1;.TH ctcpost $(MANEXT);"                   \
	-e "s;ctc (1);ctc ($(MANEXT));"                                 \
	-e "s;ctc2html (1);ctc2html ($(MANEXT));"                       \
	-e "s;ctc2excel (1);ctc2excel ($(MANEXT));"                     \
	-e "s;ctcxmlmerge (1);ctcxmlmerge ($(MANEXT));"                 \
	-e "s;ctcwrap (1);ctcwrap ($(MANEXT));"                         \
	-e "s;ctc2dat (1);ctc2dat ($(MANEXT));"                         \
	-e "s;/usr/local/bin;$(BINDIR);"
	sed < ctc2html.1 > $(TEMPDIR)/ctc2html.$(MANEXT)                \
	-e "s;^\.TH ctc2html 1;.TH ctc2html $(MANEXT);"                 \
	-e "s;ctc (1);ctc ($(MANEXT));"                                 \
	-e "s;ctcpost (1);ctcpost ($(MANEXT));"                         \
	-e "s;ctc2excel (1);ctc2excel ($(MANEXT));"                     \
	-e "s;ctcwrap (1);ctcwrap ($(MANEXT));"                         \
	-e "s;ctc2dat (1);ctc2dat ($(MANEXT));"                         \
	-e "s;ctcxmlmerge (1);ctcxmlmerge ($(MANEXT));"
	sed < ctc2excel.1 > $(TEMPDIR)/ctc2excel.$(MANEXT)              \
	-e "s;^\.TH ctc2excel 1;.TH ctc2excel $(MANEXT);"               \
	-e "s;ctc (1);ctc ($(MANEXT));"                                 \
	-e "s;ctcpost (1);ctcpost ($(MANEXT));"                         \
	-e "s;ctc2html (1);ctc2html ($(MANEXT));"                       \
	-e "s;ctcwrap (1);ctcwrap ($(MANEXT));"                         \
	-e "s;ctc2dat (1);ctc2dat ($(MANEXT));"                         \
	-e "s;ctcxmlmerge (1);ctcxmlmerge ($(MANEXT));"
	sed < ctcxmlmerge.1 > $(TEMPDIR)/ctcxmlmerge.$(MANEXT)          \
	-e "s;^\.TH ctcxmlmerge 1;.TH ctcxmlmerge $(MANEXT);"           \
	-e "s;ctc (1);ctc ($(MANEXT));"                                 \
	-e "s;ctcpost (1);ctcpost ($(MANEXT));"                         \
	-e "s;ctc2html (1);ctc2html ($(MANEXT));"                       \
	-e "s;ctc2excel (1);ctc2excel ($(MANEXT));"                     \
	-e "s;ctcwrap (1);ctcwrap ($(MANEXT));"                         \
	-e "s;ctc2dat (1);ctc2dat ($(MANEXT));"                         \
	-e "s;/usr/local/bin;$(BINDIR);"
	sed < ctcwrap.1 > $(TEMPDIR)/ctcwrap.$(MANEXT)                  \
	-e "s;^\.TH ctcwrap 1;.TH ctcwrap $(MANEXT);"                   \
	-e "s;ctc (1);ctc ($(MANEXT));"                                 \
	-e "s;ctcpost (1);ctcpost ($(MANEXT));"                         \
	-e "s;ctc2html (1);ctc2html ($(MANEXT));"                       \
	-e "s;ctc2excel (1);ctc2excel ($(MANEXT));"                     \
	-e "s;ctc2dat (1);ctc2dat ($(MANEXT));"                         \
	-e "s;ctcxmlmerge (1);ctcxmlmerge ($(MANEXT));"                 \
	-e "s;/usr/local/bin;$(BINDIR);"                                \
	-e "s;/usr/local/lib/ctc/wrap;$(WRAPDIR);"
	sed < ctc2dat.1 > $(TEMPDIR)/ctc2dat.$(MANEXT)                  \
	-e "s;^\.TH ctc2dat 1;.TH ctc2dat $(MANEXT);"                   \
	-e "s;ctc (1);ctc ($(MANEXT));"                                 \
	-e "s;ctcpost (1);ctcpost ($(MANEXT));"                         \
	-e "s;ctc2html (1);ctc2html ($(MANEXT));"                       \
	-e "s;ctc2excel (1);ctc2excel ($(MANEXT));"                     \
	-e "s;ctcxmlmerge (1);ctcxmlmerge ($(MANEXT));"                 \
	-e "s;ctcwrap (1);ctcwrap ($(MANEXT));"
	if [ ! -d $(MANDIR) ]; then                                     \
	  mkdir -p -m 755 $(MANDIR) &&                                  \
	  echo Created directory $(MANDIR);                             \
	fi
	if [ ! -d $(MANDIR)/man$(MANEXT) ]; then                        \
	  mkdir -p -m 755 $(MANDIR)/man$(MANEXT) &&                     \
	  echo Created directory $(MANDIR)/man$(MANEXT);                \
	fi
	cd $(TEMPDIR);                                                  \
	cp -v ctc.$(MANEXT) $(MANDIR)/man$(MANEXT) &&                   \
	chmod 0644 $(MANDIR)/man$(MANEXT)/ctc.$(MANEXT);                \
	cp -v ctcpost.$(MANEXT) $(MANDIR)/man$(MANEXT) &&               \
	chmod 0644 $(MANDIR)/man$(MANEXT)/ctcpost.$(MANEXT);            \
	cp -v ctc2html.$(MANEXT) $(MANDIR)/man$(MANEXT) &&              \
	chmod 0644 $(MANDIR)/man$(MANEXT)/ctc2html.$(MANEXT);           \
	cp -v ctc2excel.$(MANEXT) $(MANDIR)/man$(MANEXT) &&             \
	chmod 0644 $(MANDIR)/man$(MANEXT)/ctc2excel.$(MANEXT);          \
	cp -v ctcxmlmerge.$(MANEXT) $(MANDIR)/man$(MANEXT) &&           \
	chmod 0644 $(MANDIR)/man$(MANEXT)/ctcxmlmerge.$(MANEXT);        \
	cp -v ctc2dat.$(MANEXT) $(MANDIR)/man$(MANEXT) &&               \
	chmod 0644 $(MANDIR)/man$(MANEXT)/ctc2dat.$(MANEXT);            \
	cp -v ctcwrap.$(MANEXT) $(MANDIR)/man$(MANEXT) &&               \
	chmod 0644 $(MANDIR)/man$(MANEXT)/ctcwrap.$(MANEXT);            \
	rm ./ctc.$(MANEXT);                                             \
	rm ./ctcpost.$(MANEXT);                                         \
	rm ./ctc2html.$(MANEXT);                                        \
	rm ./ctc2excel.$(MANEXT);                                       \
	rm ./ctcxmlmerge.$(MANEXT);                                     \
	rm ./ctc2dat.$(MANEXT);                                         \
	rm ./ctcwrap.$(MANEXT)

exampledir:
	echo
	if [ ! -d $(EXAMPLEDIR) ]; then                                 \
	  mkdir -p -m 755 $(EXAMPLEDIR) &&                              \
	  echo Created directory $(EXAMPLEDIR);                         \
	fi
	cd examples;                                                    \
	for DIR in prime stack multilib ; do                            \
	  if [ ! -d $(EXAMPLEDIR)/$${DIR} ]; then                       \
	    mkdir -p -m 755 $(EXAMPLEDIR)/$${DIR} &&                    \
	    echo Created directory $(EXAMPLEDIR)/$${DIR};               \
	  fi;                                                           \
	  for FILE in $${DIR}/* ; do                                    \
	    cp -v $${FILE} $(EXAMPLEDIR)/$${DIR} &&                     \
	    chmod 0644 $(EXAMPLEDIR)/$${FILE};                          \
	  done;                                                         \
	  if [ -f $(EXAMPLEDIR)/$${DIR}/fulldemo.sh ]; then             \
	    chmod 0755 $(EXAMPLEDIR)/$${DIR}/fulldemo.sh;               \
	  fi;                                                           \
	done

docs:
	echo
	if [ ! -d $(DOCDIR) ]; then                                     \
	  mkdir -p -m 755 $(DOCDIR) &&                                  \
	  echo Created directory $(DOCDIR);                             \
	fi
	cd doc;                                                         \
	for FILE in *.* ; do                                            \
	  if [ -f $(DOCDIR)/$${FILE}.old ]; then                        \
	    rm $(DOCDIR)/$${FILE}.old &&                                \
	    echo Found and removed obsolete $(DOCDIR)/$${FILE}.old;     \
	  fi;                                                           \
	  cp -v $${FILE} $(DOCDIR) &&                                   \
	  chmod 0644 $(DOCDIR)/$${FILE};                                \
	done

wrapdir:
	echo
	if [ ! -d $(WRAPDIR) ]; then                                    \
	  mkdir -p -m 755 $(WRAPDIR) &&                                 \
	  echo Created directory $(WRAPDIR);                            \
	fi
	if [ -f $(WRAPDIR)/ctc ]; then                                  \
	  rm $(WRAPDIR)/ctc;                                            \
	fi
	if [ -f $(WRAPDIR)/gcc ]; then                                  \
	  rm $(WRAPDIR)/gcc;                                            \
	fi
	if [ -f $(WRAPDIR)/cc ]; then                                   \
	  rm $(WRAPDIR)/cc;                                             \
	fi
	if [ -f $(WRAPDIR)/g++ ]; then                                  \
	  rm $(WRAPDIR)/g++;                                            \
	fi
	if [ -f $(WRAPDIR)/c++ ]; then                                  \
	  rm $(WRAPDIR)/c++;                                            \
	fi
	if [ -f $(WRAPDIR)/ld ]; then                                   \
	  rm $(WRAPDIR)/ld;                                             \
	fi
	if [ -f $(WRAPDIR)/ctcagent.old ]; then                         \
	  rm $(WRAPDIR)/ctcagent.old &&                                 \
	  echo Found and removed obsolete $(WRAPDIR)/ctcagent.old;      \
	fi
	# some old CTC++ version still had wrap, move it aside, just in case
	if [ -f $(WRAPDIR)/wrap.old ]; then                             \
	  rm $(WRAPDIR)/wrap.old &&                                     \
	  echo Found and removed obsolete $(WRAPDIR)/wrap.old;          \
	fi
	for p in /bin /usr/bin /usr/local/bin; do                       \
	  [ -x $$p/perl -a ! -d $$p/perl ] && perldir=$$p;              \
	done;                                                           \
	if [ -x $$perldir/perl ]; then                                  \
	  sed < ctcagent > $(TEMPDIR)/ctcagent                          \
	  -e "s%^#!/usr/bin/perl$$%#!$$perldir/perl%";                  \
	  cd $(TEMPDIR);                                                \
	  cp -v ctcagent $(WRAPDIR) &&                                  \
	  chmod 0755 $(WRAPDIR)/ctcagent;                               \
	  rm ./ctcagent;                                                \
	else                                                            \
	  cp -v ctcagent $(WRAPDIR) &&                                  \
	  chmod 0755 $(WRAPDIR)/ctcagent;                               \
	  echo;                                                         \
	  echo "Could not find perl in /bin /usr/bin /usr/local/bin";   \
	  echo "Please edit the correct path to $(WRAPDIR)/ctcagent";   \
	  echo;                                                         \
	fi
	ln -s $(WRAPDIR)/ctcagent $(WRAPDIR)/ctc
	ln -s $(WRAPDIR)/ctcagent $(WRAPDIR)/gcc
	ln -s $(WRAPDIR)/ctcagent $(WRAPDIR)/cc
	ln -s $(WRAPDIR)/ctcagent $(WRAPDIR)/g++
	ln -s $(WRAPDIR)/ctcagent $(WRAPDIR)/c++
	ln -s $(WRAPDIR)/ctcagent $(WRAPDIR)/ld

ctcwrapp:
	echo
	if [ ! -d $(BINDIR) ]; then                                     \
	  mkdir -p -m 755 $(BINDIR) &&                                  \
	  echo Created directory $(BINDIR);                             \
	fi
	if [ -f $(BINDIR)/ctcwrap.old ]; then                           \
	  rm $(BINDIR)/ctcwrap.old &&                                   \
	  echo Found and removed obsolete $(BINDIR)/ctcwrap.old;        \
	fi
	for p in /bin /usr/bin /usr/local/bin; do                       \
	  [ -x $$p/perl -a ! -d $$p/perl ] && perldir=$$p;              \
	done;                                                           \
	if [ -x $$perldir/perl ]; then                                  \
	  sed < ctcwrap > $(TEMPDIR)/ctcwrap                            \
	  -e "s;^#!/usr/bin/perl$$;#!$$perldir/perl;"                   \
	  -e "s;/usr/local/lib/ctc/wrap;$(WRAPDIR);";                   \
	  cd $(TEMPDIR);                                                \
	  cp -v ctcwrap $(BINDIR) &&                                    \
	  chmod 0755 $(BINDIR)/ctcwrap;                                 \
	  rm ./ctcwrap;                                                 \
	else                                                            \
	  sed < ctcwrap > $(TEMPDIR)/ctcwrap                            \
	  -e "s;/usr/local/lib/ctc/wrap;$(WRAPDIR);";                   \
	  cd $(TEMPDIR);                                                \
	  cp -v ctcwrap $(BINDIR) &&                                    \
	  chmod 0755 $(BINDIR)/ctcwrap;                                 \
	  rm ./ctcwrap;                                                 \
	  echo;                                                         \
	  echo "Could not find perl in /bin /usr/bin /usr/local/bin";   \
	  echo "Please edit the correct path to $(BINDIR)/ctcwrap";     \
	  echo;                                                         \
	fi

finis:
	echo
	echo \*\*\* Testwell CTC++ installation makefile completed.
	echo \*\*\* Check PATH, MANPATH and CTCHOME. See readme.txt
	echo

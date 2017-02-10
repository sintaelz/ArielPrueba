// COVTOOL -- test coverage analysis tool.
// Copyright (C) 2002, Lowell Boggs Jr.
// mailto:lowell.boggs@attbi.com

// This file contains free software.  You can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2, or
// (at your option) any later version.

// This source code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Write to the Free Software Foundation, 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA for a copy of the GNU General Public License.
//


#include <read_database.h>
#include <stdlib.h>

//
// This program's purpose is to merge the instrumentation data
// collected by running a program multiple times into a single
// database file.
//
// The file format of the merged database is the same as that
// of the individual rules.  See read_database.c for an explantion.
//
// Here's how you run the program:
//
//   covmerge.exe *.covexp >merged.db
//
// You can then use the merged.db just like any of the covexp
// files -- except that it contains all the information.
//

// the following block must not be separated, it defines the
// version string
char const*
#include "covtool_version"
;
// do not separate this from the #include of covtool_version!


int main(int argc, char **argv)
{
#ifdef COVTOOL_INST
   extern void CvT_StartRecording____();
   CvT_StartRecording____();
#endif

  CvT_Database db;

  ++argv;
  --argc;

  if( argc && string("-v") == argv[0])
  {
    cout << covtool_version << endl;
    exit(1);
  }


  while(argc)
  {
    if(db.insert(*argv))
    {
      cerr << "error reading " << *argv << endl;
    }
    ++argv;
    --argc;
  }

  cout << db;


}

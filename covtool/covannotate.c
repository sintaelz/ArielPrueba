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

#include <covstream.h>
#include <read_database.h>
#include <stdlib.h>

//
// This program annotates a .c or .h file for which instrumentation
// data has been collected.  It produces an output file of the
// following form:
//
//    lines without instrumentation begin with a space
//    lines which have been executed begin with a +
//    lines which were intrumented but not executed begin with -
//
// Here is a realistic example
//
//   #include <stdio.h>
//
//   extern void CvT_StartRecording____();
//
//   int main(int argc, char **argv)
//  -{
//  -   CvT_StartRecording____();     // recording starts after this line
//
//  +   if(argc < 0)                  // got executed
//      {
//  -      exit(100);                 // this will never happen
//      }
//
//  +   exit(1);                      // got executed
//  -   return 0;                     // never executed
//   }
//
// In this example, all executable lines of the program
// show up has having either a - or a + in column 1.
// Data collection doesn't start until the call to CvT_StartRecording____()
// and thus the first line of the program (the open {) and the line
// containing CvT_StartRecording____() dont' show up as being executed
// even though they were -- again because the instrumentation was turned off.
//
// To get this annotation, instrument the above program and execute it.  Then
// use covannotate.exe to print the source code with the -/+ from the data
// collected during the run.  Here's an example invocation of covannotate:
//
//   covannotate.exe main.c *.covexp >main.c.annotated
//
// the following block must not be separated, it defines the
// version string

char const*
#include "covtool_version"
;
// do not separate this from the #include of covtool_version!


int main(int argc, char **argv)
{

  if( argc > 1 && string("-v") == argv[1])
  {
    cout << covtool_version << endl;
    exit(1);
  }

   if(argc < 3 )
   {
      cerr << "Error:  expected 'source-file-name merged-covtool-database ...'"
	   << endl;
	
      exit(1);
   }

   CvT_Database db;

   int db_file=2;

   //
   // merge all the covexp files into a single database
   //

   while( db_file < argc )
   {
    if( db.insert(argv[db_file++]) )
      cerr << "Error reading file "
	   << argv[db_file-1] << endl;
   }

   int count=0;

   string filename = argv[1];

   ifstream src(argv[1]);

   if(src.bad())
   {
     cerr << "Error reading file " << argv[1] << endl;
   }

   // look up the coverage data for this file in the merged
   // database

   string s = string("\"") + filename + "\"";

   s = CovStream::fullname(s);

   string::iterator first = s.begin(); ++first;
   string::iterator last = s.end();   --last;

   s = string(first, last);

   CvT_Database::const_iterator fileinfo = db.find(s);

   bool data_available=true;

   if(fileinfo == db.end())
   {
     cerr << "No instrumented lines found for  " << s << endl;
     data_available = false;
   }

   //
   // for each line in the file, see if it has instrumentation
   // data and if so, interpret executed versus only instrumented
   //

   while(!src.bad() && !src.eof() && !src.fail())
   {
     ++count;         // line number

     string line;

     getline(src, line);

     char const * prefix = " ";

     if(data_available)
     {
	if(fileinfo->second.executed_lines.find(count) !=
	   fileinfo->second.executed_lines.end()
	  )
	{
	  prefix = "+";
	}
	else
	{
	  if(fileinfo->second.instrumented_lines.find(count) !=
	     fileinfo->second.instrumented_lines.end()
	    )
	  {
	    prefix = "-";
	  }
	}
	
     }

     // Jam in the annotation in front of the extant
     // line of text.  When dealing with tabs, convert
     // them to space to avoid mis-allignment.s


     if(line.size() && line[0] == '\t')
     {
       line.erase(0,1);
       cout << prefix << "       " << line << endl;
     }
     else
       cout << prefix << line << endl;

   }


}

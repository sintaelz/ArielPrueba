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


//
//  This file provides access to a database of instrumentation
//  data created by running a program -- perhaps multiple times.
//  To load the database, construct a CvT_Database object and
//  then call its insert method -- giving it the name of the
//  file to read.  This function returns true IF AN ERROR OCCURS.
//  Otherwise, it returns false.
//
//  The file should consist of a sequence of tokens of the
//  following form:
//
//    file: filename instrumented_lines executed_lines percent_covered
//    el: line_no  ...
//    il: line_no ....
//    totals: instrumented_lines executed_lines percent_covered
//
//  The non-number tokens serve as delimiters and formats of the
//  records are fixed.  The parser doesn't care about new lines but
//  when send the database to a stream it is formatted attractively.
//
//  To access the database, insert a covexp log file into it -- perhaps
//  calling the insert method multiple times on multiple files to accumulate
//  them.  Then to process the information for one file, use the find()
//  method to get an iterator into the database where that file's information
//  lies. You can then iterate over the executed lines for that file, or the
//  instrumented lines.  Finally, to process all files in the database, use
//  the begin() and end() methods to get iterators bounding the database.
//


#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include <read_database.h>

using namespace std;

bool
CvT_Database::
insert(string filename)
//
// merge the database found in 'filename' into this
//
{
  string fcopy = filename;

  fcopy += '\0';    // null terminate

  ifstream src(fcopy.data());


  if(src.bad())
    return true;

  string s;

  enum processing_state
  {
    no_file_yet,
    file_header,
    instrumented_lines,
    executed_lines
  };

  value_type::iterator fileinfo = data.end();

  processing_state state = no_file_yet;

  while(!src.eof())
  {
    src >> s;

    if(src.eof())
      break;

    if(!isdigit(s[0]))
    {
      if(s == "totals:")
      {
	string trash;
	
	src >> trash;  // eat the instrumented count
	src >> trash;  // eat the executed count
	src >> trash;  // eat the percent covered
      }
      else
      if(s == "file:")
      {
	string referenced_file;
	
	src >> referenced_file;
	
	fileinfo = data.find(referenced_file);
	
	if(fileinfo == data.end())
	{
	  File_Info empty;
	
	  value_type::value_type tmp(referenced_file, empty);
	
	  fileinfo = data.insert(tmp).first;
	}
	
	src >> referenced_file; // eat the instrumented
	src >> referenced_file; // eat executed
	src >> referenced_file; // eat percent covered
	
	state = file_header;
	
      }
      else
      if(s == "dir:")
      {
	//
	// read but ignore the directory info -- you must recalculate it
	// yourself (or if you output the database it will be printed on the fly)
	//
	string referenced_file;
	
	src >> referenced_file;
	
	src >> referenced_file; // eat the instrumented
	src >> referenced_file; // eat executed
	src >> referenced_file; // eat percent covered
	
	state = no_file_yet;
	
      }
      else
      if(s == "il:")
      {
	if(fileinfo == data.end())
	{
	  cerr << "error in " << filename << ": il token before file token" << endl;
	  exit(1);
	}
	
	state = instrumented_lines;
	
      }
      else
      if(s == "el:")
      {
	if(fileinfo == data.end())
	{
	  cerr << "File " << filename << ": el token before file token" << endl;
	  exit(1);
	}
	
	state = executed_lines;

      }
      else
      {
	cerr << "File " << filename << ": invalid command string '" << s << "'" << endl;
	exit(1);
      }
    }
    else
     switch(state)
     { // handle numbers in the stream

       default:

	  cerr << "File " << filename << ": numbers before il or el token" << endl;
	  exit(1);

	 break;
	
       case instrumented_lines:
	 {
	   int number;
	
	   s += '\0';
	
	   sscanf(s.data(), "%d", &number);
	
	   fileinfo->second.instrumented_lines.insert(number);
	 }
	 break;
	
       case executed_lines:
	 {
	   int number;
	
	   s += '\0';
	
	   sscanf(s.data(), "%d", &number);
	
	   fileinfo->second.executed_lines.insert(number);
	 }
	 break;
	
     }

  }

  return false;

}

struct my_string: public string
{
  my_string(string const &r): string(r) {}
  my_string( char const *l, char const *r): string(l,r) {}

};

#define string my_string

struct directory_stat
{
  int executed_lines;
  int instrumented_lines;
};

typedef map<string, directory_stat*> directory_stat_t;

ostream& operator<< (ostream & s, CvT_Database const &db)
//
// print the coverage database to the specified stream and
// print aggregated numbers for directories and totals.  These
// numbers are computed here rather than relying on any
// values previously read during the insert() method above.
//
{
  CvT_Database::const_iterator i;

  int total_instrumented_lines = 0;
  int total_executed_lines     = 0;

  directory_stat_t dir_stats;

  for(i=db.begin(); i != db.end(); ++i)
  {
    // process each file

    int percent=0;

    if(i->second.instrumented_lines.size())
    {
      percent = i->second.executed_lines.size() * 100;
      percent /= i->second.instrumented_lines.size();
    }

    s << "file: "
      << i->first
      << " "
      << i->second.instrumented_lines.size()
      << " "
      << i->second.executed_lines.size()
      << " "
      << percent
      << endl;

    total_instrumented_lines += i->second.instrumented_lines.size();
    total_executed_lines     += i->second.executed_lines.size();

    { // update the directory status (aggregate up )

       string filename = i->first;

       while( ((int)filename.rfind('/')) > 0)
       { // aggregate up the directory name
	
	 int last_slash = filename.rfind('/');
	
	 char const *dir_start = filename.data();
	 char const *dir_end   = dir_start + last_slash;
	
	 if(last_slash < 0)
	 {
	   static char const *dot = ".";
	
	   dir_start = dot;
	   dir_end   = dot+1;
	
	 }
	
	 string dirname(dir_start, dir_end);
	
		
	 directory_stat_t::iterator ds = dir_stats.find(dirname);
	
	 if(ds == dir_stats.end())
	 {
	   directory_stat t;
	
	   t.executed_lines     = i->second.executed_lines.size();
	   t.instrumented_lines = i->second.instrumented_lines.size();
	
	   directory_stat_t::value_type v(dirname, new directory_stat(t) );
	
	   dir_stats.insert( v );
	
	 }
	 else
	 {
	    directory_stat* p = ds->second;
	
	    p->executed_lines     += i->second.executed_lines.size();
	    p->instrumented_lines += i->second.instrumented_lines.size();
	
	 }
	
	 filename = dirname;  // restart to aggregate up with one higher directory

       }

    }

    if(i->second.instrumented_lines.size())
    {
      // process this file's instrumented lines

      CvT_Database::File_Info::line_table::const_iterator j;

      int formatter = 0;

      s << "il:  ";

      for(j =  i->second.instrumented_lines.begin();
	  j != i->second.instrumented_lines.end();
	  ++j
	 )
      {
	if(0 == (++formatter % 15))
	  s << endl << "     ";
	
	s << *j << " ";
      }

      s << endl;


    }


    if(i->second.executed_lines.size())
    {
      // process this file's executed lines

      CvT_Database::File_Info::line_table::const_iterator j;

      int formatter = 0;

      s << "el:  ";

      for(j =  i->second.executed_lines.begin();
	  j != i->second.executed_lines.end();
	  ++j
	 )
      {
	if(0 == (++formatter % 15))
	  s << endl << "     ";
	
	s << *j << " ";
      }

      s << endl;


    }

  }

  s << "totals: "
    << total_instrumented_lines
    << " "
    << total_executed_lines
    << " "
    << (total_instrumented_lines?
	 (100 * total_executed_lines ) / total_instrumented_lines : 0)
    << endl;

  {
    directory_stat_t::iterator scan;

    for(scan = dir_stats.begin(); scan != dir_stats.end(); ++scan)
    {
      string const      &dirname = scan->first;
      int     instrumented_lines = scan->second->instrumented_lines;
      int     executed_lines     = scan->second->executed_lines;
      int     percent            = 0;

      if(instrumented_lines)
      {
	percent = 100 * executed_lines;
	percent /= instrumented_lines;
      }

      s << "dir: "
	<< dirname
	<< " "
	<< instrumented_lines
	<< " "
	<< executed_lines
	<< " "
	<< percent
	<< endl;
    }

  }

  return s;
}

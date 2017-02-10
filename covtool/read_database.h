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


#ifndef READ_DATABASE_H_INCLUDED
#define READ_DATABASE_H_INCLUDED

#include <map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class CvT_Database
//
// This class defines the information produced by an
// execution of a program instrumented using covtool.exe.
// A CvT_Database is empty when created, you must use the
// member function, insert(), to get data into it from a
// named dtabase file.  Further, multiple insert() calls
// may be made to merge multiple source files.
//
{
public:

  bool insert(string filename);  // load database from filename

  struct File_Info
  {
    typedef set<int> line_table;

    line_table  instrumented_lines;
    line_table  executed_lines;
  };

  typedef map<string, File_Info> value_type;

private:

  value_type data;

public:

  typedef value_type::const_iterator const_iterator;

  const_iterator find(string f) const { return data.find(f); }
  const_iterator begin()        const { return data.begin(); }
  const_iterator end()          const { return data.end(); }


};

ostream& operator<< (ostream&i, CvT_Database const &db);

#endif

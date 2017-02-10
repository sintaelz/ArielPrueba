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
// This is the runtime data collector for covtool.c.  It is not the only
// possible implementation of the classes and methods that the instrumentor
// injects into an instrumented program.  This one doesn't support threads
// or reentrancy within this module (so don't instrument this file!).
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

//
// This file must be linked into the instrumented application AS THE LAST
// OBJECT MODULE before the C++ runtime library.  You must have no instrumented
// objects or libraries (or objects in libraries) after this object on the
// link command line.
//

// this file is very carefully chosen to avoid crashes in the
// collection process.  Be careful with the introduction of new
// container class signatures.  Always use 'Allocator' rather than
// relying on the default allocator. (see below).  Specifically, the
// STL_STANDARD_ALLOC is NOT REENTRANT!

//
// Warning:  do not instrument this file.  You'll get reentrancy
// bugs.
//

//
// Warning: this version of this file doesn't support threads
//

//
// Note:  this file leaks memory at end of process.  So?
//

#if defined(__GNUC__) && (__GNUC__ < 4)

  typedef __malloc_alloc_template<999> Allocator; // a unique allocator for this
						  // file only.  You may have
						  // to change this number (999)
						  // if something you have
						  // instrumented uses it too!
						  // (unlikely, but you never know)

# define REENTRANT_ALLOCATOR(T)  Allocator

# define mapped_type data_type                   // nested inside map<>, name is wierd on g++

#else

# ifdef __hpux
#  define REENTRANT_ALLOCATOR(T) allocator
# else
#  define REENTRANT_ALLOCATOR(T) allocator<T>
# endif

#endif

typedef set<int, less<int>, REENTRANT_ALLOCATOR(int) > line_ref_set;
typedef pair<string const*, line_ref_set>              line_ref_entry;

typedef map<string const*,
	    line_ref_set,
	    less< string const*  >,
	    REENTRANT_ALLOCATOR( line_ref_entry )
	   > line_ref_table;  // map of file names to the lines executed or
			      // lines instrumented

template<class T>
struct Compare_Pair_By_First
{
  Compare_Pair_By_First(){}
  ~Compare_Pair_By_First(){}

  bool operator() (T const &a, T const &b) const
  {
    return a.first < b.first;
  }

};

typedef pair<string,int> base_file_info_entry;

typedef set< base_file_info_entry,
	    Compare_Pair_By_First< base_file_info_entry >,
	    REENTRANT_ALLOCATOR(base_file_info_entry)
	  >
	base_file_info_t;    // map of all files and the count of instrumented
			     // lines.

static bool inits_complete=false;

#if !defined(__GNUC__) && !defined(__hpux)
extern "C"
#endif
static void end_of_task_processing()
{
  inits_complete = false;
}

struct __CvT__module_info____
{
    char const **file;
    int files;
    void const **str;   // string version of file names above
    int *  line;        // pairs of ints stored here
			// the first is the index into file
			// the second is the line number in that file
    int lines;          // count of PAIRS not ints at line
    int struct_size;    // validates this struct
    int * inst;         // array of counts of instrumented lines, ordered liek file
	
    string const **string_table() const // ptrs to file names in string fmt
    {
      return reinterpret_cast<string const**>(str);
    }
						
								
    void construct();
								
    __CvT__module_info____(char const **f, int fs,
			   int   *l, int ls, int *i
			  )
    : file(f),
      files(fs),
      str(0),
      line(l),
      lines(ls),
      struct_size(sizeof(__CvT__module_info____)),
      inst(i)
    {
      construct();
    }
								
    ~__CvT__module_info____();
								
};


static base_file_info_t  *all_files; // merger of all modules info file[]'s
				    // but in string format


static line_ref_table* instrumented_lines=0;

void  __CvT__module_info____::construct()
{

  if(all_files == 0)
    all_files = new base_file_info_t;

  if(instrumented_lines == 0)
    instrumented_lines = new line_ref_table;

  bool save = inits_complete;

  inits_complete = false;  // prevent recursion in this function


  if(struct_size != sizeof( __CvT__module_info____ ))
  {
    cerr << "covtool.exe out of sync with covtoolhelper.c" << endl;

   cerr.flush();
   exit(1);
  }

#if 0
#ifdef DEBUGGING
  cerr << "covertool.exe instrumentation for file " << file[0] << endl;
  cerr << "  files included                     = " << files << endl;
  cerr << "  lines instrumented                 = " << lines << endl;
#endif
#endif

 str = reinterpret_cast<void const**>(new string const*[files]);

 int i;


 for(i=0; i < files; ++i)
 {
   pair<string,int> tmp(file[i], inst[i]);

   base_file_info_t::iterator n = all_files->insert(tmp).first;

   string const &r = n->first;

   str[i] = &r;

 }

#if 0
#ifdef DEBUGGING

 for(i=0; i < files; ++i)
 {
   string const &file_name_copy = *string_table()[i];
   char const *original_file_name = file[i];

   if( file_name_copy != original_file_name )
   {
     cerr << __FILE__ << ": " << __LINE__
	  << " something wrong with str" << endl;

     exit(100);
   }
 }

#endif
#endif

  { // accumulate instrumented lines

    string const **filenames = string_table();

    int i;

    for(i=0; i < lines; ++i)
    {
      int index = 2 * i;

      int file_index        = line[index];
      int instrumented_line = line[index+1];

      string const *filename = filenames[file_index];

      line_ref_table::iterator location = instrumented_lines->find(filename);

      if(location == instrumented_lines->end())
      {

	line_ref_table::mapped_type empty;
	
	line_ref_table::value_type tmp(filename,empty);

	location = instrumented_lines->insert(tmp).first;

      }

      location->second.insert(instrumented_line);


    }

  }


 inits_complete = save;
}



__CvT__module_info____::
~__CvT__module_info____()
{
}

void CvT_StartRecording____()
  {
    static bool first_time=true;

    if(first_time)
    {
      first_time=false;
      atexit(end_of_task_processing);  // shut off recording
    }

#if 0
#ifdef DEBUGGING

    base_file_info_t::iterator scan;

    cerr << "Listing of files with instrumentation. ("
	 << all_files->size() << ")"
	 << endl;

    for(scan = all_files->begin();
	scan != all_files->end();
	++scan
       )
    {
      cerr << scan->first << endl;
    }

#endif
#endif

    inits_complete = true;
  }


// the following object is a pointer so that it won't get
// destructed.  If it were a struct, its destructor would
// get called and we'd have ordering issues to contend with

static line_ref_table * executed_lines;

void __CvT__record_line____(__CvT__module_info____ const *mi,
			    int fileid,
			    int line
			   )
{
  // warning!  perform no string method invocations or
  // any io of any form in this function!  The string class
  // has threading locks that will get violated if you do.

  if(!inits_complete)
    return;

  if(executed_lines == 0)
    executed_lines = new line_ref_table;

  inits_complete = false;

  string const *filename = mi->string_table()[fileid];

  line_ref_table::iterator location = executed_lines->find(filename);

  if(location == executed_lines->end())
  {
    set<int, less<int>, REENTRANT_ALLOCATOR(int) > empty;

    location =
	  executed_lines->insert(line_ref_table::value_type(filename,empty)).first;
  }

  // location now points to the line references for the file of interest

  location->second.insert(line);

  inits_complete = true;
}

struct CvT_dump_database
{
  ~CvT_dump_database()
  {

    int pid = getpid();

    char buffer[200];

    char const *prefix= getenv("COVTOOL_PREFIX");

    if(prefix == 0)
      prefix="cov-run";

    sprintf(buffer, "%s-%d.covexp", prefix, pid);

    ofstream logfile;

    logfile.open(buffer);




    int total_instrumented_lines=0;
    int total_executed_lines = 0;

    // make sure all files appear in the output
    //
    if(executed_lines)
    {
      base_file_info_t::iterator i;

      for(i =  all_files->begin();
	  i != all_files->end();
	  ++i
	 )
      {
	base_file_info_t::value_type const &r = *i;
	
	string const *str = &r.first;
	
	line_ref_table::iterator ref_location = executed_lines->find(str);
	
	if(ref_location == executed_lines->end())
	{
	  set<int, less<int>, REENTRANT_ALLOCATOR(int) > empty;
	  executed_lines->insert(line_ref_table::value_type(str,empty));
	}
	
      }

    }

    line_ref_table::iterator scan;


    if(executed_lines)
    for(scan = executed_lines->begin();
	scan != executed_lines->end();
	++scan
       )
    {
      if(scan->first == 0)
        continue;
      pair<string, int> comparand(*scan->first, 0);

      base_file_info_t::iterator file_location =
					      all_files->find(comparand);

      int percent=0;

      if(file_location->second)
      {
	percent = scan->second.size() * 100;
	percent /= file_location->second;
      }
      else
      {
	continue;
      }


      logfile << "file: "
	   << *scan->first
	   << " "
	   << file_location->second
	   << " "
	   << scan->second.size()
	   << " "
	   << percent
	   ;
	
      total_instrumented_lines += file_location->second;
      total_executed_lines += scan->second.size();

      { // output the executed lines

	line_ref_table::mapped_type::iterator i;
	
	int formatter=0;
	
	if(scan->second.begin() != scan->second.end())
	  logfile << endl << "el:  ";
	
	for(i=scan->second.begin();
	    i != scan->second.end();
	    ++i
	   )
	{
	  if( 0 == (++formatter % 15) )
	  {
	    logfile << endl << "     ";
	  }
	
	
	  logfile << *i << " ";
	}
	
      }

      { // output the instrumented lines

	string const *filename = scan->first;
	
	line_ref_table::iterator fileinfo = instrumented_lines->find(filename);
	
	if(fileinfo != instrumented_lines->end())
	{
	
	  int formatter=0;
	
	  if(fileinfo->second.begin() != fileinfo->second.end())
	    logfile << endl << "il:  ";
	
	  line_ref_table::mapped_type::iterator i;
	
	  for(i=fileinfo->second.begin();
	      i != fileinfo->second.end();
	      ++i
	     )
	  {
	    if( 0 == (++formatter % 15) )
	    {
	      logfile << endl << "     ";
	    }
	
	
	    logfile << *i << " ";
	  }
	
	}
	
      }
      logfile << endl;

    }
    logfile << "totals: "
	 << total_instrumented_lines
	 << " "
	 << total_executed_lines
	 << " "
	 << (total_instrumented_lines?
	      (100 * total_executed_lines ) / total_instrumented_lines : 0)
	 << endl;


  }
};

static CvT_dump_database dump_helper;

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
// This file defines a 'stream' of tokens.  Basically it is the Lex
// mechanism for covtool.c.  You create a stream with a given filename
// then you parse the stream into C++ tokens by calling the CovStream::
// parse_token().  A 'token' is pair of CovStream iterators.  This
// only works because a CovStream is read into memory in its entirety
// when you open it.  Thus all stream iterators point to memory which
// is guaranteed to still exist.
//

#include <covstream.h>
#include <ctype.h>
#include <char_sets.h>
#include <bomb.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <algorithm>

using namespace std;

#define chunk                CovStream::chunk

typedef CovStream::token     token;

CovStream::
CovStream(FILE *f)
{
  // read a file into a CovStream

  int  bytes_read;

  chunks_ = new chunk;

  // read the first chunk

  bytes_read = fread(chunks_->data_, 1, sizeof(chunks_->data_), f);

  chunks_->end_ = chunks_->data_ + bytes_read;

  chunk *scan = chunks_;

  // read the remaining chunks

  while( bytes_read == sizeof(scan->data_) )
  {
    scan->next_ = new chunk;

    scan->next_->offset_ = scan->offset_ + bytes_read;

    scan = scan->next_;

    bytes_read = fread(scan->data_, 1, sizeof(scan->data_), f);

    scan->end_ = scan->data_ + bytes_read;

  }

  file_size_ = scan->offset_ + bytes_read;

}

CovStream::
~CovStream()
{
  chunk *scan = chunks_;

  while(scan)
  {
    chunk *next = scan->next_;

    delete scan;

    scan = next;

  }

}

// define a quick way to check for operator characters:  +, -, *, etc

char operator_chars[256];

#define isoperator(c) operator_chars[unsigned(c)]

static int load_table()
{
  char *scan = operator_chars;
  char *end  = scan + sizeof(operator_chars);

  while(scan != end) *scan++ = 0;

  operator_chars[unsigned('+')] = 1;
  operator_chars[unsigned('-')] = 1;
  operator_chars[unsigned('*')] = 1;
  operator_chars[unsigned('/')] = 1;
  operator_chars[unsigned('=')] = 1;
  operator_chars[unsigned('^')] = 1;
  operator_chars[unsigned('%')] = 1;
  operator_chars[unsigned('|')] = 1;
  operator_chars[unsigned('!')] = 1;
  operator_chars[unsigned('&')] = 1;
  operator_chars[unsigned('<')] = 1;
  operator_chars[unsigned('>')] = 1;
  operator_chars[unsigned(':')] = 1;
  operator_chars[unsigned('?')] = 1;
  operator_chars[unsigned('.')] = 1;

  return 0;
}

int force_table_load = load_table();  // static init loads operator_chars


token
CovStream::
parse_token(iterator start, iterator end)
{
  // skip whitespace and return 1 c++ token

  if(start == end)
    return token(end,end);

  while(start != end)
  {
    char c = *start;

    if( c == '\n' || !isspace(c))
      break;

    ++start;
  }

  if(start == end)
    return token(end,end);

  iterator begin = start;

  switch(*start)
  {
    LETTERS
      {
	while(start != end && ( *start == '_' || isalnum(*start) ) ) ++start;
      }
      break;

    case '.':
      {
	// handle these goofy syntaxes:
	//
	//   .1E-99
	//   a .b
	
	++start;  // accept the .
	
	if( !isdigit(*start) && *start != '*' && *start != '.')
	  break;  // if this isn't part of number, a member function pointer reference or an elipses
		  // call it a 1 character token
	
      }
      // drop through
    NUMBERS
      {
	// we really aren't parsing the language so we don't care about
	// getting tokens exactly right.  expressions are not parsed
	// into binary trees, they are just treated as sequences of
	// tokens that are terminated with a semicolon -- so we don't care
	// about exactness.
	
	while(start != end && ( isalnum(*start) ||
				*start == '.'   ||
				*start == '*'   ||
				*start == '_'
			      )
	     )
	{
	  char c = *start;
	
	  // handle 1.17549435E-38
	
	  if(c == 'e' || c == 'E')   // floatingpoint expontents
	  {
	    ++start;
	
	    if(start != end)
	    {
	       c = *start;
	
	       if(c == '-' || c == '+')
		 ++start;
	
	    }
	
	  }
	  else
	    ++start;
	}
      }
      break;

    case '\'':
      {
	++start;
	
	if(*start == '\\')
	  ++start;
	
	if(start == end) bomb("unexpected end of file");
	
	++start;
	
	if(start == end) bomb("unexpected end of file");
	
	if(*start != '\'')
	  bomb("missing closing single quote");
	
	if(start == end) bomb("unexpected end of file");

	++start;

      }
      break;

    case '"':
      {
	++start;

	while(start != end && *start != '"')
	{
	
	  if(*start == '\\')
	  {
	    ++start;
	  }
	
	  if(start == end)
	    break;

	  ++start;
	}
	
	if(start != end)
	  ++start;
	
      }
      break;

    // we don't care about language constructs
    // we are only interested in recognizing functions
    // and statements, so we don't need to poperly match
    // all operator characters to some real token they are
    // part of.  See the comment about 'NUMBERS' above

    default:

      if(isoperator(*start))
      {
	while(start != end && isoperator(*start))
	  ++start;
      }
      else
	++start;
      break;

  }

  return token(begin,start);

}


#define isSlash(c)  ( c == '/' || c == '\\' )

static void normalizePathname(char const *path,
			      char *dirname,
			      char *basename
			     )
    //
    //  This function removes /../ and /./ fragments from filenames
    //  then gives you the dirname parth of the pathname and the
    //  nodename part.  The dirname will end in /.  Pathnames beginning
    //  with ~ are also supported.  That is, ~/dir/path is equivalent to
    //  $HOME/dir/path and ~user/path is equivalent to $HOME/../user/path
    //
    //
{
    char *dirStart = dirname;

    if(path[1] == ':')
	{ // don't screw up the drive info

	    *dirname++ = path[0];
	    *dirname++ = ':';

	    path += 2;

	    *dirname++ = '/';

	    dirStart = dirname;

	} // don't screw up the drive info
    else
    if(path[0] == '/' && path[1] == '/' && path[3] == '/')
	{ // handle unixifications of the dos drive info

	    *dirname++ = '/';
	    *dirname++ = '/';
	    *dirname++ = path[2];
	    *dirname++ = '/';

	    path += 3;

	    dirStart = dirname;

	} // handle unixifications of the dos drive info
    else if(isSlash(path[0]))
	{ // handle full unix style pathnames
	    *(dirname++) = '/';

	    dirStart = dirname;
	} // handle full unix style pathnames
    else
    if( path[0] == '~' )
	{ // handle user id relative paths ($HOME relative actually)

	    char *home = getenv("HOME");

	    if(home)
		{
		    ++path; // remove the ~ from the input path

		    while(*home)
			{ // copy home dir to output directory

			    *(dirname++) = *(home++);

			} // copy home dir to output directory

		    if(isSlash(*path))
			{ // current user id relative

			    ++path;
			    *(dirname++) = '/';

			} // current user id relative
		    else
			{ // some other user id relative path

			    while(dirname > dirStart &&
				  !isSlash(dirname[-1])
				 )
				{ // remove current user name from path
				    --dirname;
				} // remove current user name from path

			} // some other user id relative path

		}

	} // handle user id relative paths ($HOME relative actually)
    else
	{ // no path specified, assume current directory

	    getcwd(dirname, 256);

	    dirname += strlen(dirname);

	    if( !isSlash(dirname[-1]) )
		*(dirname++) = '/';

	} // no path specified, assume current directory

    // at this point, path pointers to one of the following strings:
    //
    //      name        base name only case
    //      /name/...   pathname case
    //      name/path   curdir relative path


    // at this point, dirname ends in a slash but no nul

    if( ! isSlash(*path) )
	{
	    // basename only case

	    while(path[0] == '.')
		{
		    if(isSlash(path[1]))
			{
			    path += 2;
			}
		    else
		    if( path[1] == '.' && isSlash(path[2]) && dirname > dirStart)
			{
			    --dirname;

			    while(dirname > dirStart &&
				  !isSlash(dirname[-1])
				 )
				    {
					--dirname;
				    }
			    path += 3;
			}
		    else
			{
			    break;
			}

		}

	    char const *scan = path;
	    while(*scan != 0 && !isSlash(*scan)) ++ scan;

	    if(*scan)
		{ // this is a directory relative path

		    while(path < scan)
			{
			    *(dirname++) = *(path++);
			}

		    *(dirname++) = '/';
		} // this is a directory relative path
	    else
		{ // plain vanilla simple name

		    strcpy(basename, path);
		    *dirname = 0;
		    return;
		} // plain vanilla simple name
	}

    while(*path)
	{ // parse directory nodes in the path

	    // assumption:  isSlash(*path) is true right here

	    if(path[1] == '.' && isSlash(path[2]))
		{ // ignore /./

		    path += 2;

		} // ignore /./
	    else
	    if(path[1] == '.' && path[2] == '.' && isSlash(path[3]))
		{ // /../ means go backup up to parent

		    path += 3;

		    if(dirname > dirStart)
			{
			    --dirname;

			    while(dirname > dirStart &&
				  !isSlash(dirname[-1])
				 )
				    {
					--dirname;
				    }
			}


		} // /../ means go backup up to parent

	    // assumption:  isSlash(*path) is true right here
	    // assumption:  isSlash(dirname[0]) is true here

	    char const *scan;

	    for(scan = path+1; *scan && !isSlash(*scan); ++scan);

	    if(*scan == 0)
		{ // this is last node -- quit now

		    if(path[1] == '.' && path[2] == '.' && path[3] == 0)
			{ // handle trailing /..

			    if(dirname > dirStart)
				{
				    --dirname;

				    while(dirname > dirStart &&
					  !isSlash(dirname[-1])
					 )
					    {
						--dirname;
					    }
				}

			} // handle trailing /..

		    *dirname = 0;

		    strcpy(basename, path+1);

		    return;

		} // this is last node -- quit now

	    ++path;

	    while(path < scan) *(dirname++) = *(path++);

	    *(dirname++) = '/';

	} // parse directory nodes in the path
}


string
CovStream::
fullname(string const &s)
{
   char input_name[1025];

   #ifdef DEBUGGING

     if(s[0] != '"')
     {
       bomb("Whoa:  missing \"'s in filename passed to CovStream::fullname");
     }

   #endif

   if(s[0] != '"')
     return s;  // big no no, improper formatting

   string::const_iterator first = s.begin();
   string::const_iterator last = s.end();

   *copy(++first, --last, input_name) = 0;

   char dirname[1025];

   char basename[1025];

   normalizePathname(input_name, dirname, basename);

   string rv = string("\"");
	
   rv += dirname;
   rv += basename;
   rv += "\"";

   return rv;

}

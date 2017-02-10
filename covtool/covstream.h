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


#ifndef COVSTREAM_H_INCLUDED
#define COVSTREAM_H_INCLUDED

#include <stdio.h>
#include <utility>  /* to get pair */
#include <string>
#include <cstring>

#ifndef __hpux
using namespace std;
#endif

class CovStream
  //
  // A CovStream is a source of C++ source characters including the
  // preprocessor injected. line and file specifications.  The assumption
  // is that a the source text has already been run CPP.  No macro processing
  // is done.
  //
  // A CovStream is a linked list of blocks of text.  CovStream has
  // an iterator that knows how to skip magically across the blocks so
  // the caller doesn't have to know about the chunking up of the input
  // text.  It is a forward only iterator, and refers to a location in
  // the input stream -- which, again, is stored in ram.  Incrementing
  // the iterator moves iterator by exactly 1 character, not a token.
  //
{

  struct chunk
  {
     chunk *next_;

     char data_[37268];
     char *end_;         // points into data_
     long offset_;       // from file start

     chunk(): next_(0), end_(0), offset_(0) {}
  };

  chunk *chunks_;

  long file_size_;

public:

  long file_size() const { return file_size_; }

  struct iterator;

  friend struct iterator;

  struct iterator
  {

    char * ptr_;
    char * end_; // a copy of chunk_->end_ to speed up comparisons

    chunk* chunk_;

    char operator*() const { return *ptr_; }

    iterator& operator++()
    {
      if(ptr_ == end_)
      {
	if(chunk_->next_)
	{
	  chunk_ = chunk_->next_;
	  ptr_   = &chunk_->data_[0];
	  end_   = chunk_->end_;
	}
	else
	{
	  ptr_ = 0;
	  end_ = 0;
	}

      }
      else
      {
	++ptr_;

	if(ptr_ == end_ )
	{

	  if(chunk_->next_)
	  {
	    chunk_ = chunk_->next_;
	    ptr_   = &chunk_->data_[0];
	    end_   = chunk_->end_;
	  }
	  else
	  {
	    ptr_ = 0;
	    end_ = 0;
	  }
	}

      }

      return *this;
    }

    iterator operator++(int)
    {
      iterator old = *this;

      if(ptr_ == end_)
      {
	if(chunk_->next_)
	{
	  chunk_ = chunk_->next_;
	  ptr_   = &chunk_->data_[0];
	  end_   = chunk_->end_;
	}
	else
	{
	  ptr_ = 0;
	  end_ = 0;
	}

      }
      else
      {
	++ptr_;

	if(ptr_ == end_ )
	{

	  if(chunk_->next_)
	  {
	    chunk_ = chunk_->next_;
	    ptr_   = &chunk_->data_[0];
	    end_   = chunk_->end_;
	  }
	  else
	  {
	    ptr_ = 0;
	    end_ = 0;
	  }
	}

      }

      return old;
    }

    bool operator== (iterator const &r) const
      {
	return ptr_ == r.ptr_;
      }
    bool operator!= (iterator const &r) const { return ptr_ != r.ptr_; }


  };


  iterator begin() const
  {
    iterator tmp;

    if(chunks_)
    {

      tmp.chunk_ = chunks_;
      tmp.ptr_   = &chunks_->data_[0];
      tmp.end_   = chunks_->end_;
    }
    else
    {
      tmp.chunk_ = 0;
      tmp.ptr_   = 0;
      tmp.end_   = 0;
    }

    return tmp;
  }

  iterator end() const
  {
    iterator tmp;

    tmp.chunk_ = 0;
    tmp.ptr_   = 0;
    tmp.end_   = 0;

    return tmp;
  }

  CovStream(FILE*);   // read file into a CovStream

  ~CovStream();       // destroy and free memory

  typedef pair<iterator,iterator> token;

  static token parse_token(iterator start, iterator end);
					  // parse C++ tokens from start
					  // iterator position, returning
					  // iterator to 1 character past
					  // the token.  Won't go past
					  // end position.  token.first
					  // is begin of token, token.second
					  // is end of token -- the point from
					  // which subsequent parsing should
					  // continue

  static string fullname(string const &); // convert a string of the form
					  // "../somefile" (including '"'s)
					  // to the form
					  // "/dir/somefile".  Meaning, it
					  // resolves . and .. in the filename
					  // to the full pathanmes.

private:

  CovStream(CovStream const &r);            // no can copy big fella ;->
  CovStream &operator=(CovStream const &r);

};


#endif

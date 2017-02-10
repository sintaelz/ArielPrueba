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


#include <bomb.h>
#include <stdlib.h>
#include <stdio.h>

void bomb(char const *msg)
{
  fprintf(stderr, "%s", msg);
  fflush(stderr);
  exit(2);
}

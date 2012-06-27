/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

/** Add this to get the @ref vf_sqlite external module.

    @file vf_sqlite.c
    @ingroup vf_sqlite external
*/

#include "AppConfig.h"

// Prevents sqlite.h from being included, since it screws up the .c
#define VF_SQLITE_PRIVATE_INTERFACE

#include "vf_sqlite.h"

#if ! (VF_USE_NATIVE_SQLITE && VF_HAVE_NATIVE_SQLITE)

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4127) /* conditional expression is constant */
#pragma warning (disable: 4232) /* nonstandard extension used: dllimport address */
#pragma warning (disable: 4244) /* conversion from 'int': possible loss of data */
#pragma warning (disable: 4701) /* potentially uninitialized variable */
#pragma warning (disable: 4706) /* assignment within conditional expression */
#endif

/* When compiled with SQLITE_THREADSAFE=2, SQLite can be used in a
   multithreaded program so long as no two threads attempt to use the
   same database connection at the same time.
*/

#define SQLITE_THREADSAFE 2

#include "sqlite/sqlite3.c"
#include "sqlite/sqlite3async.c"

#if JUCE_MSVC
#pragma warning (pop)
#endif

#endif

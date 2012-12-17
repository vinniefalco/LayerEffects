/*============================================================================*/
/*
  VFLib: https://github.com/vinniefalco/VFLib

  Copyright (C) 2008 by Vinnie Falco <vinnie.falco@gmail.com>

  This library contains portions of other open source products covered by
  separate licenses. Please see the corresponding source files for specific
  terms.
  
  VFLib is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
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

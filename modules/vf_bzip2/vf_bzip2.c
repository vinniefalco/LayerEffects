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

/** Add this to get the @ref vf_bzip2 external module.

    @file vf_bzip2.c
    @ingroup vf_bzip2 external
*/

#include "AppConfig.h"

// This screws up bZip and UInt32
//#include "modules/juce_core/system/juce_TargetPlatform.h"

#if _MSC_VER
#pragma push_macro("_CRT_SECURE_NO_WARNINGS")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma warning (push)
#pragma warning (disable: 4100) /* unreferenced formal parameter */
#pragma warning (disable: 4127) /* conditional expression is constant */
#pragma warning (disable: 4244) /* conversion, possible loss of data */
#pragma warning (disable: 4701) /* potentially uninitialized variable */
#pragma warning (disable: 4996) /* deprecated POSIX name */
#endif

#include "bzip2/blocksort.c"
#include "bzip2/bzlib.c"
#include "bzip2/compress.c"
#include "bzip2/crctable.c"
#include "bzip2/decompress.c"
#include "bzip2/huffman.c"
#include "bzip2/randtable.c"

#if _MSC_VER
#pragma warning (pop)
#pragma pop_macro("_CRT_SECURE_NO_WARNINGS")
#endif

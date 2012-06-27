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

#ifndef VF_APPCONFIGTEMPLATE_VFHEADER
#define VF_APPCONFIGTEMPLATE_VFHEADER

/*============================================================================*/
/**     
  Additional configuration options.

  Append these additional conditional compilation directives to your already
  existing AppConfig.h to customize the available compilations options.

  @note AppConfig.h must be included before any VFLib or JUCE headers.

  @file AppConfig.h
  @ingroup vf_core
*/

/** Activate features that use Boost.

    Your project will need to be configured to find the Boost includes
    and libraries.
*/
#ifndef VF_USE_BOOST
#define VF_USE_BOOST 0
#endif

/** Activate features that use bZip2.

    Your project will require the @ref vf_bzip2 external module.
*/
#ifndef VF_USE_BZIP2
#define VF_USE_BZIP2 1
#endif

/** Activate features that use FreeType.

    Your project will require the @ref vf_freetype external module.
*/
#ifndef VF_USE_FREETYPE
#define VF_USE_FREETYPE 1
#endif

/** Use native FreeType on platforms where it is available.
*/
#ifndef VF_USE_NATIVE_FREETYPE
#define VF_USE_NATIVE_FREETYPE 0
#endif

/** Use native sqlite on platforms where it is available.
*/
#ifndef VF_USE_NATIVE_SQLITE
#define VF_USE_NATIVE_SQLITE 1
#endif

/** Use custom leak checking code.
*/
#ifndef VF_USE_LEAKCHECKED
#define VF_USE_LEAKCHECKED 1
#endif

/*============================================================================*/

// Ignore this
#define JUCE_CHECK_MEMORY_LEAKS 1

#endif

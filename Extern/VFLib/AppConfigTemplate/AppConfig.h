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

#ifndef VF_APPCONFIGTEMPLATE_VFHEADER
#define VF_APPCONFIGTEMPLATE_VFHEADER

#define JUCE_MODULE_AVAILABLE_juce_core 1

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

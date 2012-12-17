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

/** Add this to get the @ref vf_core module.

    @file vf_core.cpp
    @ingroup vf_core
*/

#include "AppConfig.h"

#include "vf_core.h"

#include "modules/juce_gui_basics/juce_gui_basics.h"

#if JUCE_MSVC && _DEBUG
#include <crtdbg.h>
#endif

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#pragma warning (disable: 4355) // 'this' used in base member
#endif

namespace vf
{

#include "diagnostic/vf_CatchAny.cpp"
#include "diagnostic/vf_Debug.cpp"
#include "diagnostic/vf_Error.cpp"
#include "diagnostic/vf_FPUFlags.cpp"
#include "diagnostic/vf_LeakChecked.cpp"

#include "events/vf_OncePerSecond.cpp"
#include "events/vf_PerformedAtExit.cpp"

#include "math/vf_MurmurHash.cpp"

#include "threads/vf_InterruptibleThread.cpp"
#include "threads/vf_Semaphore.cpp"

#if JUCE_WINDOWS
#include "native/vf_win32_FPUFlags.cpp"
#include "native/vf_win32_Threads.cpp"

#else
#include "native/vf_posix_FPUFlags.cpp"
#include "native/vf_posix_Threads.cpp"

#endif

}

#if JUCE_MSVC
#pragma warning (pop)
#endif

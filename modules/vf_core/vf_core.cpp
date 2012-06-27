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

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

/** Add this to get the @ref vf_concurrent module.

    @file vf_concurrent.cpp
    @ingroup vf_concurrent
*/

#include "AppConfig.h"

#include "vf_concurrent.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#endif

namespace vf
{
#if VF_USE_BOOST
#include "memory/vf_FifoFreeStoreWithTLS.cpp"
#else
#include "memory/vf_FifoFreeStoreWithoutTLS.cpp"
#endif
#include "memory/vf_GlobalPagedFreeStore.cpp"
#include "memory/vf_PagedFreeStore.cpp"

#include "threads/vf_CallQueue.cpp"
#include "threads/vf_ConcurrentObject.cpp"
#include "threads/vf_Listeners.cpp"
#include "threads/vf_ManualCallQueue.cpp"
#include "threads/vf_MessageThread.cpp"
#include "threads/vf_ParallelFor.cpp"
#include "threads/vf_ReadWriteMutex.cpp"
#include "threads/vf_ThreadGroup.cpp"
#include "threads/vf_ThreadWithCallQueue.cpp"

#include "threads/vf_GuiCallQueue.cpp"
}

#if JUCE_MSVC
#pragma warning (pop)
#endif

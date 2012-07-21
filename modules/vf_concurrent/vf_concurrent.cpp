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

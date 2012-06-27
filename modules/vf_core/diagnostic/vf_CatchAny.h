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

#ifndef VF_CATCHANY_VFHEADER
#define VF_CATCHANY_VFHEADER

#include "../functor/vf_Function.h"

/**
  Exception catcher.

  Executes the function and catches any exception.
  In addition to C++ exceptions, this will also catch
  any platform-specific exceptions. For example, SEH
  (Structured Exception Handling) on Windows, or POSIX
  signals if they are available.
    
  If returnFromException is false then a framework
  specific unhandled exception handler will be called.
  Otherwise, this function will return true if it
  catches something or else false.
    
  The return value approach is useful for detecting
  when outside code fails (for example, a VST plugin),
  and disabling its future use for example.
    
  @todo Remove dependence on the JUCEApplication object and remove juce_gui_basics.h from vf_core.cpp

  @ingroup vf_core
*/
extern bool CatchAny (Function <void (void)> f,
                      bool returnFromException = false);

#endif

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

#ifndef VF_DEBUG_VFHEADER
#define VF_DEBUG_VFHEADER

// Auxiliary outines for debugging

namespace Debug
{

// Returns true if a debugger is attached, for any build.
extern bool isDebuggerAttached ();

// Breaks to the debugger if a debugger is attached.
extern void breakPoint ();

// VF: IS THIS REALLY THE RIGHT PLACE FOR THESE??

// Return only the filename portion of sourceFileName
// This hides the programmer's directory structure from end-users.
const String getFileNameFromPath (const char *sourceFileName);

// Convert a String that may contain double quotes and newlines
// into a String with double quotes escaped as \" and each
// line as a separate quoted command line argument.
String stringToCommandLine (const String& s);

// Convert a quoted and escaped command line back into a String
// that can contain newlines and double quotes.
String commandLineToString (const String& commandLine);

extern void setHeapAlwaysCheck (bool bAlwaysCheck);
extern void setHeapDelayedFree (bool bDelayedFree);
extern void setHeapReportLeaks (bool bReportLeaks);
extern void checkHeap ();

}

#endif

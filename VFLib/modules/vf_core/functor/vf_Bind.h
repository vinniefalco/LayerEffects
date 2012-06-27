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

#ifndef VF_BIND_VFHEADER
#define VF_BIND_VFHEADER

/* Brings functional support into our namespace, based on environment.
*/
#if JUCE_MSVC
  // Visual Studio has these in std.
  using std::ref;
  using std::bind;
  using std::function;
  using std::placeholders::_1;
  using std::placeholders::_2;

#elif JUCE_IOS
  #if VF_USE_BOOST
    /* If boost is activated, use it. This works
       around a bug with the iOS implementation of bind.
    */
    using boost::ref
    using boost::bind;
    using boost::function;
    using ::_1;
    using ::_2;
  #else
    /* Xcode puts these in std::tr1 */
    using std::tr1::ref;
    using std::tr1::bind;
    using std::tr1::function;
    using std::tr1::placeholders::_1;
    using std::tr1::placeholders::_2;
  #endif

#elif JUCE_MAC
  using std::ref;
  using std::bind;
  using std::function;
  using std::placeholders::_1;
  using std::placeholders::_2;

#else
  #error Unknown platform in vf_Bind.h

#endif

#endif

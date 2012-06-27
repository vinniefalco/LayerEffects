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

/** Add this to get the @ref vf_audio module.

    @file vf_audio.cpp
    @ingroup vf_audio
*/

#include "AppConfig.h"

#include "vf_audio.h"

#if JUCE_MSVC
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parmaeter
#endif

namespace vf
{

#include "buffers/vf_AudioBufferPool.cpp"

#include "midi/vf_MidiDevices.cpp"
#include "midi/vf_MidiInput.cpp"

#include "sources/vf_NoiseAudioSource.cpp"
#include "sources/vf_SeekingAudioSource.cpp"
#include "sources/vf_SeekingSampleSource.cpp"

}

#if JUCE_MSVC
#pragma warning (pop)
#endif

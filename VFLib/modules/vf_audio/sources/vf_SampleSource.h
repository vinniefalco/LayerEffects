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

#ifndef VF_SAMPLESOURCE_VFHEADER
#define VF_SAMPLESOURCE_VFHEADER

//==============================================================================
/**
  Abstract source of audio samples.

  This interface is used to retrieve sequentual raw audio samples from an
  abstract source. It is intended as a facade for @ref AudioSource, with these
  features:

  - No thread safety; the caller is responsible for all synchronization.

  - The preparation state feature is removed (along with its methods).

  @ingroup vf_audio
*/
class SampleSource
{
public:
  virtual ~SampleSource () { }

  /**
    Read the next block of samples.
  */
  virtual void getNextAudioBlock (AudioSourceChannelInfo const& bufferToFill) = 0;
};

#endif

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

#ifndef VF_SEEKINGSAMPLESOURCE_VFHEADER
#define VF_SEEKINGSAMPLESOURCE_VFHEADER

//==============================================================================
/**
  Abstract positionable source of audio samples.

  This interface adds positionable capabilities to a SampleSource. It is
  intended as a facade for @ref PositionableAudioSource, with these features:

  - No thread safety; the caller is responsible for all synchronization.

  - Forward and reverse playback is supported.

  - The looping and total length features have been removed.

  @ingroup vf_audio
*/
class SeekingSampleSource : public SampleSource
{
public:
  enum Direction
  {
    forward,
    reverse
  };

  /**
    Get the direction for the retrieval of samples.
  */
  virtual Direction getNextReadDirection () const = 0;

  /**
    Set the direction for the retrieval of samples.
  */

  virtual void setNextReadDirection (Direction direction) = 0;

  /**
    Get the position of the next returned sample.

    @see setNextReadPosition
  */
  virtual int64 getNextReadPosition () const = 0;

  /**
    Move the read position.

    Calling this indicates that the next call to SampleSource::getNextAudioBlock()
    should return samples from this position.
  */
  virtual void setNextReadPosition (int64 newPosition) = 0;

public:
  //============================================================================
  /**
    Adapter to appear as a @ref PositionableAudioSource.

    @ingroup vf_audio
  */
  class PositionableAdapter : public PositionableAudioSource, Uncopyable
  {
  public:
    PositionableAdapter (SeekingSampleSource* source, bool takeOwnership);

    void setNextReadPosition (int64 newPosition);

    int64 getNextReadPosition() const;

    int64 getTotalLength() const;

    bool isLooping() const;

    void setLooping (bool shouldLoop);

    void prepareToPlay (int samplesPerBlockExpected,
                        double sampleRate);

    void releaseResources();

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

  private:
    OptionalScopedPointer <SeekingSampleSource> m_source;
  };
};

#endif

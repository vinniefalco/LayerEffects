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

#ifndef VF_SEEKINGAUDIOSOURCE_VFHEADER
#define VF_SEEKINGAUDIOSOURCE_VFHEADER

//==============================================================================
/**
  Facade for @ref PositionableAudioSource.

  This Facade provides an alternative interface to @ref PositionableAudioSource
  with the following features:

  - No thread safety; the caller is responsible for all synchronization.

  - The looping and total length features have been removed.

  @ingroup vf_audio
*/
class SeekingAudioSource : public SeekingSampleSource
{
public:
  /** Tells the source to prepare for playing.
  */
  virtual void prepareToPlay (int samplesPerBlockExpected,
                              double sampleRate) = 0;

  /** Allows the source to release anything it no longer needs after playback has stopped.
  */
  virtual void releaseResources() = 0;

public:
  //============================================================================
  /**
    Adapter to appear as a @ref PositionableAudioSource.

    @ingroup vf_audio
  */
  class PositionableAdapter : public PositionableAudioSource, Uncopyable
  {
  public:
    PositionableAdapter (SeekingAudioSource* source,
                         bool takeOwnership,
                         int64 totalLength);

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
    OptionalScopedPointer <SeekingAudioSource> m_source;
    int64 const m_totalLength;
    bool m_shouldLoop;
  };

public:
  class Adapter;
};

//==============================================================================
/**
  Adapter to wrap a @ref PositionableAudioSource.

  @ingroup vf_audio
*/
class SeekingAudioSource::Adapter : public SeekingAudioSource
{
public:
  Adapter (PositionableAudioSource* source, bool takeOwnership);

  void setNextReadPosition (int64 newPosition);

  int64 getNextReadPosition() const;

  void prepareToPlay (int samplesPerBlockExpected,
                      double sampleRate);

  void releaseResources();

  void getNextAudioBlock (AudioSourceChannelInfo const& bufferToFill);

private:
  OptionalScopedPointer <PositionableAudioSource> m_source;
};

#endif

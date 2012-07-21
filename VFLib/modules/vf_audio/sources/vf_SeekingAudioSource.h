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

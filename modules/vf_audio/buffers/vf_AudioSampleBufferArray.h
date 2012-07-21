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

#ifndef VF_AUDIOSAMPLEBUFFERARRAY_VFHEADER
#define VF_AUDIOSAMPLEBUFFERARRAY_VFHEADER

/*============================================================================*/
/** 
  An array of movable pointers to existing audio buffers.

  This simple class wraps an already existing array of pointers to
  multi-channel audio data. Provided functions can move the pointers back and
  forth as a group, making certain forms of code that manipulate audio buffers
  more concise. Type conversions to and from AudioSampleBuffer allow seamless,
  intuitive usage.

  All constructors and assignments leave the array pointing to already
  existing memory, none of these functions create new buffers. All arrays will
  point to the same sample data or storage as the objects they were
  constructed from.

  @tparam Channels The number of channels in the array of pointers,
                    default to 2 (stereo).

  @ingroup vf_audio
*/
template <int Channels = 2>
class AudioSampleBufferArray
{
public:
  // If AudioSampleBuffer ever becomes a template, we can
  // move the Sample typedef into the template parameters.
  typedef float Sample;

  /** @details Construct an array with no samples. */
  AudioSampleBufferArray ()
    : m_numSamples (0)
  {
  }

/**
  @param numSamples      The number of samples in the resulting array. This
                         may be less than or equal to the actual amount of
                         space in the memory pointed to by arrayOfChannels.

  @param arrayOfChannels The array of pointers to existing memory.
*/
  AudioSampleBufferArray (int numSamples, Sample* const* arrayOfChannels)
  {
    setFrom (numSamples, arrayOfChannels);
  }

  /** @param other The AudioSampleBufferArray to copy from.
  */
  AudioSampleBufferArray (const AudioSampleBufferArray& other)
  {
    setFrom (other);
  }

/**
  @param buffer      The AudioSampleBuffer to point to.
      
  @param startSample Zero based index of the first sample to use.
      
  @param numSamples  The number of samples in the desired range.
                     This must be less than or equal to the actual
                     amount of space in the memory pointed to by
                     buffer, less startingSampleIndex.
*/
  AudioSampleBufferArray (const AudioSampleBuffer& buffer,
                          int startSample = 0,
                          int numSamples = -1)
  {
    setFrom (buffer, startSample, numSamples);
  }

  /** @param bufferToFill The AudioSourceChannelInfo to point to. */
  AudioSampleBufferArray (const AudioSourceChannelInfo& bufferToFill)
  {
    setFrom (*bufferToFill.buffer,
             bufferToFill.startSample,
             bufferToFill.numSamples);
  }

/**
  @param buffer The buffer to point to.
  
  @return A reference to the array.
*/
  AudioSampleBufferArray& operator= (const AudioSampleBuffer& buffer)
  {
    setFrom (buffer);
    return *this;
  }

/**
  @param bufferToFill The portion of an AudioSampleBuffer to point to.

  @return A reference to the array.
*/
  AudioSampleBufferArray& operator= (const AudioSourceChannelInfo& bufferToFill)
  {
    setFrom (bufferToFill);
    return *this;
  }

/**
  @param other The other AudioSampleBufferArray to point to.
  
  @return A reference to the array.
*/
  AudioSampleBufferArray& operator= (const AudioSampleBufferArray& other)
  {
    setFrom (other);
    return *this;
  }

/**
  Manually assign a range of samples from a set of pointers.
  
  @param numSamples The number of samples in the desired range.
      
  @param channels The array of pointers to sample data.
*/
  void setFrom (int numSamples, Sample* const* channels)
  {
    m_numSamples = numSamples;
    for (int i=0; i<Channels; i++)
      m_channels[i]=channels[i];
  }

  /** @param other The AudioSampleBufferArray to point to.
  */
  void setFrom (const AudioSampleBufferArray& other)
  {
    m_numSamples = other.m_numSamples;
    for (int i=0; i<Channels; i++)
      m_channels[i] = other.m_channels[i];
  }

/**
  @param buffer The AudioSampleBuffer containing the desired channel buffers.
      
  @param startSample Zero based index of the first sample to use.

  @param numSamples  The number of samples in the desired range.
                     This must be less than or equal to the actual
                     amount of space in the memory pointed to by
                     buffer, less startingSampleIndex.
*/
  void setFrom (AudioSampleBuffer const& buffer,
                int startSample = 0,
                int numSamples = -1)
  {
    jassert (buffer.getNumChannels() == Channels);
    jassert (startSample >= 0 && startSample <= buffer.getNumSamples());
    if (numSamples == -1)
      numSamples = buffer.getNumSamples() - startSample;
    jassert (numSamples <= buffer.getNumSamples() - startSample);
    m_numSamples = numSamples;
    for (int i = 0; i < Channels; ++i)
      m_channels[i] = buffer.getArrayOfChannels()[i] + startSample;
  }

  /** @return A const array of pointers to the channel data. */
  operator Sample* const* () const
  {
    return m_channels;
  }

  /** @return An AudioSampleBuffer pointing to the channel data. */
  operator AudioSampleBuffer()
  {
    return AudioSampleBuffer (m_channels, Channels, m_numSamples);
  }

  /** @return A const AudioSampleBuffer pointing to the channel data. */
  operator const AudioSampleBuffer() const
  {
    return AudioSampleBuffer (m_channels, Channels, m_numSamples);
  }

/**
  Get a raw channel pointer.

  @param index The zero based channel number. This must be less than Channels.

  @return A pointer to the channel data.
*/
  Sample*& operator[] (int index)
  {
    jassert (index >= 0 && index < Channels);
    return m_channels[index];
  }

  const Sample* operator[] (int index) const
  {
    jassert (index >= 0 && index < Channels);
    return m_channels[index];
  }

/**
  Advance all channels by the specified number of samples.

  Advancing by more than the number of samples remaining is undefined.
  After the pointers are moved forward, the number of samples remaining
  is adjusted downwards.

  @param numSamples The number of samples to advance by.

  @return An array that points to the new range of samples.
*/
  AudioSampleBufferArray operator+ (int numSamples)
  {
    jassert (numSamples <= m_numSamples);
    Sample* channels[Channels];
    for (int i=0; i<Channels; i++)
      channels[i] = m_channels[i] + numSamples;
    return AudioSampleBufferArray (m_numSamples - numSamples, channels);
  }

  AudioSampleBufferArray& operator+= (int numSamples)
  {
    *this = *this + numSamples;
    return *this;
  }

/**
  Rewind all channels by the specified number of samples.

  Rewinding to before the start of the original memory pointers is
  undefined. After the pointers are moved back, the number of samples
  remaining is adjusted upwards.

  @param numSamples The number of samples to rewind by.

  @return An array representing the new range of samples.
*/
  AudioSampleBufferArray operator- (int numSamples)
  {
    return operator+ (-numSamples);
  }

  AudioSampleBufferArray& operator-= (int numSamples)
  {
    return operator+= (-numSamples);
  }

  /** Determine if there are samples remaining in the array.

      @return true if there are no more samples in the data pointed
                   to by the array.
  */
  bool isEmpty () const
  {
    return m_numSamples <= 0;
  }

  /** Determine the number of samples remaining in the array.

      @return The number of samples remaining. This will decrease or increase
              as the array is incremented or decremented respectively.
  */
  int getNumSamples () const
  {
    return m_numSamples;
  }

  /** Retrieve the raw array of channel pointers.

      @return An array of pointers to sample data.
  */
  Sample* const* getArrayOfChannels() const
  {
    return m_channels;
  }

private:
  int m_numSamples;
  Sample* m_channels[Channels];
};

/** An AudioSampleBufferArray with 2 channels.

    @ingroup vf_audio
*/
typedef AudioSampleBufferArray <2> StereoSampleBuffer;

#endif

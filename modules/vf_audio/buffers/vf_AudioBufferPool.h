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

#ifndef VF_AUDIOBUFFERPOOL_VFHEADER
#define VF_AUDIOBUFFERPOOL_VFHEADER

/*============================================================================*/
/**
  Temporary audio buffers.

  This container provides a pool of audio buffers that grow to match the
  working set requirements based on actual usage. Since the buffers never
  shrink or get deleted, there are almost no calls to the system to allocate
  or free memory.

  This is ideal for AudioIODeviceCallback implementations which process
  audio buffers and require temporary storage for intermediate calculations.
  The usage style is to request a temporary buffer of the desired size,
  perform calculations, and then release the buffer when finished.

  Buffers are intelligently resized and recycled to consume the smallest
  amount of memory possible based on the usage pattern, with no effort
  required by the programmer.

  To use the container, create an instance of the AudioBufferPoolType
  template, and specify the type of lock to use for synchronization. By
  default, a CriticalSection is used but if you aren't sharing the pool
  between threads, you can use a DummyCriticalSection instead.

  Here's an example:

  @code

  AudioBufferPoolType <DummyCriticalSection> pool;

  // Request a stereo buffer with room for 1024 samples.
  AudioBufferPool::Buffer* buffer = pool.requestBuffer (2, 1024);

  // (Process buffer)

  // Release the buffer to be re-used later.
  pool.releaseBuffer (buffer);

  @endcode

  Since Buffer is derived from AudioSampleBuffer, it can be used anywhere
  an AudioSampleBuffer is expected. This example requests a temporary buffer
  and stores it in an AudioSourceChannelInfo:

  @code

  // Request a stereo buffer with room for 1024 samples.
  AudioBufferPool::Buffer* buffer = pool.requestBuffer (2, 1024);

  // Fill out the AudioSourceChannelInfo structure with the buffer
  AudioSourceChannelInfo info;
  info.buffer = buffer;         // allowed, since AudioBufferPool::Buffer *
                                // is-a AudioSampleBuffer *
  info.startSample = 0;
  info.numSamples = 1024;

  // Clear out the range of samples
  info.clearActiveBufferRegion ();

  @endcode

  @see AudioBufferPoolType, ScopedAudioSampleBuffer

  @ingroup vf_audio
*/
class AudioBufferPool
{
public:
  /**
    Size tracking for AudioSampleBuffer.

    This provides the getNumSamplesAllocated () function necessary for the
    implementation of AudioBufferPool. It otherwise acts like a normal
    AudioSampleBuffer.

    @ingroup vf_audio
  */
  class Buffer : public AudioSampleBuffer
  {
  public:
    Buffer (int numChannels, int numSamples);

    void resize (int newNumChannels, int newNumSamples);

    /** @return The absolute number of samples available in the storage area,
                regardless of the number of channels.
    */
    int getNumSamplesAllocated () const;

  private:
    int m_samplesAllocated;
  };

  AudioBufferPool ();

  /** @details

	  All allocated buffers are freed. Any previously requested buffers must
      already be released.
  */
  ~AudioBufferPool ();

  /** Request a temporary buffer.

      The pool returns a buffer with the specified number of channels and
      enough room for at least numSamples. The caller owns the buffer until it
      is released with a matching call to releaseBuffer().

      @param numChannels  The number of channels requested.

      @param numSamples   The number of samples per channel requested.

      @return             The resulting buffer.
  */
  virtual Buffer* requestBuffer (int numChannels, int numSamples) = 0;

  /** Releases a previously requested buffer back into the pool.

      @param buffer The buffer to release. This must have been provided by an
                    earlier call to requestBuffer()
  */
  virtual void releaseBuffer (Buffer* buffer) = 0;

protected:
  Buffer* requestBufferInternal (int numChannels, int numSamples);
  void releaseBufferInternal (Buffer* buffer);

private:
  Array <Buffer*> m_buffers;
};

/*============================================================================*/
/**
    Template for AudioBufferPool with a specified lock type.

    This provides an instance of AudioBufferPool using the specified type as
    the lock. The default is to use a CriticalSection. Alternatively, a
    DummyCriticalSection may be used when the caller is responsible for
    synchronization.

    @ingroup vf_audio
*/
template <class TypeOfCriticalSectionToUse = CriticalSection>
class AudioBufferPoolType
  : public AudioBufferPool
  , public LeakChecked <AudioBufferPoolType <TypeOfCriticalSectionToUse> >
{
public:
  Buffer* requestBuffer (int numChannels, int numSamples)
  {
    typename TypeOfCriticalSectionToUse::ScopedLockType lock (m_mutex);

    return requestBufferInternal (numChannels, numSamples);
  }

  void releaseBuffer (Buffer* buffer)
  {
    typename TypeOfCriticalSectionToUse::ScopedLockType lock (m_mutex);

    releaseBufferInternal (buffer);
  }    

private:
  TypeOfCriticalSectionToUse m_mutex;
};

#endif

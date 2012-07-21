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

#ifndef VF_SCOPEDAUDIOSAMPLEBUFFER_VFHEADER
#define VF_SCOPEDAUDIOSAMPLEBUFFER_VFHEADER

/*============================================================================*/
/**
    A temporary audio buffer with scoped lifetime.

    This utility class allows scoped lifetime management for acquiring temporary
    audio buffers from the AudioBufferPool. It is easy to use:

    @code

    AudioBufferPoolType <CriticalSection> pool;

    // Request a stereo buffer with room for 1024 samples.
    ScopedAudioSampleBuffer buffer (pool, 2, 1024);

    // 'buffer' is released when it goes out of scope.

    @endcode

    ScopedAudioSampleBuffer is freely convertible to AudioSampleBuffer* so it
    can be used anywhere a pointer to AudioSampleBuffer is expected. The
    dereference and pointer to member operators are similarly overloaded to
    support transparent usage of the underlying AudioSampleBuffer:

    @code

    AudioBufferPoolType <CriticalSection> pool;

    ScopedAudioSampleBuffer buffer (pool, 2, 1024);

    // Call a member of AudioSampleBuffer
    buffer->clear ();

    @endcode

    Note that changing the size of a buffer is undefined.

    @ingroup vf_audio
*/
class ScopedAudioSampleBuffer
  // NO IDEA why the leak checking fails
  // : LeakChecked <ScopedAudioSampleBuffer>, Uncopyable
{
public:
  /** Create a ScopedAudioSampleBuffer from a pool.

      @param pool         The pool to acquire a buffer from.

      @param numChannels  The number of channels requested.

      @param numSamples   The number of samples per channel requested.
  */
  ScopedAudioSampleBuffer (AudioBufferPool& pool,
	                       int numChannels,
	                       int numSamples)
	: m_pool (pool)
	, m_buffer (pool.requestBuffer (numChannels, numSamples))
  {
  }

  /** Destroy the ScopedAudioSampleBuffer, releasing the buffer */
  ~ScopedAudioSampleBuffer ()
  {
	m_pool.releaseBuffer (m_buffer);
  }

  /** @return A pointer to AudioSampleBuffer.

      @todo Fix broken documentation hyperlink caused by juce scope.
  */
  AudioSampleBuffer* operator-> ()
  {
	return getBuffer();
  }

  /** @return A reference to AudioSampleBuffer.
  */
  AudioSampleBuffer& operator* ()
  {
	return *getBuffer();
  }

  /** @return A pointer to AudioSampleBuffer. */
  operator AudioSampleBuffer* ()
  {
	return getBuffer();
  }

  /** @return A pointer to AudioSampleBuffer. */
  AudioSampleBuffer* getBuffer ()
  {
	return m_buffer;
  }

private:
  AudioBufferPool& m_pool;
  AudioBufferPool::Buffer* const m_buffer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopedAudioSampleBuffer);
};

#endif

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

AudioBufferPool::Buffer::Buffer (int numChannels,
                                 int numSamples)
  : AudioSampleBuffer (numChannels, numSamples)
  , m_samplesAllocated (numChannels * numSamples)
{
}

void AudioBufferPool::Buffer::resize (int newNumChannels, int newNumSamples)
{
  int samplesAllocated = newNumChannels * newNumSamples;

  if (m_samplesAllocated < samplesAllocated)
    m_samplesAllocated = samplesAllocated;

  setSize (newNumChannels, newNumSamples, false, false, true);
}

int AudioBufferPool::Buffer::getNumSamplesAllocated () const
{
  return m_samplesAllocated;
}

/*============================================================================*/

AudioBufferPool::AudioBufferPool ()
{
  m_buffers.ensureStorageAllocated (10);
}

AudioBufferPool::~AudioBufferPool ()
{
  for (int i = 0; i < m_buffers.size(); ++i)
	delete m_buffers[i];
}    

AudioBufferPool::Buffer* AudioBufferPool::requestBufferInternal (int numChannels, int numSamples)
{
  Buffer* buffer = 0;
  int samplesNeeded = numChannels * numSamples;

  int index = -1;

  for (int i = 0; i < m_buffers.size(); ++i)
  {
	Buffer* cur = m_buffers[i];

	if (!buffer)
	{
	  buffer = cur;
	  index = i;
	}
	else
	{
	  int numSamplesAvailable = cur->getNumSamplesAllocated();

	  // Use the smallest buffer which is equal or bigger than what
	  // we need. If no buffer is large enough, then we will use the
	  // largest available and increase it, to minimize memory usage.
	  if ( (numSamplesAvailable >= samplesNeeded &&
		numSamplesAvailable < buffer->getNumSamplesAllocated()) ||
		(numSamplesAvailable < samplesNeeded &&
		numSamplesAvailable > buffer->getNumSamplesAllocated()))
	  {
		buffer = cur;
		index = i;
	  }
	}
  }

  if (buffer)
	m_buffers.remove (index);

  if (buffer)
	buffer->resize (numChannels, numSamples);
  else
	buffer = new Buffer (numChannels, numSamples);

  return buffer;
}

void AudioBufferPool::releaseBufferInternal (Buffer* buffer)
{
  if (buffer != nullptr)
	m_buffers.add (buffer);
}

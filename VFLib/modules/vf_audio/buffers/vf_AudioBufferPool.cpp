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

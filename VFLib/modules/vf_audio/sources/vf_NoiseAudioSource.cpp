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

NoiseAudioSource::NoiseAudioSource (bool pink)
  : m_pink (pink)
  , m_random (Time::currentTimeMillis())
{
}

NoiseAudioSource::~NoiseAudioSource ()
{
}

void NoiseAudioSource::prepareToPlay (int samplesPerBlockExpected,
                                      double sampleRate)
{
}

void NoiseAudioSource::releaseResources()
{
}

void NoiseAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
  if (m_pink)
  {
    for (int i = 0; i < bufferToFill.buffer->getNumChannels(); ++i)
      pink_noise (bufferToFill.numSamples,
                  bufferToFill.buffer->getArrayOfChannels()[i] + bufferToFill.startSample);
  }
  else
  {
    for (int i = 0; i < bufferToFill.buffer->getNumChannels(); ++i)
      white_noise (bufferToFill.numSamples,
                   bufferToFill.buffer->getArrayOfChannels()[i] + bufferToFill.startSample);
  }
}

void NoiseAudioSource::white_noise (int numSamples, float* dest)
{
  while (--numSamples >= 0)
  {
    *dest++ = (m_random.nextFloat()*2)-1;
  }
}

void NoiseAudioSource::pink_noise (int numSamples, float* dest)
{
  while (--numSamples >= 0)
  {
    *dest++ = m_filter.process ((m_random.nextFloat()*2)-1);
  }
}

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

SeekingAudioSource::PositionableAdapter::PositionableAdapter (
  SeekingAudioSource* source,
  bool takeOwnership,
  int64 totalLength)
  : m_source (source, takeOwnership)
  , m_totalLength (totalLength)
  , m_shouldLoop (false)
{
}

void SeekingAudioSource::PositionableAdapter::setNextReadPosition (int64 newPosition)
{
  m_source->setNextReadPosition (newPosition);
}

int64 SeekingAudioSource::PositionableAdapter::getNextReadPosition () const
{
  return m_source->getNextReadPosition ();
}

int64 SeekingAudioSource::PositionableAdapter::getTotalLength () const
{
  return m_totalLength;
}

bool SeekingAudioSource::PositionableAdapter::isLooping () const
{
  return m_shouldLoop;
}

void SeekingAudioSource::PositionableAdapter::setLooping (bool shouldLoop)
{
  m_shouldLoop = shouldLoop;
}

void SeekingAudioSource::PositionableAdapter::prepareToPlay (
  int samplesPerBlockExpected, double sampleRate)
{
  m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void SeekingAudioSource::PositionableAdapter::releaseResources ()
{
  m_source->releaseResources ();
}

void SeekingAudioSource::PositionableAdapter::getNextAudioBlock (
  const AudioSourceChannelInfo& bufferToFill)
{
  if (m_shouldLoop)
  {
    int64 nextReadPosition = m_source->getNextReadPosition ();

    if (nextReadPosition < m_totalLength)
    {
      int outputPosition = 0; // relative to bufferToFill

      while (outputPosition < bufferToFill.numSamples)
      {
        int amountToProcess = bufferToFill.numSamples - outputPosition;
        int64 remainingInputSamples = m_totalLength - nextReadPosition;

        // inequality is for the edge case, to rewind the read position.
        if (amountToProcess >= remainingInputSamples)
        {
          // copy remaining input till end
          amountToProcess = static_cast <int> (remainingInputSamples);
          m_source->getNextAudioBlock (AudioSourceChannelInfo (
            bufferToFill.buffer,
            bufferToFill.startSample + outputPosition,
            amountToProcess));

          // rewind
          nextReadPosition = 0;
          m_source->setNextReadPosition (nextReadPosition);
        }
        else
        {
          m_source->getNextAudioBlock (AudioSourceChannelInfo (
            bufferToFill.buffer,
            bufferToFill.startSample + outputPosition,
            amountToProcess));
        }

        // advance
        outputPosition += amountToProcess;
      }
    }
    else
    {
      // already past the end
      m_source->getNextAudioBlock (bufferToFill);
    }
  }
  else
  {
    m_source->getNextAudioBlock (bufferToFill);
  }
}

//==============================================================================

SeekingAudioSource::Adapter::Adapter (
  PositionableAudioSource* source, bool takeOwnership)
  : m_source (source, takeOwnership)
{
}

void SeekingAudioSource::Adapter::setNextReadPosition (int64 newPosition)
{
  m_source->setNextReadPosition (newPosition);
}

int64 SeekingAudioSource::Adapter::getNextReadPosition () const
{
  return m_source->getNextReadPosition ();
}

void SeekingAudioSource::Adapter::prepareToPlay (
  int samplesPerBlockExpected, double sampleRate)
{
  m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void SeekingAudioSource::Adapter::releaseResources ()
{
  m_source->releaseResources ();
}

void SeekingAudioSource::Adapter::getNextAudioBlock (
  AudioSourceChannelInfo const& bufferToFill)
{
  m_source->getNextAudioBlock (bufferToFill);
}


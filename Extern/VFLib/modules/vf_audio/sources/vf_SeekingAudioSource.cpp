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

SeekingAudioSource::PositionableAudioSourceAdapter::PositionableAudioSourceAdapter (
  SeekingAudioSource* source,
  bool takeOwnership,
  int64 totalLength)
  : m_source (source, takeOwnership)
  , m_totalLength (totalLength)
  , m_shouldLoop (false)
{
}

void SeekingAudioSource::PositionableAudioSourceAdapter::setNextReadPosition (int64 newPosition)
{
  m_source->setNextReadPosition (newPosition);
}

int64 SeekingAudioSource::PositionableAudioSourceAdapter::getNextReadPosition () const
{
  return m_source->getNextReadPosition ();
}

int64 SeekingAudioSource::PositionableAudioSourceAdapter::getTotalLength () const
{
  return m_totalLength;
}

bool SeekingAudioSource::PositionableAudioSourceAdapter::isLooping () const
{
  return m_shouldLoop;
}

void SeekingAudioSource::PositionableAudioSourceAdapter::setLooping (bool shouldLoop)
{
  m_shouldLoop = shouldLoop;
}

void SeekingAudioSource::PositionableAudioSourceAdapter::prepareToPlay (
  int samplesPerBlockExpected, double sampleRate)
{
  m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void SeekingAudioSource::PositionableAudioSourceAdapter::releaseResources ()
{
  m_source->releaseResources ();
}

void SeekingAudioSource::PositionableAudioSourceAdapter::getNextAudioBlock (
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

SeekingAudioSource::SeekingAudioSourceAdapter::SeekingAudioSourceAdapter (
  PositionableAudioSource* source, bool takeOwnership)
  : m_source (source, takeOwnership)
{
}

void SeekingAudioSource::SeekingAudioSourceAdapter::setNextReadPosition (int64 newPosition)
{
  m_source->setNextReadPosition (newPosition);
}

int64 SeekingAudioSource::SeekingAudioSourceAdapter::getNextReadPosition () const
{
  return m_source->getNextReadPosition ();
}

void SeekingAudioSource::SeekingAudioSourceAdapter::prepareToPlay (
  int samplesPerBlockExpected, double sampleRate)
{
  m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void SeekingAudioSource::SeekingAudioSourceAdapter::releaseResources ()
{
  m_source->releaseResources ();
}

void SeekingAudioSource::SeekingAudioSourceAdapter::getNextAudioBlock (
  AudioSourceChannelInfo const& bufferToFill)
{
  m_source->getNextAudioBlock (bufferToFill);
}


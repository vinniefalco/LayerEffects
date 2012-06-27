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

SeekingSampleSource::PositionableAdapter::PositionableAdapter (
  SeekingSampleSource* source, bool takeOwnership)
  : m_source (source, takeOwnership)
{
}

void SeekingSampleSource::PositionableAdapter::setNextReadPosition (int64 newPosition)
{
  m_source->setNextReadPosition (newPosition);
}

int64 SeekingSampleSource::PositionableAdapter::getNextReadPosition () const
{
  return m_source->getNextReadPosition ();
}

int64 SeekingSampleSource::PositionableAdapter::getTotalLength () const
{
  // Unsupported
  jassertfalse;
  return 0;
}

bool SeekingSampleSource::PositionableAdapter::isLooping () const
{
  // Unsupported
  jassertfalse;
  return false;
}

void SeekingSampleSource::PositionableAdapter::setLooping (bool shouldLoop)
{
  // Unsupported
  jassertfalse;
}

void SeekingSampleSource::PositionableAdapter::prepareToPlay (
  int samplesPerBlockExpected, double sampleRate)
{
}

void SeekingSampleSource::PositionableAdapter::releaseResources ()
{
}

void SeekingSampleSource::PositionableAdapter::getNextAudioBlock (
  const AudioSourceChannelInfo& bufferToFill)
{
  m_source->getNextAudioBlock (bufferToFill);
}

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

namespace Pipe {

//******************************************************************************

MemOut::MemOut( void* buffer, size_t bufferBytes )
{
  m_buffer=static_cast<uint8*>(buffer);
  m_remain=bufferBytes;
}

//------------------------------------------------------------------------------

Error MemOut::Write( const void* src, size_t srcBytes )
{
  vf::Error error;

  if( m_remain>=srcBytes )
  {
    ::memcpy( m_buffer, src, srcBytes );
    m_buffer+=srcBytes;
    m_remain-=srcBytes;
  }
  else
  {
    error.fail( __FILE__, __LINE__, Error::fileNoSpace );
  }

  return error;
}

//------------------------------------------------------------------------------

uint8* MemOut::GetBuffer()
{
  return m_buffer;
}

//------------------------------------------------------------------------------

size_t MemOut::GetBytesRemaining()
{
  return m_remain;
}

//******************************************************************************

MemIn::MemIn( const void* buffer, size_t bufferBytes )
{
  m_buffer=static_cast<const uint8*>(buffer);
  m_remain=bufferBytes;
}

//------------------------------------------------------------------------------

Error MemIn::Read( void* dest, size_t destBytes )
{
  Error error;

  if( destBytes<=m_remain )
  {
    ::memcpy( dest, m_buffer, destBytes );

    m_buffer+=destBytes;
    m_remain-=destBytes;
  }
  else
  {
	error.fail (__FILE__, __LINE__, Error::noMoreData);
  }

  return error;
}

//------------------------------------------------------------------------------

const uint8* MemIn::GetBuffer()
{
  return m_buffer;
}

//------------------------------------------------------------------------------

size_t MemIn::GetBytesRemaining()
{
  return m_remain;
}

}

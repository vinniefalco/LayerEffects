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

#ifndef VF_PIPE_H
#define VF_PIPE_H

//
// JUCE DOES THIS ALREADY SO DONT USE THIS
//

namespace Pipe {

//--------------------------------------------------------------------------

class In : Uncopyable
{
public:
  virtual Error Read( void* dest, size_t destBytes )=0;

public:
  // read in native endianness

  template<typename Ty>
  Error ReadBlob( Ty* pValue )
  {
    return Read( pValue, sizeof(*pValue) );
  }
};

//--------------------------------------------------------------------------

class Out : Uncopyable
{
public:
  virtual Error Write( const void* src, size_t srcBytes )=0;

public:
  // write in native endianness

  template<typename Ty>
  Error WriteBlob( const Ty& value )
  {
    return Write( &value, sizeof(value) );
  }

};

//--------------------------------------------------------------------------

class MemOut : public Out
{
public:
  MemOut( void* buffer, size_t bufferBytes );

  virtual Error Write( const void* src, size_t srcBytes );

  uint8* 	GetBuffer();
  size_t	GetBytesRemaining();

private:
  uint8* 	m_buffer;
  size_t	m_remain;
};

//--------------------------------------------------------------------------

class MemIn : public In
{
public:
  MemIn( const void* buffer, size_t bufferBytes );

  virtual Error Read( void* dest, size_t destBytes );

  const uint8* GetBuffer();
  size_t	GetBytesRemaining();

private:
  const uint8* m_buffer;
  size_t	m_remain;
};

}

#endif

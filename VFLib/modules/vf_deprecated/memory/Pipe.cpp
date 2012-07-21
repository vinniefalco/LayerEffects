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

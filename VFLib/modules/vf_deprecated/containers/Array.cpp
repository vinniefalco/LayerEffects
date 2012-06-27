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

#include "../memory/Pipe.h"

// if not defined we simply Reset() the block storage,
// bypassing destructor calls and frees for objects
#ifndef NDEBUG
#define FULL_DELETE
#endif

ArrayStorage::ArrayStorage(
  size_t elemBytes,
  size_t blockBytes)
{
  vfassert( blockBytes>=sizeof(void*) );
  vfassert( elemBytes>0 );
  vfassert( elemBytes<blockBytes );

  m_elemBytes=elemBytes;
  m_blockBytes=blockBytes;
  m_blockElems=blockBytes/elemBytes;

  m_blocks=0;
  m_block=0;
  m_count=0;
}

//------------------------------------------------------------------------------

ArrayStorage::~ArrayStorage()
{
  if( m_block!=0 )
  {
    Index i;
    for( i=0; i<m_blocks; i++ )
    {
      free( m_block[i] );
    }

    free( m_block );
  }
}

//------------------------------------------------------------------------------

ArrayStorage::Index ArrayStorage::Count( void ) const
{
  return m_count;
}

//------------------------------------------------------------------------------

size_t ArrayStorage::MaxElem( void ) const
{
  size_t max=m_blockBytes/sizeof(void*);

  return max;
}

//------------------------------------------------------------------------------

ArrayStorage::Index ArrayStorage::Create( void )
{
  Index zeroBasedIndex;

  zeroBasedIndex=m_count;

  if( m_block!=0 )
  {
    Index n=zeroBasedIndex/m_blockElems;

    if( m_blocks<n+1 )
    {
      m_block[n]=(void**)malloc( m_blockBytes );
      m_blocks++;
    }
  }
  else
  {
    m_block=(void**)malloc( m_blockBytes );
    m_block[0]=malloc( m_blockBytes );
    m_blocks++;
  }

  m_count++;

  return zeroBasedIndex+1;
}

//------------------------------------------------------------------------------

void* ArrayStorage::Elem( Index oneBasedIndex )
{
  vfassert( oneBasedIndex>=1 && oneBasedIndex<=m_count );

  Index zeroBasedIndex=oneBasedIndex-1;
  Index n=zeroBasedIndex/m_blockElems;
  void* block=m_block[n];
  n=zeroBasedIndex-n*m_blockElems;

  void* elem=((char*)block)+n*m_elemBytes;

  return elem;
}

//------------------------------------------------------------------------------

const void* ArrayStorage::Elem( Index oneBasedIndex ) const
{
  vfassert( oneBasedIndex>=1 && oneBasedIndex<=m_count );

  Index zeroBasedIndex=oneBasedIndex-1;
  Index n=zeroBasedIndex/m_blockElems;
  const void* block=m_block[n];
  n=zeroBasedIndex-n*m_blockElems;

  const void* elem=((const char*)block)+n*m_elemBytes;

  return elem;
}

//------------------------------------------------------------------------------

void ArrayStorage::Reset( void )
{
  m_count=0;
}

//------------------------------------------------------------------------------

/*
void * __cdecl DSort::bsearch (
        const void *key,
        const void *base,
        size_t num,
        size_t width,
        int (__cdecl *compare)(const void *, const void *)
        )
{
        char *lo = (char *)base;
        char *hi = (char *)base + (num - 1) * width;
        char *mid;
        unsigned int half;
        int result;

        while (lo <= hi)
                if (half = num / 2)
                {
                        mid = lo + (num & 1 ? half : (half - 1)) * width;
                        if (!(result = (*compare)(key,mid)))
                                return(mid);
                        else if (result < 0)
                        {
                                hi = mid - width;
                                num = num & 1 ? half : half-1;
                        }
                        else    {
                                lo = mid + width;
                                num = half;
                        }
                }
                else if (num)
                        return((*compare)(key,lo) ? NULL : lo);
                else
                        break;

        return(NULL);
}
*/

/*
	if array is empty, result=0, index=0

	returns result of the comparison of key and *pIndex
	( -1 when key < index )

	if key is not found, will return the element with the largest index
	that still compares to less than the key (i.e. the place to insert after)

	if there is at least one element in the array, this must always return
	an index between 1..m_count
*/
int ArrayStorage::BSearch(
  Index* pIndex,
  const void* key,
  int (*CompareProc)( const void* key, const void* elem ) )
{
  int result=-1;

  // If index never gets set in the loop, it means
  // that key is smaller than every element in the array.
  // result should stay at -1 in that case.
  Index index=1;

  if( m_count>0 )
  {
    Index num=m_count;
    Index lo=1;
    Index hi=num;
    Index mid;
    Index half;

    while( lo <= hi )
    {
      int comp;

      half = num / 2 ;
      if( half!=0 )
      {
        mid = lo + (num & 1 ? half : (half - 1));

        comp = CompareProc( key, Elem(mid)  );

        if( comp==0 )
        {
          // exact match
          index=mid;
          result=0;
          break;
        }
        else if( comp < 0 )
        {
          hi = mid - 1;
          num = num & 1 ? half : half-1;
        }
        else
        {
          index = mid;
          result = 1;
          lo = mid + 1;
          num = half;
        }
      }
      else
      {
        // one element left
        vfassert( num==1 );

        comp = CompareProc( key, Elem(lo)  );

        if( comp>=0 )
        {
          // key >= lo
          index=lo;
          result=comp;
        }
        /*
        else if( index>0 )
        {
        	// index < key < lo
        	// index and comp should be set already
        }
        result=comp;
        */
        break;
      }
    }
  }
  else
  {
    // empty array
    index=0;
    result=0;
  }

  vfassert( m_count==0 || ( index>=1 && index<=m_count ) );
  vfassert( index==0 || CompareProc( key, Elem(index) )==result );

  if( pIndex!=0 )
    *pIndex=index;

  return result;
}

//------------------------------------------------------------------------------

size_t ArrayStorage::FlatBytes( void )
{
  size_t bytes=m_count*m_elemBytes;

  return bytes;
}

//------------------------------------------------------------------------------

Error ArrayStorage::Write( Pipe::Out& pipe )
{
  vf::Error error;

  size_t i;

  for( i=0; !error&&i<m_blocks; i++ )
  {
    void* block=m_block[i];
    size_t bytes;

    if( i<m_blocks-1 )
      bytes=m_blockElems*m_elemBytes;
    else
      bytes=(m_count%m_blockElems)*m_elemBytes;

    error = pipe.Write( block, bytes );
  }

  if (!error)
  {
  }

  return error;
}

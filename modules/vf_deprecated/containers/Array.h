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

#ifndef VF_ARRAY_H
#define VF_ARRAY_H

#include "../memory/Pipe.h"

//
// Now this class is useful but it needs work.
// It represent an array whose storage only grows.
// It allocates array elements in big, separate blocks.
// This avoids any need to do memcpy() at the expense of one
// extra pointer indirection to get at an element.
//
// The usage pattern is that the array will never shrink,
// under the assumption that even if elements are removed,
// it will eventually need to grow back to that size (i.e. "high water marking")
//

class ArrayStorage : Uncopyable
{
public:
  typedef size_t Index; // one based

  ArrayStorage( size_t elemBytes, size_t blockBytes );
  ~ArrayStorage();

public:
  Index Count( void ) const;
  Index Create( void );
  void Reset( void );

  size_t MaxElem( void ) const;

  void* Elem( Index oneBasedIndex );
  const void* Elem( Index oneBasedIndex ) const;

  int BSearch(
    Index* pIndex,
    const void* key,
    int (*CompareProc)( const void* key, const void* elem ) );

  size_t	FlatBytes	( void );

  Error Write ( Pipe::Out& pipe );

private:
  size_t m_elemBytes;
  size_t m_blockBytes;
  size_t m_blockElems;
  size_t m_blocks;
  size_t m_count;
  void** m_block;
};

//--------------------------------------------------------------------------

// generic array
template<class T>
class ArrayBase : public ArrayStorage
{
public:
  // stdlib compatibility

  class iterator;
  class const_iterator;

  typedef T				value_type;
  //typedef allocator_type;
  typedef T& 				reference;
  typedef const T& 		const_reference;
  typedef std::size_t		size_type;
  typedef std::ptrdiff_t	difference_type;
  typedef T* 				pointer;
  typedef const T* 		const_pointer;

  struct const_iterator :
    public std::iterator<std::random_access_iterator_tag, value_type>
  {
    const_iterator( const ArrayBase& a, Index i )
      :m_a(&a), m_i(i)
    { }
    const T& operator *() const
    {
      return (*m_a)[m_i];
    }
    const T* operator->() const
    {
      return &(**this);
    }
    const_iterator& operator++()
    {
      m_i++;
      return *this;
    }
    const_iterator operator++(int)
    {
      const_iterator temp=*this;
      operator++();
      return temp;
    }
    const_iterator& operator--()
    {
      m_i--;
      return *this;
    }
    const_iterator operator --(int)
    {
      const_iterator temp=*this;
      operator--();
      return temp;
    }
    bool operator==( const const_iterator& rhs ) const
    {
      return m_i==rhs.m_i;
    }
    bool operator!=( const const_iterator& rhs ) const
    {
      return !(this->operator==(rhs));
    }
    const_iterator& operator=( const const_iterator& iter )
    {
      m_a=iter.m_a;
      m_i=iter.m_i;
      return *this;
    }
    difference_type operator-( const const_iterator& rhs ) const
    {
      return m_i-rhs.m_i;
    }
    const_iterator& operator+=( difference_type n )
    {
      m_i+=n;
      return *this;
    }
    const_iterator& operator-=( difference_type n )
    {
      m_i-=n;
      return *this;
    }
  private:
    const ArrayBase* m_a;
    Index m_i;
  };

  const_iterator begin() const
  {
    return const_iterator( *this, 1 );
  }
  const_iterator end() const
  {
    return const_iterator( *this, Count()+1 );
  }

public:
  typedef T Type;

  ArrayBase( size_t blockBytes ) :
    ArrayStorage( sizeof(T), blockBytes )
  { }

public:
  T& operator[]( Index oneBasedIndex )
  {
    return *((T*)Elem( oneBasedIndex ));
  }

  const T& operator[]( Index oneBasedIndex ) const
  {
    return *((const T*)Elem( oneBasedIndex ));
  }

};

#endif

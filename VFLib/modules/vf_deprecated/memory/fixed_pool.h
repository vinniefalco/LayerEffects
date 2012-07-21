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

#ifndef VF_FIXED_POOL_H
#define VF_FIXED_POOL_H

#include "destroy_n.h"

// Implements a memory pool for objects of uniform size.
// Free list holds deleted elements.
template <class Object>
class fixed_pool
{
public:
  fixed_pool( size_t block_bytes )
    : m_block_bytes( block_bytes )
    , m_cur (0)
    , m_empty (0)
    , m_full (0)
    , m_free (0)
    , m_page_used (0)
    , m_page_free (0)
  {
  }

  ~fixed_pool()
  {
    purge();
  }

  void clear()
  {
    m_page_free += m_page_used;
    m_page_used = 0;

    while( m_full )
    {
      page* p = m_full;
      m_full = m_full->m_next;
      p->clear();
      p->m_next = m_empty;
      m_empty = p;
    }

    if( m_cur )
      m_cur->clear();
  }

  void purge()
  {
    while( m_full )
    {
      page* p = m_full;
      m_full = m_full->m_next;
      p->destroy();
    }

    while( m_empty )
    {
      page* p = m_empty;
      m_empty = m_empty->m_next;
      p->destroy();
    }

    if( m_cur )
    {
      m_cur->destroy();
      m_cur = 0;
    }

    m_page_free = 0;
    m_page_used = 0;
  }

  Object* alloc()
  {
    Object* t;

    if( ! m_free )
    {
      if( ! m_cur )
      {
        if( m_empty )
        {
          m_cur = m_empty;
          m_empty = m_empty->m_next;
          m_page_free--;
        }
        else
        {
          m_cur = page::create( m_block_bytes );
        }
        m_page_used++;
      }

      t = m_cur->alloc();

      if( m_cur->full() )
      {
        m_cur->m_next = m_full;
        m_full = m_cur;
        m_cur = 0;
      }
    }
    else
    {
      t = &m_free->t;
      m_free = m_free->next;
    }

    return t;
  }

  void dealloc( Object* t )
  {
    elem_t* e = reinterpret_cast<elem_t*>( t );
    e->next = m_free;
    m_free = e;
  }

private:
  union elem_t
  {
    Object t;
    elem_t* next;
  };

  class page : LeakChecked <page>
  {
  public:
    page* m_next;

    static page* create( size_t bytes )
    {
      if( bytes < sizeof( page ) )
        throw std::invalid_argument( "bytes < sizeof( page )" );

      return new( ::operator new( bytes ) ) page( bytes );
    }

    void destroy()
    {
      this->~page();
      ::operator delete( this );
    }

    void clear()
    {
      //destroy_n( &m_elem, m_count );
      m_count = 0;
    }

    bool full() const
    {
      return m_count == m_max;
    }

    Object* alloc()
    {
      if( m_count >= m_max )
        throw std::bad_alloc();

      return &m_elem[m_count++].t;
    }

  private:
    page( size_t bytes )
      : m_max( ( bytes - sizeof(*this) ) / sizeof( Object ) )
      , m_count( 0 )

    {
    }

    ~page()
    {
      clear();
    }

  private:
    size_t m_max;
    size_t m_count;
    elem_t m_elem[1];
  };

private:
  size_t m_block_bytes;
  page* m_cur;
  page* m_empty;
  page* m_full;
  elem_t* m_free;
  int m_page_used;
  int m_page_free;
};

#endif
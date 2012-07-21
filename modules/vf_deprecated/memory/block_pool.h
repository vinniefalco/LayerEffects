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

#ifndef VF_BLOCK_POOL_H
#define VF_BLOCK_POOL_H

#include "page_pool.h"

// Implements a memory pool for objects of variable size.
// Memory is allocated in pages and then carved up as needed.
// A page is only released when all of its allocations get
// freed, therefore this is not suitable as a general purpose
// allocator. It is most useful for queues, allocating at the back
// and deleting from the (amortized) front.
// Caller is responsible for synchronization.
class block_pool : vf::Uncopyable
{
private:
  class page
  {
  private:
    char* m_pos;
    size_t m_count;

  public:
    page()
      : m_pos( reinterpret_cast<char*>( this + 1 ) )
      , m_count( 0 )
    {
    }

    bool empty() const
    {
      return m_count == 0;
    }

    void* alloc( size_t bytes )
    {
      void* buffer = 0;
      page_pool::page* p = page_pool::page::get_page( this );
      char* pos = m_pos + bytes;
      if( pos <= p->end() )
      {
        buffer = m_pos;
        m_pos = pos;
        ++m_count;
      }
      return buffer;
    }

    // returns true if page becomes free
    bool dealloc()
    {
      bool bEmpty;
      bEmpty = ! --m_count;
      if( bEmpty )
        m_pos = reinterpret_cast<char*>( this + 1 );
      return bEmpty;
    }
  };

private:
  page_pool& m_pages;
  page* m_page; // current page

public:
  block_pool( page_pool& pages )
    : m_pages( pages )
    , m_page( 0 )
  {
    if( pages.page_bytes() <= sizeof( page ) )
      throw std::logic_error( "pages.page_bytes() <= sizeof( page )" );
  }

  ~block_pool()
  {
    jassert( ! m_page || m_page->empty() );
    if( m_page )
      page_pool::page::get_page( m_page )->dealloc();
  }

  void* alloc( size_t bytes )
  {
    size_t needed = bytes + sizeof(page*);

    void* buf = 0;

    if( m_page )
    {
      buf = m_page->alloc( needed );

      if( ! buf )
        m_page = 0;
    }

    if( ! m_page )
    {
      page_pool::page* pp = m_pages.alloc();
      m_page = new( pp->data() ) page();
    }

    if( ! buf )
      buf = m_page->alloc( needed );

    *((page**)buf) = m_page;
    buf = ((page**)buf)+1;

    return buf;
  }

  void dealloc( void* buf )
  {
    // recover page
    page*& p = ((page**)buf)[-1];
    assert( p ); // double free
    bool bFree = p->dealloc();
    if( bFree )
    {
      if( p == m_page )
        m_page = 0;
      page_pool::page::get_page( p )->dealloc();
    }
    else
    {
#ifndef NDEBUG
      p = 0;
#endif
    }
  }
};

#endif

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

#ifndef VF_PAGE_POOL_H
#define VF_PAGE_POOL_H

// Low level memory pool for allocating pages of fixed size.
// Pages are never freed they are kept on a free list.
// Callers are responsible for synchronization
class page_pool
{
public:
  class page;

private:
  size_t m_page_bytes;
  page* m_free; // list of free pages
  int m_npage;

public:
  class page
  {
  private:
    friend class page_pool;

    union
    {
      page* m_next;
      page_pool* m_pool;
    };

    size_t m_bytes;

  private:
    page (page_pool* pool, size_t bytes)
      : m_pool( pool )
      , m_bytes( bytes - sizeof( *this ) )
    {
    }

  public:
    size_t size() const { return m_bytes; }
    char* data() { return reinterpret_cast<char*>( this + 1 ); }
    char* begin() { return data (); }
    char* end() { return begin() + size(); }
    void dealloc() { m_pool->dealloc (this); }
    static page* get_page( void* buffer ) { return ((page*)buffer)-1; }
  };

public:
  // bytes includes the overhead so the actual
  // amount available is slightly lesss.
  page_pool (size_t bytes)
    : m_page_bytes (bytes)
    , m_free (0)
    , m_npage (0)
  {
    if (bytes <= sizeof (page))
      throw std::logic_error ("bytes <= sizeof(page)");
  }

  ~page_pool ()
  {
    purge ();
  }

  // bytes per page less overhead
  size_t page_bytes () const
  {
    return m_page_bytes - sizeof (page);
  }

  // deallocate all pages on the free list
  void purge ()
  {
    while (m_free)
    {
      page* next = m_free->m_next;
      m_free->~page();
      ::operator delete(m_free);
      m_free = next;
    }
  }

  page* alloc()
  {
    page* p = m_free;

    if (p)
    {
      m_free = m_free->m_next;
      p->m_pool = this;
    }
    else
    {
      p = new (::operator new (m_page_bytes)) page (this, m_page_bytes);

      m_npage++;

      //if (m_npage > 3)
      //  vf::Throw (vf::Error().fail (__FILE__, __LINE__));
    }

    return p;
  }

  void dealloc (page* p)
  {
    p->m_next = m_free;
    m_free = p;
  }
};

#endif
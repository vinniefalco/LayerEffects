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
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

#ifndef VF_PAGEDFREESTORE_VFHEADER
#define VF_PAGEDFREESTORE_VFHEADER

/*============================================================================*/
/**
    Lock-free memory allocator for fixed size pages.

    The ABA problem (http://en.wikipedia.org/wiki/ABA_problem) is avoided by
    treating freed pages as garbage, and performing a collection every second.

    @internal
    @ingroup vf_concurrent internal
*/
class PagedFreeStore : private OncePerSecond
{
public:
  explicit PagedFreeStore (const size_t pageBytes);
  ~PagedFreeStore ();

  // The available bytes per page is a little bit less
  // than requested in the constructor, due to overhead.
  //
  inline size_t getPageBytes () const
  {
    return m_pageBytesAvailable;
  }

  inline void* allocate (const size_t bytes)
  {
    if (bytes > m_pageBytes)
      Throw (Error().fail (__FILE__, __LINE__, "the size is too large"));

    return allocate ();
  }

  void* allocate ();
  static void deallocate (void* const p);

private:
  void* newPage ();
  void doOncePerSecond ();

private:
  struct Page;
  typedef LockFreeStack <Page> Pages;

  struct Pool
  {
    CacheLine::Padded <Pages> fresh;
    CacheLine::Padded <Pages> garbage;
  };

  static inline void* fromPage (Page* const p);
  static inline Page* toPage (void* const p);

  void dispose (Pages& pages);
  void dispose (Pool& pool);

private:
  const size_t m_pageBytes;
  const size_t m_pageBytesAvailable;
  CacheLine::Aligned <Pool> m_pool1;  // pair of pools
  CacheLine::Aligned <Pool> m_pool2;
  Pool* volatile m_cold;            // pool which is cooling down
  Pool* volatile m_hot;             // pool we are currently using
  AtomicCounter m_newPagesLeft; // limit of system allocations

#if 1
  int m_swaps;
  AtomicCounter m_total;
  AtomicCounter m_used;
#endif
};

#endif

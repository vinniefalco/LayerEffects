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

#ifndef VF_FIFOFREESTOREWITHTLS_VFHEADER
#define VF_FIFOFREESTOREWITHTLS_VFHEADER

#include "vf_GlobalPagedFreeStore.h"

/*============================================================================*/
/**
    Lock-free and mostly wait-free FIFO memory allocator.

    This allocator is suitable for use with CallQueue and Listeners. It is
    expected that over time, deallocations will occur in roughly the same order
    as allocations.

    @invariant allocate() and deallocate() are fully concurrent.

    @invariant The ABA problem is handled automatically.

    This implementation uses Thread Local Storage to further improve
    performance. However, it requires boost style thread_specific_ptr.

    @internal
    @ingroup vf_concurrent internal
*/
class FifoFreeStoreWithTLS
{
public:
  FifoFreeStoreWithTLS ();
  ~FifoFreeStoreWithTLS ();

  void* allocate (const size_t bytes);
  static void deallocate (void* const p);

private:
  typedef GlobalPagedFreeStore PagedFreeStoreType;
  struct Header;

  class Page;

  inline Page* newPage ();
  static inline void deletePage (Page* page);

private:
  class PerThreadData;
  boost::thread_specific_ptr <PerThreadData> m_tsp;

  PagedFreeStoreType::Ptr m_pages;
};

#endif

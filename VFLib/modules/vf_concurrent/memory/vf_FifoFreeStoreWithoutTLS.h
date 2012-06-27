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

#ifndef VF_FIFOFREESTOREWITHOUTTLS_VFHEADER
#define VF_FIFOFREESTOREWITHOUTTLS_VFHEADER

#include "vf_GlobalPagedFreeStore.h"

/*============================================================================*/
/**
    Lock-free FIFO memory allocator.

    This allocator is suitable for use with CallQueue and Listeners. It is
    expected that over time, deallocations will occur in roughly the same order
    as allocations.

    @invariant allocate() and deallocate() are fully concurrent.

    @invariant The ABA problem is handled automatically.

    This version of the fifo free store uses less memory and doesn't require
    thread specific storage. However, it runs slower. The performance
    differences are negligible for desktop class applications.

    @internal
    @ingroup vf_concurrent internal
*/
class FifoFreeStoreWithoutTLS
{
public:
  explicit FifoFreeStoreWithoutTLS ();
  ~FifoFreeStoreWithoutTLS ();

  void* allocate (const size_t bytes);
  static void deallocate (void* const p);

private:
  typedef GlobalPagedFreeStore PagedFreeStoreType;

  struct Header;

  class Block;

  inline Block* newBlock ();
  static inline void deleteBlock (Block* b);

private:
  Block* volatile m_active;
  PagedFreeStoreType::Ptr m_pages;
};

#endif

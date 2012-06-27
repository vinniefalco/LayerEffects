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

#ifndef VF_GLOBALFIFOFREESTORE_VFHEADER
#define VF_GLOBALFIFOFREESTORE_VFHEADER

#include "vf_FifoFreeStore.h"

/*============================================================================*/
/**
    A FifoFreeStore singleton.

    @internal
    @ingroup vf_concurrent internal
*/
template <class Tag>
class GlobalFifoFreeStore : public ReferenceCountedSingleton <GlobalFifoFreeStore <Tag> >
{
public:
  inline void* allocate (size_t bytes)
  {
    return m_allocator.allocate (bytes);
  }

  static inline void deallocate (void* const p)
  {
    FifoFreeStoreType::deallocate (p);
  }

  static GlobalFifoFreeStore* createInstance ()
  {
    return new GlobalFifoFreeStore;
  }

private:
  GlobalFifoFreeStore ()
	: ReferenceCountedSingleton <GlobalFifoFreeStore <Tag> >
		(SingletonLifetime::persistAfterCreation)
  {
  }

  ~GlobalFifoFreeStore ()
  {
  }

private:
  FifoFreeStoreType m_allocator;
};

#endif

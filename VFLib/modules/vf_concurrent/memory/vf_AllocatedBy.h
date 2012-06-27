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

#ifndef VF_ALLOCATEDBY_VFHEADER
#define VF_ALLOCATEDBY_VFHEADER

/*============================================================================*/
/** @internal
    @ingroup vf_concurrent internal

    @brief Customized allocation for heap objects.

    Derived classes will use the specified allocator for new and delete

    @param AllocatorType The type of allocator to use.
*/
template <class AllocatorType>
class AllocatedBy
{
public:
  static inline void* operator new (size_t bytes, AllocatorType& allocator) noexcept
  {
    return allocator.allocate (bytes);
  }

  static inline void* operator new (size_t bytes, AllocatorType* allocator) noexcept
  {
    return allocator->allocate (bytes);
  }

  static inline void operator delete (void* p, AllocatorType&) noexcept
  {
    AllocatorType::deallocate (p);
  }

  static inline void operator delete (void* p, AllocatorType*) noexcept
  {
    AllocatorType::deallocate (p);
  }

  static inline void operator delete (void* p) noexcept
  {
    AllocatorType::deallocate (p);
  }
};

#endif

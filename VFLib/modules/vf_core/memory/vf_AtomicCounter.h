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

#ifndef VF_ATOMICCOUNTER_VFHEADER
#define VF_ATOMICCOUNTER_VFHEADER

/*============================================================================*/
/** 
    A thread safe usage counter.
 
    This provides a simplified interface to an atomic integer suitable for
    measuring reference or usage counts. The counter is signaled when the
    count is non zero.

    @ingroup vf_core
*/
class AtomicCounter
{
public:
  /** Create a new counter.

      @param initialValue An optional starting usage count (default is 0).
  */
  AtomicCounter (int initialValue = 0) noexcept
	: m_value (initialValue)
  {
  }

  /** Increment the usage count.

      @return \c true if the counter became signaled.
  */
  inline bool addref () noexcept
  {
	return (++m_value) == 1;
  }

  /** Decrements the usage count.

      @return \c true if the counter became non-signaled.
  */
  inline bool release () noexcept
  {
    // Unfortunately, AllocatorWithoutTLS breaks this assert
    //jassert (isSignaled ());

    return (--m_value) == 0;
  }

  /** Determine if the counter is signaled.

      Note that another thread can cause the counter to become reset after
      this function returns true.

      @return \c true if the counter was signaled.
  */
  inline bool isSignaled () const noexcept
  {
	return m_value.get() > 0;
  }

private:
  Atomic <int> m_value;
};

#endif

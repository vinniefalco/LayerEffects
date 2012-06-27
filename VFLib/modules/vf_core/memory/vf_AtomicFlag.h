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

#ifndef VF_ATOMICFLAG_VFHEADER
#define VF_ATOMICFLAG_VFHEADER

/*============================================================================*/
/** 
    A thread safe flag.
 
    This provides a simplified interface to an atomic integer suitable for
    representing a flag. The flag is signaled when on, else it is considered
    reset.

    @ingroup vf_core
*/
class AtomicFlag
{
public:
  /** Create an AtomicFlag in the reset state. */
  AtomicFlag () noexcept
	: m_value (0)
  {
  }

  /** Signal the flag.

      If two or more threads simultaneously attempt to signal the flag,
      only one will receive a true return value.

      @return true if the flag was previously reset.
  */
  inline bool trySignal () noexcept
  {
    return m_value.compareAndSetBool (1, 0);
  }

  /** Signal the flag.
  
      The flag must be in the reset state. Only one thread may
      call this at a time.
  */
  inline void signal () noexcept
  {
  #if VF_DEBUG
    const bool success = m_value.compareAndSetBool (1, 0);
    vfassert (success);
  #else
    m_value.set (1);
  #endif
  }

  /** Reset the flag.

      The flag must be in the signaled state. Only one thread may
      call this at a time. Usually it is the thread that was successful
      in a previous call to trySignal().
  */
  inline void reset () noexcept
  {
  #if VF_DEBUG
    const bool success = m_value.compareAndSetBool (0, 1);
    vfassert (success);
  #else
    m_value.set (0);
  #endif
  }

  /** Check if the AtomicFlag is signaled

      The signaled status may change immediately after this call
      returns. The caller must synchronize.

      @return true if the flag was signaled.
  */
  inline bool isSignaled () const noexcept
  {
	return m_value.get() == 1;
  }

private:
  Atomic <int> m_value;
};

#endif

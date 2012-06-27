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

#ifndef VF_ATOMICSTATE_VFHEADER
#define VF_ATOMICSTATE_VFHEADER

/*============================================================================*/
/**
    A thread safe state variable.

    This provides a simplified interface to an integer used to control atomic
    state transitions. A state is distinguished by a single integer value.

    @ingroup vf_core
*/ 
class AtomicState
{
public:
  /** Create a new state with an optional starting value.

      @param initialState The initial state.
  */

      
  explicit AtomicState (const int initialState = 0) noexcept
	: m_value (initialState)
  {
  }
  
  /** Retrieve the current state.

      This converts the object to an integer reflecting the current state.

      Note that other threads may change the value immediately after this
      function returns. The caller is responsible for synchronizing.

      @return The state at the time of the call.
  */
  inline operator int () const
  {
	return m_value.get();
  }

  /** Attempt a state transition.

      The current state is compared to `from`, and if the comparison is
      successful the state becomes `to`. The entire operation is atomic.

      @param from   The current state, for comparison.
      
      @param to     The desired new state.

      @return       true if the state transition succeeded.
  */
  inline bool tryChangeState (const int from, const int to) noexcept
  {
    return m_value.compareAndSetBool (to, from);
  }

  /** Perform a state transition.

      This attempts to change the state and generates a diagnostic on
      failure. This routine can be used instead of tryChangeState()
      when program logic requires that the state change must succeed.

      @param from   The required current state.
      
      @param to     The new state.
  */
  inline void changeState (const int from, const int to) noexcept
  {
#if VF_DEBUG
    const bool success = tryChangeState (from, to);
    vfassert (success);
#else
    tryChangeState (from, to);
#endif
  }

private:
  Atomic <int> m_value;
};

#endif

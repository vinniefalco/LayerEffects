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

#ifndef VF_ATOMICPOINTER_VFHEADER
#define VF_ATOMICPOINTER_VFHEADER

/*============================================================================*/
/**
    A thread safe pointer.
 
    This provides a simplified interface to an atomic pointer suitable
    for building containers or composite classes. Operator overloads
    allow access to the underlying pointer using natural C++ syntax.

    @ingroup vf_core
*/
template <class P>
class AtomicPointer
{
public:
  /** Create a pointer.

      @param initialValue An optional starting value (default is null).
  */
  explicit AtomicPointer (P* const initialValue = nullptr) noexcept
    : m_value (initialValue)
  {
  }

  /** Retrieve the pointer value */
  inline P* get () const noexcept
  {
    return m_value.get();
  }

  /** Obtain a pointer to P through type conversion.

      The caller must synchronize access to P.

      @return A pointer to P.
  */
  inline operator P* () const noexcept
  {
    return get ();
  }

  /** Dereference operator

      The caller must synchronize access to P.

      @return A reference to P.
  */
  inline P& operator* () const noexcept
  {
    return &get();
  }

  /** Member selection

      The caller must synchronize access to P.
  
      @return A pointer to P.
  */
  inline P* operator-> () const noexcept
  {
    return get();
  }

  inline void set (P* p)
  {
    m_value.set (p);
  }

  /** Atomically assign a new pointer

      @param newValue The new value to assign.
  */
  inline void operator= (P* newValue) noexcept
  {
    set (newValue);
  }

  /** Atomically assign a new pointer and return the old value.

      @param newValue The new value to assign.

      @return         The previous value.
  */
  inline P* exchange (P* newValue)
  {
    return m_value.exchange (newValue);
  }

  /** Conditionally perform an atomic assignment.

      The current value is compared with oldValue and atomically
      set to newValue if the comparison is equal.
      
      The caller is responsible for handling the ABA problem.

      @param  newValue  The new value to assign.

      @param  oldValue  The matching old value.

      @return true if the assignment was performed.
  */
  inline bool compareAndSet (P* newValue, P* oldValue)
  {
    return m_value.compareAndSetBool (newValue, oldValue);
  }

private:
  Atomic <P*> m_value;
};

#endif

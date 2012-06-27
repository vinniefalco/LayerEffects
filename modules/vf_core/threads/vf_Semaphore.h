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

#ifndef VF_SEMAPHORE_VFHEADER
#define VF_SEMAPHORE_VFHEADER

/*============================================================================*/
/**
  @ingroup vf_core

  @brief A semaphore.

  This provides a traditional semaphore synchronization primitive. There is no
  upper limit on the number of signals.

  @note There is no tryWait() or timeout facility for acquiring a resource.
*/
class Semaphore
{
public:
  /** Create a semaphore with the specified number of resources.

      @param initialCount The starting number of resources.
  */
  explicit Semaphore (int initialCount);

  ~Semaphore ();

  /** Increase the number of available resources.

      @param amount The number of new resources available.
  */
  void signal (int amount = 1);

  /** Wait for a resource.
  */
  void wait ();

private:
  class WaitingThread
    : public LockFreeStack <WaitingThread>::Node
    , LeakChecked <WaitingThread>
  {
  public:
    WaitingThread ();

    void wait ();
    void signal ();

  private:
    WaitableEvent m_event;
  };

  typedef SpinLock LockType;

  LockType m_mutex;
  Atomic <int> m_counter;
  LockFreeStack <WaitingThread> m_waitingThreads;
  LockFreeStack <WaitingThread> m_deleteList;
};

#endif

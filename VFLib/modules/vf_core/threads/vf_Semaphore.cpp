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

Semaphore::WaitingThread::WaitingThread ()
  : m_event (false) // auto-reset
{
}

void Semaphore::WaitingThread::wait ()
{
  m_event.wait ();
}

void Semaphore::WaitingThread::signal ()
{
  m_event.signal ();
}

//==============================================================================

Semaphore::Semaphore (int initialCount)
  : m_counter (initialCount)
{
}

Semaphore::~Semaphore ()
{
  // Can't delete the semaphore while threads are waiting on it!!
  jassert (m_waitingThreads.pop_front () == nullptr);

  for (;;)
  {
    WaitingThread* waitingThread = m_deleteList.pop_front ();

    if (waitingThread != nullptr)
      delete waitingThread;
    else
      break;
  }
}

void Semaphore::signal (int amount)
{
  jassert (amount > 0);

  while (amount--)
  {
    // Make counter and list operations atomic.
    LockType::ScopedLockType lock (m_mutex);

    if (++m_counter <= 0)
    {
      WaitingThread* waitingThread = m_waitingThreads.pop_front ();

      jassert (waitingThread != nullptr);

      waitingThread->signal ();
    }
  }
}

void Semaphore::wait ()
{
  // Always prepare the WaitingThread object first, either
  // from the delete list or through a new allocation.
  //
  WaitingThread* waitingThread = m_deleteList.pop_front ();
  if (waitingThread == nullptr)
    waitingThread = new WaitingThread;

  {
    // Make counter and list operations atomic.
    LockType::ScopedLockType lock (m_mutex);

    if (--m_counter >= 0)
    {
      // Acquired the resource so put waitingThread back.
      m_deleteList.push_front (waitingThread);

      waitingThread = nullptr;
    }
    else
    {
      // Out of resources, go on to the waiting list.
      m_waitingThreads.push_front (waitingThread);
    }
  }

  // Do we need to wait?
  if (waitingThread != nullptr)
  {
    // Yes so do it.
    waitingThread->wait ();

    // If the wait is satisfied, then we've been taken off the
    // waiting list so put waitingThread back in the delete list.
    //
    m_deleteList.push_front (waitingThread);
  }
}
